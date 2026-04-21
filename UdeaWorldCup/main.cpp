#include <iostream>
#include "Grupo.h"
#include "Equipo.h"
#include "Jugador.h"

using namespace std;

int main() {
    cout << "--- PRUEBA DE FUEGO ---" << endl;

    // Creamos el Grupo A
    Grupo* grupoA = new Grupo('A');

    // Creamos un par de equipos para meter al grupo
    Equipo* e1 = new Equipo("Argentina", "Lionel Scaloni", 1, "CONMEBOL");
    Equipo* e2 = new Equipo("Francia", "Didier Deschamps", 2, "UEFA");

    // Agregamos un jugador
    Jugador* messi = new Jugador("Lionel", "Messi", 10);
    e1->agregarJugador(messi);

    // Metemos los equipos al grupo
    grupoA->agregarEquipo(e1);
    grupoA->agregarEquipo(e2);

    cout << "\nGrupo " << grupoA->getLetra() << " creado con "
         << grupoA->getCantidadEquiposRegistrados() << " equipos." << endl;

    //PRUEBA DE NAVEGACIÓN (La "Cuádruple Flecha")
    cout << "Goles iniciales del 10 de " << grupoA->getEquipo(0)->getNombrePais() << ": "
         << grupoA->getEquipo(0)->getJugador(0)->getStats()->getGoles() << endl;

    // 6. LA LIMPIEZA
    cout << "\nBorrando el grupo..." << endl;
    delete grupoA;

    cout << "¡Sistema limpio!" << endl;

    return 0;
}
