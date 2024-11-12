#pragma once
#include "Recursos.h"
#include "Pelicula.h"
#define NOT_FOUND -1

template<typename Comparable>
class BinarySearchPelicula {
public:
	BinarySearchPelicula() {}

	int buscarPorCalificacion(const vector<Comparable>& peliculas, const float calificacion) {
		int bajo = 0, alto = peliculas.size() - 1;
		while (bajo <= alto) {
			int medio = (bajo + alto) / 2;
			if (peliculas[medio].obtenerCalificacion() < calificacion) {
				bajo = medio + 1;
			}
			else if (peliculas[medio].obtenerCalificacion() > calificacion) {
				alto = medio - 1;
			}
			else {
				return medio;
			}
		}
		return NOT_FOUND;
	}

	int buscarMejorPorGenero(const vector<Comparable>& peliculas, const string& genero)
	{
		int bajo = 0;
		int alto = peliculas.size() - 1;
		int mejorIndice = NOT_FOUND;

		while (bajo <= alto) {
			int medio = (bajo + alto) / 2;
			if (peliculas[medio].obtenerGenero() < genero) {
				bajo = medio + 1;
			}
			else {
				alto = medio - 1;
			}
		}

		if (bajo < peliculas.size() && peliculas[bajo].obtenerGenero() == genero)
		{
			mejorIndice = bajo;             
			float mejorCalificacion = peliculas[bajo].obtenerCalificacion();

			for (int i = bajo; i < peliculas.size() && peliculas[i].obtenerGenero() == genero; i++) {
				if (peliculas[i].obtenerCalificacion() > mejorCalificacion) {
					mejorCalificacion = peliculas[i].obtenerCalificacion();
					mejorIndice = i;
				}
			}
		}

		return mejorIndice;
	}

	int buscarPorTitulo(const vector<Pelicula>& peliculas, const string& titulo) {
		for (int i = 0; i < peliculas.size(); ++i) {
			if (peliculas[i].obtenerTitulo() == titulo) {
				return i;
			}
		}
		return NOT_FOUND;
	}

};

