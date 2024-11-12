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
	// atributos principales de la aplicación
	Lista<Pelicula> listaPelicula;               // lista de todas las películas disponibles
	FileHandler FileHandler;                     // manejador de archivos
	Ordenador<Pelicula> ordenador;               // clase para ordenar películas
	BinarySearchPelicula<Pelicula> busqueda;     // clase para búsqueda binaria de películas
	HashTable favoritos;                         // tabla hash para almacenar películas favoritas
	Lista<Cliente> listaCliente;                 // lista de clientes registrados
	ColaReproduccion listaReproduccion;          // cola de reproducción de películas
	Lista<Suscripcion> listaSuscripcion;         // lista de suscripciones

public:
	// carga las películas desde el archivo
	bool loadFilePelicula(const string& file_url)
	{
		FileHandler.setFileURL(file_url);
		return FileHandler.loadFilePelicula(listaPelicula);
	}

	// guarda las películas en el archivo
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
		cout << "¡Nos alegra tenerte con nosotros!" << endl;
		cout << "===========================================" << endl;
		cout << "¡Disfruta de tu experiencia!" << endl;
		cout << "===========================================" << endl;
	}

	// permite al cliente iniciar sesión ingresando correo y contraseña
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

	// muestra el menú inicial para iniciar sesión o crear un perfil
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
				clienteActivo = iniciarSesion(); // intenta iniciar sesión
				break;
			case 2:
				system("cls");
				crearPerfil(); // crea un nuevo perfil
				clienteActivo = &listaCliente.obtener().back(); // asigna el cliente recién creado como activo
				break;
			default:
				cout << "Ingrese una opcion valida." << endl;
				break;
			}
		}

		bienvenida(clienteActivo->obtenerNombre()); // muestra bienvenida al cliente activo
		return clienteActivo;
	}

	// inicializa los archivos de películas y clientes
	bool init()
	{
		return loadFilePelicula("ListaPeliculas.txt") && loadFileCliente("ListaClientes.txt");
	}

	// muestra la lista de favoritos del cliente
	void mostrarFavoritos() {
		favoritos.mostrarFavoritos();
	}

	// muestra la lista de reproducción del cliente y reproduce la siguiente película
	void mostrarListaReproduccion() {
		listaReproduccion.mostrarCola();
		listaReproduccion.reproducirSiguiente();
	}

	// muestra un submenú con opciones adicionales para la película
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
		case 13: // reproducir la película seleccionada
			pelicula.reproducirPelicula(pelicula.obtenerTitulo(), pelicula.obtenerDuracion());
			Console::Clear;
			break;

		case 'q':
		case 'Q': // agregar a la cola de reproducción
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

	// función principal para ejecutar la aplicación
	void run()
	{
		if (!init()) { // verifica que los archivos se carguen correctamente
			cout << "Error al cargar los archivos de peliculas o clientes." << endl;
			return;
		}

		Mostrar_LogoUPC(); 
		Imprimir_Netflix(); 
		Cliente* cliente = menuInicial(); // muestra el menú inicial para iniciar sesión o crear un perfil
		system("cls");

		int eleccion = 0;
		vector<Pelicula> contenidos = listaPelicula.obtener();

		do {
			// muestra el menú principal
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
				listaPelicula.imprimirContenidos(contenidos); // muestra todas las películas
				cout << endl << endl;
				break;

			case 2: {
				// busca una película por su título
				system("cls");
				string titulo;
				cout << "Buscar pelicula: ";
				cin.ignore();
				getline(cin, titulo);

				int indice = busqueda.buscarPorTitulo(contenidos, titulo); // busca la película por título
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

					mostrarSubmenuPelicula(peliculaEncontrada, listaReproduccion, favoritos); // muestra el submenú
				}
				else
				{
					cout << "Pelicula no encontrada. Intente de nuevo." << endl;
				}
				break;
			}

			case 3: {
				// filtra y muestra la mejor película por género
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
				Mostrar_Creditos(); // muestra los créditos de la aplicación
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
