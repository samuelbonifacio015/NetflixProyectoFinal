#pragma once
#include <iostream>
#include <conio.h>
#include <algorithm>
#include <string>
#include <istream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <locale.h>
#define COLUMNAS 52
#define FILAS 40


using namespace std;
using namespace System;

/*short MenuNetflix() {
	short op;
	do {
		cout << " Menu de Opciones " << endl;
		cout << "1.- Mostrar Lista de Peliculas Disponibles" << endl;
		cout << "2.- Mostrar Detalles de una Pelicula " << endl;
		cout << "3.- Historial de Visualizacion " << endl;
		cout << "4.- Mostrar Creditos " << endl;
		cout << "5.- Salir " << endl;
		cout << " Ingrese opcion: "; std::cin >> op;
	} while (op < 1 || op > 5);
	return op;
}
*/

void Mostrar_LogoUPC() {
	int tecla = 0;
	system("color 7C"); 	cout << R"(  
                                                   
                                                   
                                                                                                     
                                                    
                       .;.                          
                     .dKx.                          
            ..      ;0WWd.            ..            
          .l:.     ,0MMM0,             ;l'          
         :Ol       oWMMMW0d:.           lOc         
        lXO.      .xMMMMMMMNO:.         .kNl.       
       :XWd        lWMMMMMMMMWk'         oWXc       
      .OMWo        .OWMMMMMMMMWO'        lWMO'      
      :XMMx.        'kWMMMMMMMMWo       .xWMNc      
      lNMMX:         .c0WMMMMMMMx.      ;KMMWl      
      cNMMM0,          .cKWWMMMWd.     'OMMMNl      
      ,KMMMM0:           ,d0MMMK;     ;0WMMMK;      
      .dWMMMMNx,          .oWMKc    ,xNMMMMWd.      
       .kWMMMMMNOl,.     ..dXk, .'ckNMMMMMWO'       
        'kWMMMMMMMN0xoc::ok0Odox0NMMMMMMMWO'        
         .oXMMMMMMMMMMMMWMMMMMMMMMMMMMMMXo.         
           'dXWMMMMMMMMMMMMMMMMMMMMMMMXx,           
             .lOXWMMMMMMMMMMMMMMMMMNOl'             
                .:ok0XNWWWWWWNX0ko:'                
                    ..',,,,,,'..                                                 
)" << endl;

	Console::SetCursorPosition(FILAS / 2 - 2, 26);
	cout << "(Presione Enter para Continuar)";

	while (true) {
		if (_kbhit()) {
			tecla = getch();
			if (tecla == 13) {
				tecla = 0;
				break;
			}
		}
	}
	fflush(stdin); 	system("color 0F");
	system("cls");
}

void Imprimir_Netflix() {
	int tecla = 0;
	system("color 0C"); 	cout << R"(
 

 ###############          %#############
 %###############         ##############%
 %###############         ##############%
 %################        ##############%
 %#%###############       ##############%
 %##%##############       ##############%
 %##%%##############      ##############%
 %###%##############      ##############%
 %###%%##############     ##############%
 %####%%##############    ##############%
 %####%%##############    ##############%
 %#####%%##############   %#############%
 %#####%%%##############  %%############%
 %#####%%%##############  %%############%
 %######%%%############## %%%###########%
 %######%%%###############%%%%##########%
 %#######%%%##############%%%%##########%
 %#######%%%%#############%%%%%#########%
 %########%%%##############%%%%#########%
 %########%%%%##############%%%%########%
 %#########%%%%#############%%%%########%
 %#########%%%%##############%%%%#######%
 %##########%%%%##############%%%#######%
 %##########%%%%##############%%%%######%
 %###########%%% ##############%%%######%
 %###########%%% ###############%%######%
 %############%%  ##############%%%#####%
 %##############   ##############%%#####%
 %##############   ###############%%####%
 %##############    ##############%%####%
 %##############     ##############%%###%
 %##############     ##############%%###%
 %##############      ##############%%##%
 %##############       ##############%##%
 %##############       ##############%%#%
 %##############        ##############%#%
 %##############         ###############%
 %##############         ###############%
 %###%%%                          ######%

)" << endl;


	while (true) {
		if (_kbhit()) {
			tecla = getch();
			if (tecla == 13) {
				tecla = 0;
				break;
			}
		}
	}
	fflush(stdin); 	system("color 0F");
	system("cls");

}

int OpcionesFiltrado() {
	Console::Clear();
	int opFiltrar;
	do {
		cout << "Opciones de filtrado:" << endl;
		cout << "1. Filtrar por calificacion" << endl;
		cout << "2. Filtrar por duracion" << endl;
		cout << "3. Filtrar por genero" << endl;
		cout << "4. Volver al menu principal" << endl;
		cout << "Ingrese su opcion: ";
		cin >> opFiltrar;
	} while (opFiltrar < 1 || opFiltrar > 4);
	return opFiltrar;
}

