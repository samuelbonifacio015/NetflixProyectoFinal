#pragma once 
#include "Pelicula.h"
#include "Lista.h"
#include "Ordenador.h"
#include "ArbolBinario.h"
#include "Recursos.h"
#include "Cliente.h"

class FileHandler {
private:
	string file_url;
	ifstream file;
	string delimiter = ",";
public:

	Pelicula* fromStringPelicula(const string& s, const string& delim)
	{
		size_t pos = 0;
		string token;
		int i = 0;
		string values[8];
		string line = s;

		while ((pos = line.find(delim)) != string::npos)
		{
			token = line.substr(0, pos);
			values[i] = token;
			line.erase(0, pos + delim.length());
			i++;
		}
		values[i] = line;
		for (int j = 0; j < 8; j++) {
			if (values[j].empty()) {
				return nullptr;
			}
		}

		Director* director = new Director(values[4]);

		vector<Actor*> actores;
		stringstream actoresStream(values[6]);
		string nombreActor;

		while (getline(actoresStream, nombreActor, ';')) {
			nombreActor.erase(nombreActor.begin(), find_if(nombreActor.begin(), nombreActor.end(), [](unsigned char ch) { return !isspace(ch); }));
			nombreActor.erase(find_if(nombreActor.rbegin(), nombreActor.rend(), [](unsigned char ch) { return !isspace(ch); }).base(), nombreActor.end());

			if (!nombreActor.empty()) {
				actores.push_back(new Actor(nombreActor));
			}
		}

		return new Pelicula(stoi(values[0]), values[1], stoi(values[2]), values[3], director, actores, values[5], stof(values[7]));
	}

	bool loadFilePelicula(Lista<Pelicula>& lista)
	{
		file.open(file_url);
		if (file.is_open()) {
			string line;
			while (getline(file, line)) {
				Pelicula* pelicula = fromStringPelicula(line, delimiter);
				if (pelicula != nullptr) {
					lista.agregar(*pelicula);
					delete pelicula;
				}
			}
			file.close();
			return true;
		}
		else {
			cout << "No se pudo abrir el archivo." << endl;
			return false;
		}
	}

	void saveFilePelicula(Lista<Pelicula> lista)
	{
		ofstream outfile(file_url);
		if (outfile.is_open()) {
			Nodo<Pelicula>* current = lista.getCabeza();
			while (current != nullptr)
			{
				Pelicula pelicula = current->data;
				outfile << pelicula.obtenerId() << delimiter
					<< pelicula.obtenerTitulo() << delimiter
					<< pelicula.obtenerDuracion() << delimiter
					<< pelicula.obtenerGenero() << delimiter
					<< pelicula.obtenerDirector()->obtenerNombre() << delimiter << pelicula.obtenerFechaEstreno() << delimiter
					<< pelicula.obtenerCalificacion() << delimiter;

				bool isFirst = true;
				for (Actor* actor : pelicula.obtenerActores())
				{
					if (!isFirst)
					{
						outfile << ";";
					}
					outfile << actor->obtenerNombre();
					isFirst = false;
				}
				outfile << "\n";
				current = current->siguiente;
			}

			outfile.close();
		}
		else {
			cout << "No se pudo abrir el archivo para guardar." << endl;
		}
	}

	Cliente* fromStringCliente(const string& s, const string& delim)
	{
		size_t pos = 0;
		string token;
		int i = 0;
		string values[8];
		string line = s;

		while ((pos = line.find(delim)) != string::npos)
		{
			token = line.substr(0, pos);
			values[i] = token;
			line.erase(0, pos + delim.length());
			i++;
		}
		values[i] = line;
		for (int j = 0; j < 8; j++)
		{
			if (values[j].empty())
			{
				return nullptr;
			}
		}
		return new Cliente(stoi(values[0]), values[1], values[2], values[3], values[4]);
	}

	bool loadFileCliente(Lista<Cliente>& lista)
	{
		file.open(file_url);
		if (file.is_open())
		{
			string line;
			while (getline(file, line))
			{
				Cliente* cliente = fromStringCliente(line, delimiter);
				if (cliente != nullptr)
				{
					lista.agregar(*cliente);
					delete cliente;
				}
			}
			file.close();
			return true;
		}
		else {
			cout << "No se pudo abrir el archivo." << endl;
			return false;
		}
	}

	void saveFileCliente(Lista<Cliente> lista)
	{
		ofstream outfile(file_url);
		if (outfile.is_open())
		{
			Nodo<Cliente>* current = lista.getCabeza();
			while (current != nullptr)
			{
				Cliente cliente = current->data;
				outfile << cliente.obtenerID() << delimiter
					<< cliente.obtenerNombre() << delimiter
					<< cliente.obtenerTelefono() << delimiter
					<< cliente.obtenerCorreoElectronico() << delimiter
					<< cliente.obtenerContrasena() << delimiter;
				outfile << "\n";
				current = current->siguiente;
			}

			outfile.close();
		}
		else
		{
			cout << "No se pudo abrir el archivo para guardar." << endl;
		}
	}

	void setFileURL(const string& file_url)
	{
		this->file_url = file_url;
	}

	~FileHandler()
	{
		if (file.is_open())
		{
			file.close();
		}
	}
};