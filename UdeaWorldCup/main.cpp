#include <iostream>
#include "Equipo.h"
#include "Jugador.h"

using namespace std;

int main() {
    cout << "--- LABORATORIO DE PRUEBAS: CLASE EQUIPO ---" << endl;

    // 1. CREAR EL EQUIPO
    Equipo* colombia = new Equipo("Colombia", "Nestor Lorenzo", 12, "CONMEBOL");

    cout << "\nEquipo creado: " << colombia->getNombrePais() << endl;
    cout << "Ranking inicial: " << colombia->getRankingFIFA() << endl;

    // 2. CREAR JUGADORES Y AGREGARLOS AL EQUIPO
    Jugador* j1 = new Jugador("Luis", "Diaz", 7);
    Jugador* j2 = new Jugador("James", "Rodriguez", 10);

    colombia->agregarJugador(j1);
    colombia->agregarJugador(j2);

    cout << "\nJugadores inscritos exitosamente." << endl;

    // 3. SIMULAR UN PARTIDO (Ejemplo: Colombia 2 - 1 Brasil)
    colombia->actualizarResultadosEquipo(2, 1, 3);
    colombia->getJugador(0)->actualizarEstadisticasJugador(2, 0, 0, 0, 90); //Luis dias esta en la posicion 0
    colombia->getJugador(1)->actualizarEstadisticasJugador(0, 1, 0, 0, 85); // james en la posicion 1

    // 4. MOSTRAR RESULTADOS GENERALES
    cout << "\n--- ESTADO DE LA TABLA ---" << endl;
    cout << "Pais: " << colombia->getNombrePais() << " | Puntos: " << colombia->getPuntosFaseGrupos() << endl;
    cout << "Goles a Favor: " << colombia->getGolesFavor() << " | Goles en Contra: " << colombia->getGolesContra() << endl;

    cout << "\n--- ESTADO DE LOS JUGADORES ---" << endl;
    // Triple flecha: Equipo -> Jugador -> Estadistica -> Goles
    cout << "Goles de " << colombia->getJugador(0)->getNombreCompleto() << ": "
         << colombia->getJugador(0)->getStats()->getGoles() << endl;

    cout << "Asistencias de " << colombia->getJugador(1)->getNombreCompleto() << ": "
         << colombia->getJugador(1)->getStats()->getAsistencias() << endl;

    // 5. LA LIMPIEZA
    cout << "\nEjecutando limpieza de memoria..." << endl;
    delete colombia;

    cout << "Memoria liberada correctamente." << endl;

    return 0;
}
