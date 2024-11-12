#pragma once
#include "Pelicula.h"
#include <iostream>
#include <string>
#include <functional> using namespace std;

struct NodoPelicula {
    Pelicula pelicula;
    NodoPelicula* izquierdo;
    NodoPelicula* derecho;

    NodoPelicula(Pelicula p) : pelicula(p), izquierdo(nullptr), derecho(nullptr) {}
};

template <typename T>
class Nodo
{
public:
    T data;
    Nodo* siguiente;
    Nodo* anterior;

    Nodo(T data) : data(data), siguiente(nullptr), anterior(nullptr) {}
};

class ArbolBinarioPelicula {
private:
    NodoPelicula* raiz;
    function<bool(Pelicula, Pelicula)> criterio;

        NodoPelicula* insertarRec(NodoPelicula* nodo, Pelicula p) 
        {
        if (!nodo) {
            return new NodoPelicula(p);}
        if (criterio(p, nodo->pelicula)) {
            nodo->izquierdo = insertarRec(nodo->izquierdo, p);}
        else {
            nodo->derecho = insertarRec(nodo->derecho, p);}
        return nodo;
    }

        void enOrdenRec(NodoPelicula* nodo) const {
        if (nodo) {
            enOrdenRec(nodo->izquierdo);
            cout << nodo->pelicula.obtenerTitulo() << " - Calificaci�n: " << nodo->pelicula.obtenerCalificacion() << endl;
            enOrdenRec(nodo->derecho);
        }
    }

        NodoPelicula* buscarPorTituloRec(NodoPelicula* nodo, const string& titulo) const {
        if (!nodo || nodo->pelicula.obtenerTitulo() == titulo) {
            return nodo;
        }
        if (titulo < nodo->pelicula.obtenerTitulo())
        {
            return buscarPorTituloRec(nodo->izquierdo, titulo);   
        }
        return buscarPorTituloRec(nodo->derecho, titulo);  
        }

public:
        ArbolBinarioPelicula(function<bool(Pelicula, Pelicula)> criterio) : raiz(nullptr), criterio(criterio) {}

        void insertar(Pelicula p) 
        {
        raiz = insertarRec(raiz, p);
        }

        void mostrarEnOrden() const 
        {
        enOrdenRec(raiz);
        }

        Pelicula* buscarPorTitulo(const string& titulo) const 
        {
        NodoPelicula* resultado = buscarPorTituloRec(raiz, titulo);
        if (resultado)
        {
            return &resultado->pelicula;
        }
        return nullptr;
    }
};
