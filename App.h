#pragma once
#include "Archivo.h"
#include "BusquedaBinaria.h"
#include "Recursos.h"
#include "Ordenador.h"
#include "HashTable.h"
#include "ColaReproduccion.h"
#include "Cliente.h"
#include "Grafos.h"
#include "Suscripcion.h"
#include <conio.h>

class App
{
private:
	// atributos principales de la aplicaci�n
	Lista<Pelicula> listaPelicula;               // lista de todas las pel�culas disponibles
	FileHandler FileHandler;                     // manejador de archivos
	Ordenador<Pelicula> ordenador;               // clase para ordenar pel�culas
	BinarySearchPelicula<Pelicula> busqueda;     // clase para b�squeda binaria de pel�culas
	HashTable favoritos;                         // tabla hash para almacenar pel�culas favoritas
	Lista<Cliente> listaCliente;                 // lista de clientes registrados
	ColaReproduccion listaReproduccion;          // cola de reproducci�n de pel�culas
	Lista<Suscripcion> listaSuscripcion;         // lista de suscripciones

public:
	// carga las pel�culas desde el archivo
	bool loadFilePelicula(const string& file_url)
	{
		FileHandler.setFileURL(file_url);
		return FileHandler.loadFilePelicula(listaPelicula);
	}

	// guarda las pel�culas en el archivo
	void saveFilePelicula()
	{
		FileHandler.saveFilePelicula(listaPelicula);
	}

	// carga los clientes desde el archivo
	bool loadFileCliente(const string& file_url)
	{
		FileHandler.setFileURL(file_url);
		return FileHandler.loadFileCliente(listaCliente);
	}

	// guarda los clientes en el archivo
	void saveFileCliente()
	{
		FileHandler.saveFileCliente(listaCliente);
	}

	// registra un nuevo cliente y lo guarda en el archivo
	void registrarCliente(Lista<Cliente>& lista)
	{
		int id;
		string nombre, telefono, correoElectronico, contrasena;

		cout << "===========================================" << endl;
		cout << "                  REGISTRO                 " << endl;
		cout << "===========================================" << endl;
		cout << "Ingrese el ID del cliente: ";
		cin >> id;
		cin.ignore();
		cout << "Ingrese el nombre del cliente: ";
		getline(cin, nombre);

		cout << "Ingrese el telefono del cliente: ";
		getline(cin, telefono);

		cout << "Ingrese el correo electronico del cliente: ";
		getline(cin, correoElectronico);

		cout << "Ingrese la contrasena del cliente: ";
		getline(cin, contrasena);

		Cliente nuevoCliente(id, nombre, telefono, correoElectronico, contrasena);
		lista.agregar(nuevoCliente);
		saveFileCliente();

		cout << "Cliente registrado exitosamente y guardado en el archivo.\n";
	}

	// muestra mensaje de bienvenida al usuario
	void bienvenida(const string& nombreCliente)
	{
		cout << "===========================================" << endl;
		cout << "                  BIENVENIDO               " << endl;
		cout << "===========================================" << endl;
		cout << "Hola, " << nombreCliente << "!" << endl;
		cout << "�Nos alegra tenerte con nosotros!" << endl;
		cout << "===========================================" << endl;
		cout << "�Disfruta de tu experiencia!" << endl;
		cout << "===========================================" << endl;
	}

	// permite al cliente iniciar sesi�n ingresando correo y contrase�a
	Cliente* iniciarSesion()
	{
		string correo, contrasena;
		cout << "Ingrese su correo electronico: ";
		cin >> correo;
		cout << "Ingrese su contrasena: ";
		cin >> contrasena;

		for (Cliente& cliente : listaCliente.obtener()) // verifica cada cliente en la lista
		{
			if (cliente.obtenerCorreoElectronico() == correo && cliente.obtenerContrasena() == contrasena)
			{
				cout << "Inicio de sesion exitoso. Bienvenido, " << cliente.obtenerNombre() << "!" << endl;
				return &cliente;
			}
		}
		cout << "Aun no ha creado cuenta o" << endl;
		cout << "correo o contrasena incorrectos. Vuelva a intentarlo." << endl;
		return nullptr;
	}

	// crea un nuevo perfil de cliente
	void crearPerfil()
	{
		registrarCliente(listaCliente); // registra y guarda al nuevo cliente
		saveFileCliente();
		cout << "Perfil creado exitosamente." << endl;
	}

	// muestra el men� inicial para iniciar sesi�n o crear un perfil
	Cliente* menuInicial()
	{
		Cliente* clienteActivo = nullptr;
		int opcionC;

		while (clienteActivo == nullptr) {
			cout << "=============================" << endl;
			cout << "        INICIO DE SESION        " << endl;
			cout << "=============================" << endl;
			cout << "1. Iniciar sesion" << endl;
			cout << "2. Crear perfil" << endl;
			cout << "Ingrese su opcion: ";
			cin >> opcionC;

			switch (opcionC)
			{
			case 1:
				clienteActivo = iniciarSesion(); // intenta iniciar sesi�n
				break;
			case 2:
				system("cls");
				crearPerfil(); // crea un nuevo perfil
				clienteActivo = &listaCliente.obtener().back(); // asigna el cliente reci�n creado como activo
				break;
			default:
				cout << "Ingrese una opcion valida." << endl;
				break;
			}
		}

		bienvenida(clienteActivo->obtenerNombre()); // muestra bienvenida al cliente activo
		return clienteActivo;
	}

	// inicializa los archivos de pel�culas y clientes
	bool init()
	{
		return loadFilePelicula("ListaPeliculas.txt") && loadFileCliente("ListaClientes.txt");
	}

	// muestra la lista de favoritos del cliente
	void mostrarFavoritos() {
		favoritos.mostrarFavoritos();
	}

