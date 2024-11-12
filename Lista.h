#pragma once
#include "Recursos.h"
#include "ArbolBinario.h"  
#include "Reparto.h"
#include "Pelicula.h"
#include "Ordenador.h"
#include "Cliente.h"

using namespace std;

template <typename T>
class Lista
{
private:

	Nodo<T>* cabeza;
	Nodo<T>* cola;
	int tamano;

public:
	Lista() : cabeza(nullptr), cola(nullptr), tamano(0) {}

	Nodo<T>* getCabeza()
	{
		return cabeza;
	}

	void agregar(T dato)
	{
		Nodo<T>* current = new Nodo <T>(dato);
		current->data = dato;
		if (cola == nullptr)
		{
			cola = current;
			cabeza = current;
			return;
		}
		cola->siguiente = current;
		current->anterior = cola;
		cola = current;
		current = nullptr;
	}

	vector <T> obtener()
	{
		vector <T> lista;
		Nodo<T>* current = cabeza;
		while (current != nullptr)
		{
			lista.push_back(current->data);
			current = current->siguiente;
		}
		return lista;
	}

	void imprimirContenidosCalificacion(vector <T> contenidos)
	{
		for (int i = 0; i < contenidos.size(); i++)
		{
			cout << "Titulo: " << contenidos[i].obtenerTitulo() << ", Calificacion: " << contenidos[i].obtenerCalificacion() << endl;
		}
	}

	void imprimirContenidos(vector <T> contenidos)
	{
		for (int i = 0; i < contenidos.size(); i++)
		{
			cout << "Titulo: " << contenidos[i].obtenerTitulo() << endl;
		}
	}

	void imprimirContenidosTiempo(vector <T> contenidos)
	{
		for (int i = 0; i < contenidos.size(); i++)
		{
			cout << "Titulo: " << contenidos[i].obtenerTitulo() << ", Tiempo de Duracion: " << contenidos[i].obtenerDuracion() << endl;
		}
	}

	void imprimirNombreCliente(vector <T> nombre)
	{
		for (int i = 0; i < nombre.size(); i++)
		{
			cout << "BIENVENIDO " << nombre[i].obtenerNombre() << endl;
		}
	}

	Nodo <T>* obtenerContenidoPorIndice(int indice)
	{
		int index = 0;
		Nodo<T>* current = cabeza;
		while (current != nullptr)
		{
			if (index == indice)
			{
				return current;
			}
			index++;
			current = current->siguiente;
		}
		return nullptr;
	}

	/*void agregarPelicula(T pelicula) {
		Nodo<T>* nuevoNodo = new Nodo<T>(pelicula);
		if (cola == nullptr) {
			cabeza = cola = nuevoNodo;
		}
		else {
			cola->siguiente = nuevoNodo;
			nuevoNodo->anterior = cola;
			cola = nuevoNodo;
		}
		tamano++;
	} */

	void eliminarPrimera()
	{
		if (cabeza == nullptr) return;
		Nodo<T>* temp = cabeza;
		cabeza = cabeza->siguiente;
		if (cabeza != nullptr) {
			cabeza->anterior = nullptr;
		}
		else {
			cola = nullptr;
		}
		delete temp;
		tamano--;
	}

	T* obtenerPrimeraPelicula() {
		if (cabeza != nullptr) {
			return &cabeza->data;
		}
		return nullptr;
	}

	int obtenerTamano() {
		return tamano;
	}

	void imprimirLista() {
		Nodo<T>* actual = cabeza;
		while (actual != nullptr) {
			cout << actual->data.obtenerTitulo() << endl;
			actual = actual->siguiente;
		}
	}

	void eliminarPorIndice(int indice) {
		if (indice < 0 || indice >= tamano || cabeza == nullptr) {
			cout << "Indice fuera de rango o lista vacia." << endl;
			return;
		}
		Nodo<T>* actual = cabeza;
		for (int i = 0; i < indice; i++) {
			actual = actual->siguiente;
		}
		if (actual == cabeza) {
			eliminarPrimera();
		}
		else if (actual == cola) {
			cola = actual->anterior;
			cola->siguiente = nullptr;
			delete actual;
			tamano--;
		}
		else {
			actual->anterior->siguiente = actual->siguiente;
			actual->siguiente->anterior = actual->anterior;
			delete actual;
			tamano--;
		}
	}

	/** void cargarPeliculasDesdeArchivo(string nombreArchivo) {
		 ifstream archivo(nombreArchivo);
		 if (!archivo.is_open()) {
			 cout << "Error al abrir el archivo: " << nombreArchivo << endl;
			 return;
		 }

		 string linea;
		 while (getline(archivo, linea)) {
			 stringstream ss(linea);

			 string id, titulo, duracion, genero, nombreDirector, fechaEstreno, calificacion, actoresStr;

			 getline(ss, id, ',');
			 getline(ss, titulo, ',');
			 getline(ss, duracion, ',');
			 getline(ss, genero, ',');
			 getline(ss, nombreDirector, ',');
			 getline(ss, fechaEstreno, ',');
			 getline(ss, calificacion, ',');
			 getline(ss, actoresStr);

			 Director* director = new Director(nombreDirector);

			 vector<Actor*> actores;
			 stringstream actoresStream(actoresStr);
			 string nombreActor;

			 while (getline(actoresStream, nombreActor, ';')) {
				 nombreActor.erase(nombreActor.begin(), find_if(nombreActor.begin(), nombreActor.end(), [](unsigned char ch) { return !isspace(ch); }));
				 nombreActor.erase(find_if(nombreActor.rbegin(), nombreActor.rend(), [](unsigned char ch) { return !isspace(ch); }).base(), nombreActor.end());

				 if (!nombreActor.empty()) {
					 actores.push_back(new Actor(nombreActor));
				 }
			 }

			 Pelicula pelicula(stoi(id), titulo, stoi(duracion), genero, director, actores, fechaEstreno, stof(calificacion));
			 agregar(pelicula);
		 }

		 archivo.close();
	 } */
};
