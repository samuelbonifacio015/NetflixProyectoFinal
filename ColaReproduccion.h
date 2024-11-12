#pragma once
#include "Pelicula.h"
#include <queue>

class ColaReproduccion {
private:
queue <Pelicula> cola;  public:

	void agregarACola(const Pelicula& pelicula)
	{
		cola.push(pelicula);
		cout << "Pelicula: " << pelicula.obtenerTitulo() << " agregada a la Cola de Reproduccion" << endl;
	}

	void reproducirSiguiente()
	{
		if (cola.empty())
		{
			cout << "No hay peliculas en la lista de reproduccion, agregue una." << endl;
		}
		else {
			Pelicula peliculaActual = cola.front(); 		
			cola.pop(); 		
			cout << "Reproduciendo: " << peliculaActual.obtenerTitulo() << endl;
		}
	}

	void mostrarCola() const
	{
		queue<Pelicula>temp = cola; 
		cout << "Lista de Reproduccion: " << endl;
		while (!temp.empty())
		{
			cout << " - " << temp.front().obtenerTitulo() << endl;
			temp.pop();
		}
	}
};