void Desplazarse(int x, int y, bool visible) {
	Console::SetCursorPosition(y, x);
	(visible) ? cout << ">" : cout << ' ';
}
void GoBack() {
	int tecla = 0;
	Console::SetCursorPosition(0, 0);
	do {
		if (kbhit()) tecla = getch();
	} while (tecla != 27);
}

void Iniciar_Arreglos_Creditos(int**& pCreditos) {
	pCreditos = new int* [FILAS];

	for (int i = 0; i < FILAS; i++)pCreditos[i] = new int[COLUMNAS];

	for (int i = 0; i < FILAS; i++) {
		for (int j = 0; j < COLUMNAS; j++) {
			pCreditos[i][j] = 0;
		}
	}

		for (int i = 0; i < FILAS; i++) {
		for (int j = 0; j < COLUMNAS; j++) {
			if (i == 0 || i == FILAS - 1 || j == 0 || j == COLUMNAS - 1) pCreditos[i][j] = 1;
		}
	}

		pCreditos[8][8] = 3; pCreditos[8][9] = 3;
	pCreditos[8][11] = 3; pCreditos[8][12] = 3;
	pCreditos[8][15] = 3; pCreditos[8][16] = 3;
	pCreditos[8][18] = 3; pCreditos[8][19] = 3;
	pCreditos[8][22] = 3; pCreditos[8][24] = 3;
	pCreditos[8][25] = 3; pCreditos[8][26] = 3;
	pCreditos[8][29] = 3; pCreditos[8][32] = 3;
	pCreditos[8][33] = 3; pCreditos[8][34] = 3;
	pCreditos[9][7] = 3; pCreditos[9][11] = 3;
	pCreditos[9][13] = 3; pCreditos[9][15] = 3;
	pCreditos[9][18] = 3; pCreditos[9][20] = 3;
	pCreditos[9][22] = 3; pCreditos[9][25] = 3;
	pCreditos[9][28] = 3; pCreditos[9][30] = 3;
	pCreditos[9][32] = 3;
	pCreditos[10][7] = 3; pCreditos[10][11] = 3;
	pCreditos[10][12] = 3; pCreditos[10][15] = 3;
	pCreditos[10][16] = 3; pCreditos[10][11] = 3;
	pCreditos[10][18] = 3; pCreditos[10][20] = 3;
	pCreditos[10][22] = 3; pCreditos[10][25] = 3;

	pCreditos[10][28] = 3; pCreditos[10][30] = 3;
	pCreditos[10][32] = 3; pCreditos[10][33] = 3;
	pCreditos[10][34] = 3; pCreditos[11][7] = 3;
	pCreditos[11][11] = 3; pCreditos[11][13] = 3;
	pCreditos[11][15] = 3; pCreditos[11][18] = 3;
	pCreditos[11][20] = 3; pCreditos[11][22] = 3;
	pCreditos[11][25] = 3; pCreditos[11][28] = 3;
	pCreditos[11][30] = 3; pCreditos[11][34] = 3;
	pCreditos[12][9] = 3; pCreditos[12][11] = 3;
	pCreditos[12][13] = 3; pCreditos[12][15] = 3;
	pCreditos[12][16] = 3; pCreditos[12][18] = 3;
	pCreditos[12][19] = 3; pCreditos[12][22] = 3;
	pCreditos[12][25] = 3; pCreditos[12][29] = 3;
	pCreditos[12][32] = 3; pCreditos[12][33] = 3;
	pCreditos[12][34] = 3;	pCreditos[12][8] = 3;

}


void Mostrar_Creditos() {
	int** pCreditos;
	Iniciar_Arreglos_Creditos(pCreditos);
	Console::Clear();

	for (int i = 0; i < FILAS; i++) {
		for (int j = 0; j < COLUMNAS; j++) {
			if (pCreditos[i][j] == 1) {
				Console::ForegroundColor = ConsoleColor::Yellow;
				cout << (char)219;
			}
			else if (pCreditos[i][j] == 3) {
				Console::ForegroundColor = ConsoleColor::White;
				cout << "@";
			}
			else if (i == 16) {
				if (j == 14) cout << "DESARROLLADO POR:        ";
				else if (j < 27) cout << ' ';
			}
			else if (i == 19) {
				if (j == 14) cout << "x Samuel Bonifacio      ";
				else if (j < 27) cout << ' ';
			}
			else if (i == 21) {
				if (j == 14) cout << "x Luis Tufi�o           ";
				else if (j < 27) cout << ' ';
			}
			else if (i == 23) {
				if (j == 14) cout << "x Jefferson         ";
				else if (j < 27) cout << ' ';
			}

			else if (i == 25) {
				if (j == 8) cout << "PRESIONE 'ESC' PARA REGRESAR AL MENU ";
				else if (j < 15) cout << ' ';
			}

			else {
				cout << ' ';
			}
		}
		cout << endl;
	}
	GoBack();
}

