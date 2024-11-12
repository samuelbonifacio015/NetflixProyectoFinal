#pragma once
#include "Contenido.h"
#include "Recursos.h"

class Pelicula : public Contenido
{
public:
	string fechaEstreno;
	float calificacion;

	Pelicula()
		: Contenido(0, "", 0, "", nullptr, {}), fechaEstreno(""), calificacion(0.0) {}

	Pelicula(int id, string titulo, int duracion, string genero, Director* director, const vector<Actor*>& actores, string fechaEstreno, float calificacion)
		: Contenido(id, titulo, duracion, genero, director, actores), fechaEstreno(fechaEstreno), calificacion(calificacion) {}

	string obtenerFechaEstreno() const { return fechaEstreno; }
	float obtenerCalificacion() const { return calificacion; }

	const vector<Actor*>& obtenerActores() const
	{
		return this->actores;
	}

	void reproducirPelicula(const string& titulo, int duracion)
	{
		system("cls");
		cout << "-----------------------" << endl;
		cout << "Reproduciendo: " << titulo << endl;
		cout << "Duracion: " << duracion << " minutos" << endl;
		cout << "-----------------------" << endl;

		cout << "Presione cualquier tecla para detener la reproducci�n..." << endl;

		_getch();         
		system("cls");
	}


};