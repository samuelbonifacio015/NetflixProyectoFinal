#pragma once
#include <unordered_map> #include "App.h"
#include "Pelicula.h"

class HashTable
{
private:
	unordered_map<string, Pelicula> favoritos;
public:
	void agregarAFavoritos(const Pelicula& pelicula)
	{
		favoritos[pelicula.obtenerTitulo()] = pelicula;
		cout << "Pelicula: " << pelicula.obtenerTitulo() << " ha sido agregada a favoritos: " << endl;
	}

	bool estaEnFavoritos(const string& titulo) const {
		return favoritos.find(titulo) != favoritos.end();
	}

	void mostrarFavoritos() const {
		cout << "Lista de Favoritos:" << endl;
		for (const auto& par : favoritos) {
			const string& titulo = par.first;
			cout << "- " << titulo << endl;
		}
	}

};