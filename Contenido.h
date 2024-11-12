#pragma once
#include "Recursos.h"
#include "Reparto.h"
#include <vector>

class Contenido
{
public:
	int id;
	string titulo;
	int duracion;
	string genero;
	Director* director;      vector<Actor*> actores;
	Contenido(int id, string titulo, int duracion, string genero, Director* director, const vector<Actor*>& actores)
		: id(id), titulo(titulo), duracion(duracion), genero(genero), director(director), actores(actores) {}

	int obtenerId() const { return id; }
	string obtenerTitulo() const { return titulo; }
	int obtenerDuracion() const { return duracion; }
	string obtenerGenero() const { return genero; }

	Director* obtenerDirector() const { return director; }
	vector<Actor*> obtenerActores() const { return actores; }
};