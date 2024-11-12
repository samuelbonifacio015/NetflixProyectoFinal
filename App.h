#pragma once  
#include "Archivo.h"
#include "BusquedaBinaria.h"
#include "Recursos.h"
#include "Ordenador.h"
#include "HashTable.h"
#include "ColaReproduccion.h"
#include "Cliente.h"
#include "Suscripcion.h" // nueva clase de suscripcion
#include "Grafos.h"
#include <conio.h>

class App
{
private:
    Lista<Pelicula> listaPelicula;              // lista de peliculas
    FileHandler FileHandler;                    // manejador de archivos
    Ordenador<Pelicula> ordenador;              // ordenamiento de peliculas
    BinarySearchPelicula<Pelicula> busqueda;    // busqueda binaria para peliculas
    HashTable favoritos;                        // tabla hash para favoritos
    Lista<Cliente> listaCliente;                // lista de clientes
    ColaReproduccion listaReproduccion;         // cola de reproduccion
    Lista<Suscripcion> listaSuscripciones;      // lista de suscripciones

public:
    bool loadFilePelicula(const string& file_url) {
        FileHandler.setFileURL(file_url);
        return FileHandler.loadFilePelicula(listaPelicula);
    }

    void saveFilePelicula() {
        FileHandler.saveFilePelicula(listaPelicula);
    }

    bool loadFileCliente(const string& file_url) {
        FileHandler.setFileURL(file_url);
        return FileHandler.loadFileCliente(listaCliente);
    }

    void saveFileCliente() {
        FileHandler.saveFileCliente(listaCliente);
    }

    // registra un nuevo cliente y lo guarda en el archivo
    void registrarCliente(Lista<Cliente>& lista) {
        int id;
        string nombre, telefono, correoElectronico, contrasena;

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

    // muestra mensaje de bienvenida
    void bienvenida(const string& nombreCliente) {
        cout << "===========================================" << endl;
        cout << "            BIENVENIDO                   " << endl;
        cout << "===========================================" << endl;
        cout << " Hola, " << nombreCliente << "!" << endl;
        cout << " ¡Nos alegra tenerte con nosotros!" << endl;
        cout << "===========================================" << endl;
        cout << " ¡Disfruta de tu experiencia! " << endl;
        cout << "===========================================" << endl;
    }

    // inicia sesion del cliente solicitando correo y contrasena
    Cliente* iniciarSesion() {
        string correo, contrasena;
        cout << "Ingrese su correo electronico: ";
        cin >> correo;
        cout << "Ingrese su contrasena: ";
        cin >> contrasena;

        for (Cliente& cliente : listaCliente.obtener()) {
            if (cliente.obtenerCorreoElectronico() == correo && cliente.obtenerContrasena() == contrasena) {
                cout << "Inicio de sesion exitoso. Bienvenido, " << cliente.obtenerNombre() << "!" << endl;
                return &cliente;
            }
        }
        cout << "Correo o contrasena incorrectos." << endl;
        return nullptr;
    }

    // crea un perfil de cliente nuevo
    void crearPerfil() {
        registrarCliente(listaCliente);
        saveFileCliente();
        cout << "Perfil creado exitosamente." << endl;
    }

    // menu inicial para iniciar sesion o crear perfil
    Cliente* menuInicial() {
        Cliente* clienteActivo = nullptr;
        int opcion;

        while (clienteActivo == nullptr) {
            cout << "=============================" << endl;
            cout << "        INICIO DE SESION        " << endl;
            cout << "=============================" << endl;
            cout << "1. Iniciar sesion" << endl;
            cout << "2. Crear perfil" << endl;
            cout << "Ingrese su opcion: ";
            cin >> opcion;

            switch (opcion) {
            case 1:
                clienteActivo = iniciarSesion();
                break;
            case 2:
                crearPerfil();
                clienteActivo = &listaCliente.obtener().back();
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
                break;
            }
        }

        bienvenida(clienteActivo->obtenerNombre());
        return clienteActivo;
    }

    // muestra un submenu con opciones adicionales para la pelicula
    void mostrarSubmenuPelicula(Pelicula& pelicula, ColaReproduccion& listaReproduccion, HashTable& favoritos) {
        cout << "Opciones:" << endl;
        cout << "Enter - Reproducir" << endl;
        cout << "Q - Agregar a Lista de Reproduccion" << endl;
        cout << "F - Agregar a Favoritos" << endl;
        cout << "Presione una tecla para seleccionar una opcion..." << endl;

        char opcion = _getch();
        switch (opcion) {
        case 13: // reproducir
            pelicula.reproducirPelicula(pelicula.obtenerTitulo(), pelicula.obtenerDuracion());
            Console::Clear;
            break;
        case 'q':
        case 'Q': // agregar a cola
            listaReproduccion.agregarACola(pelicula);
            Console::Clear;
            break;
        case 'f':
        case 'F': // agregar a favoritos
            favoritos.agregarAFavoritos(pelicula);
            Console::Clear;
            break;
        default:
            cout << "Opcion no valida." << endl;
            break;
        }
    }

    // inicia la aplicacion
    void run() {
        Mostrar_LogoUPC();
        Imprimir_Netflix();
        Cliente* cliente = menuInicial();
        system("cls");

        int eleccion = 0;
        vector<Pelicula> contenidos = listaPelicula.obtener();

        do {
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

            switch (eleccion) {
            case 1:
                system("cls");
                listaPelicula.imprimirContenidos(contenidos);
                break;
            case 2:
                buscarPeliculaPorTitulo(busqueda, contenidos);
                break;
            case 3:
                filtrarPorGenero(busqueda, contenidos);
                break;
            case 4:
                system("cls");
                Mostrar_Creditos();
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