	// muestra la lista de reproducci�n del cliente y reproduce la siguiente pel�cula
	void mostrarListaReproduccion() {
		listaReproduccion.mostrarCola();
		listaReproduccion.reproducirSiguiente();
	}

	// muestra un submen� con opciones adicionales para la pel�cula
	void mostrarSubmenuPelicula(Pelicula& pelicula, ColaReproduccion& listaReproduccion, HashTable& favoritos)
	{
		cout << "Opciones:" << endl;
		cout << "Enter - Reproducir" << endl;
		cout << "Q - Agregar a Lista de Reproduccion" << endl;
		cout << "F - Agregar a Favoritos" << endl;
		cout << "Presione una tecla para seleccionar una opcion..." << endl;
		cout << endl;

		char opcion = _getch();
		switch (opcion)
		{
		case 13: // reproducir la pel�cula seleccionada
			pelicula.reproducirPelicula(pelicula.obtenerTitulo(), pelicula.obtenerDuracion());
			Console::Clear;
			break;

		case 'q':
		case 'Q': // agregar a la cola de reproducci�n
			listaReproduccion.agregarACola(pelicula);
			Console::Clear;
			break;

		case 'f':
		case 'F': // agregar a la lista de favoritos
			favoritos.agregarAFavoritos(pelicula);
			Console::Clear;
			break;

		default:
			cout << "Opcion no valida." << endl;
			break;
		}
	}

	// funci�n principal para ejecutar la aplicaci�n
	void run()
	{
		if (!init()) { // verifica que los archivos se carguen correctamente
			cout << "Error al cargar los archivos de peliculas o clientes." << endl;
			return;
		}

		Mostrar_LogoUPC(); 
		Imprimir_Netflix(); 
		Cliente* cliente = menuInicial(); // muestra el men� inicial para iniciar sesi�n o crear un perfil
		system("cls");

		int eleccion = 0;
		vector<Pelicula> contenidos = listaPelicula.obtener();

		do {
			// muestra el men� principal
			cout << "=============================" << endl;
			cout << "       MENU PRINCIPAL       " << endl;
			cout << "=============================" << endl;
			cout << "1. Listar todas las peliculas" << endl;
			cout << "2. Buscar una pelicula por titulo" << endl;
			cout << "3. Filtrar por genero (mejor pelicula de cada genero)" << endl;
			cout << "4. Creditos" << endl;
			cout << "5. Salir" << endl;
			cout << "Ingrese su eleccion: ";
			cin >> eleccion;

			switch (eleccion)
			{
			case 1:
				system("cls");
				cout << "===================================" << endl;
				cout << "  Lista de peliculas (sin ordenar)  " << endl;
				cout << "===================================" << endl;
				listaPelicula.imprimirContenidos(contenidos); // muestra todas las pel�culas
				cout << endl << endl;
				break;

			case 2: {
				// busca una pel�cula por su t�tulo
				system("cls");
				string titulo;
				cout << "Buscar pelicula: ";
				cin.ignore();
				getline(cin, titulo);

				int indice = busqueda.buscarPorTitulo(contenidos, titulo); // busca la pel�cula por t�tulo
				if (indice != NOT_FOUND) {
					Pelicula& peliculaEncontrada = contenidos[indice];
					cout << endl;
					cout << "==============================" << endl;
					cout << "Pelicula encontrada:" << endl;
					cout << "Titulo: " << peliculaEncontrada.obtenerTitulo() << endl;
					cout << "Genero: " << peliculaEncontrada.obtenerGenero() << endl;
					cout << "Duracion: " << peliculaEncontrada.obtenerDuracion() << " minutos" << endl;
					cout << "Director: " << peliculaEncontrada.obtenerDirector()->obtenerNombre() << endl;
					cout << "Actores: ";
					for (const auto& actor : peliculaEncontrada.obtenerActores())
					{
						cout << actor->obtenerNombre() << ", ";
					}
					cout << endl;
					cout << "Anio: " << peliculaEncontrada.obtenerFechaEstreno() << endl;
					cout << "Calificacion: " << peliculaEncontrada.obtenerCalificacion() << endl;
					cout << "==============================" << endl;

					mostrarSubmenuPelicula(peliculaEncontrada, listaReproduccion, favoritos); // muestra el submen�
				}
				else
				{
					cout << "Pelicula no encontrada. Intente de nuevo." << endl;
				}
				break;
			}

			case 3: {
				// filtra y muestra la mejor pel�cula por g�nero
				system("cls");
				string genero;
				cout << "Ingrese el genero que desea buscar: ";
				cin.ignore();
				getline(cin, genero);

				int indiceMejorPelicula = busqueda.buscarMejorPorGenero(contenidos, genero);
				if (indiceMejorPelicula != NOT_FOUND)
				{
					Pelicula mejorPelicula = contenidos[indiceMejorPelicula];
					cout << "=============================================" << endl;
					cout << "La mejor pelicula de genero " << genero << " es:" << endl;
					cout << "=============================================" << endl;
					cout << "Titulo: " << mejorPelicula.obtenerTitulo() << endl;
					cout << "Calificacion: " << mejorPelicula.obtenerCalificacion() << endl;
					mostrarSubmenuPelicula(mejorPelicula, listaReproduccion, favoritos);
				}
				else {
					cout << "No se encontraron peliculas de ese genero." << endl;
				}
				break;
			}

			case 4:
				system("cls");
				Mostrar_Creditos(); // muestra los cr�ditos de la aplicaci�n
				break;

			case 5:
				cout << "Saliendo..." << endl;
				break;

			default:
				cout << "Opcion no valida. Intente de nuevo." << endl;
				break;
			}
		} while (eleccion != 5);
	}
};
