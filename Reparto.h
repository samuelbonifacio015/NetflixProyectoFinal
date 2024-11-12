#pragma once
#include "Recursos.h"

class Director
{
public:
    string nombre;

    Director(string nombre) : nombre(nombre) {}
    string obtenerNombre() const { return nombre; }
};

class Actor
{
public:
    string nombre;

    Actor(const string& nombre) : nombre(nombre) {}

    string obtenerNombre() const { return nombre; }
};

