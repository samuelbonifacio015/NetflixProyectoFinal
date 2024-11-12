#pragma once
#include "Recursos.h"
#include "Pelicula.h"

using namespace std;

template <typename T>
class Ordenador
{
public:
	void mergeSort(vector<T>& contenidos, int izquierda, int derecha, bool criterioOrd)
	{
		if (izquierda < derecha) {
			int medio = izquierda + (derecha - izquierda) / 2;
			mergeSort(contenidos, izquierda, medio, criterioOrd);
			mergeSort(contenidos, medio + 1, derecha, criterioOrd);
			merge(contenidos, izquierda, medio, derecha, criterioOrd);
		}
	}

private:
	void merge(vector<T>& contenidos, int izquierda, int medio, int derecha, bool criterioOrd)
	{
		int n1 = medio - izquierda + 1;
		int n2 = derecha - medio;

		vector<T> L(n1);
		vector<T> R(n2);

		for (int i = 0; i < n1; i++)
			L[i] = contenidos[izquierda + i];
		for (int i = 0; i < n2; i++)
			R[i] = contenidos[medio + 1 + i];

		auto compararCriterioOrd = [](const T& a, const T& b) {
			return a.obtenerCalificacion() > b.obtenerCalificacion();
			};
		auto compararPorDuracion = [](const T& a, const T& b) {
			return a.obtenerDuracion() > b.obtenerDuracion();
			};

		int i = 0, j = 0, k = izquierda;
		while (i < n1 && j < n2) {
			if (criterioOrd ? compararCriterioOrd(L[i], R[j]) : compararPorDuracion(L[i], R[j]))
			{
				contenidos[k] = L[i];
				i++;
			}
			else {
				contenidos[k] = R[j];
				j++;
			}
			k++;
		}

		while (i < n1) {
			contenidos[k] = L[i];
			i++;
			k++;
		}

		while (j < n2) {
			contenidos[k] = R[j];
			j++;
			k++;
		}
	}
};

class Filtrador
{
public:
	static void filtrarPorGenero(const vector<Pelicula>& contenidos, const string& genero)
	{
		vector<Pelicula> peliculasFiltradas;

		for (const auto& pelicula : contenidos)
		{
			if (pelicula.obtenerGenero() == genero)
			{
				peliculasFiltradas.push_back(pelicula);
			}
		}

		if (peliculasFiltradas.empty())
		{
			cout << "No se encontraron peliculas en el genero: " << genero << endl;
		}
		else {
			cout << "Peliculas en el genero " << genero << ":" << endl;
			for (const auto& pelicula : peliculasFiltradas)
			{
				cout << "=============================================" << endl;
				cout << pelicula.obtenerTitulo() << " - " << pelicula.obtenerCalificacion() << endl;
				cout << "=============================================" << endl;
			}
		}
	}
};

