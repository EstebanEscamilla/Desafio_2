#include <iostream>
#include "Jugador.h" // Solo se incluira jugador.h ya que dentro de el esta Estadistica.h

using namespace std;

int main() {
    cout << "--- LABORATORIO DE PRUEBAS: CLASE JUGADOR ---" << endl;

    // 1. CREAR EL JUGADOR usando el 2do constructor
    Jugador* elBicho = new Jugador("Cristiano", "Ronaldo", 7);

    cout << "\nFichaje confirmado: " << elBicho->getNombreCompleto() << " (Camiseta #" << elBicho->getNumCamiseta() << ")" << endl;

    // 2. Verificar antes del inicio del mundial
    cout << "Goles antes del Mundial: " << elBicho->getStats()->getGoles() << endl;

    // 3. SIMULAR UN PARTIDO
    // Se le suman goles y minutos provenientes de un partido
    cout << "\nSimulando partido de fase de grupos..." << endl;
    elBicho->actualizarEstadisticasJugador(2, 1, 0, 0, 90);

    // 4. CONSULTAR DATOS ACTUALIZADOS
    cout << "Goles despues del partido: " << elBicho->getStats()->getGoles() << endl;
    cout << "Asistencias totales: " << elBicho->getStats()->getAsistencias() << endl;
    cout << "Minutos jugados: " << elBicho->getStats()->getMinutos() << endl;

    delete elBicho;

    cout << "\nPrueba exitosa. Jugador y libreta eliminados de la RAM." << endl;

    return 0;
}
