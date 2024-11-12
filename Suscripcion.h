#pragma once
#include "Recursos.h"

using namespace std;

class Suscripcion {
public:
    string plan;          // nombre del plan (por ejemplo, "basico", "estandar", "premium")
    double costo;         // costo del plan
    int duracion;         // duracion del plan en meses

    // constructor por defecto
    Suscripcion() : plan(""), costo(0.0), duracion(0) {}

    // constructor parametrizado
    Suscripcion(string plan, double costo, int duracion)
        : plan(plan), costo(costo), duracion(duracion) {}

    // obtiene el nombre del plan
    string obtenerPlan() const { return plan; }

    // obtiene el costo del plan
    double obtenerCosto() const { return costo; }

    // obtiene la duracion del plan en meses
    int obtenerDuracion() const { return duracion; }

    // muestra los detalles de la suscripcion
    void mostrarDetallesSuscripcion() const {
        cout << "plan: " << plan << endl;
        cout << "costo: S/" << costo << " por " << duracion << " meses" << endl;
    }
};
