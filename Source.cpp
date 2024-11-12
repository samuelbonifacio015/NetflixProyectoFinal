#include "ArbolBinario.h"
#include "Recursos.h"
#include "BusquedaBinaria.h"
#include "App.h"

using namespace std;

int main()
{
    Console::SetWindowSize(COLUMNAS, FILAS);
    Console::CursorVisible = false;

    App* app = new App();

    if (app->init())
    {
        app->run();
    }
}