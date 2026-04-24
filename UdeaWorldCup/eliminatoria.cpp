#include "eliminatoria.h"
#include <iostream>

using namespace std;

Eliminatoria::Eliminatoria() {
    // 2. INICIALIZACIÓN CON MEMORIA DINÁMICA (Cumpliendo el requisito estricto)
    ronda32 = new Equipo*[32];
    ronda16 = new Equipo*[16];
    cuartos = new Equipo*[8];
    semis = new Equipo*[4];
    finalTorneo = new Equipo*[2];
    campeon = nullptr;

    partidosFaseActual = nullptr;
    cantidadPartidosActual = 0;
}

Eliminatoria::~Eliminatoria() {
    // Limpieza estricta para evitar fugas de memoria
    delete[] ronda32;
    delete[] ronda16;
    delete[] cuartos;
    delete[] semis;
    delete[] finalTorneo;
    limpiarPartidos();
}

void Eliminatoria::limpiarPartidos() {
    if (partidosFaseActual != nullptr) {
        for (int i = 0; i < cantidadPartidosActual; ++i) {
            delete partidosFaseActual[i]; // Borramos cada objeto partido
        }
        delete[] partidosFaseActual; // Borramos el arreglo de punteros
        partidosFaseActual = nullptr;
    }
}

void Eliminatoria::cargarClasificados(Equipo** clasificados) {
    for (int i = 0; i < 32; ++i) {
        ronda32[i] = clasificados[i];
    }
}

void Eliminatoria::simularRonda32() {
    cout << "\n=== INICIANDO DIECISEISAVOS DE FINAL (R16) ===" << endl;
    cantidadPartidosActual = 16;
    partidosFaseActual = new Partido*[cantidadPartidosActual];

    int indiceGanadores = 0;

    // Los cruces dependen del fixture. Aquí se hace secuencial como ejemplo.
    // Deberás ajustar el emparejamiento según la regla del punto III.b
    for (int i = 0; i < 32; i += 2) {
        // 3. SE CREA EL OBJETO PARTIDO
        // El documento exige fecha "10 07 2026" para estas etapas
        char fecha[] = "10 07 2026";
        partidosFaseActual[i/2] = new Partido(ronda32[i], ronda32[i+1], fecha, true);

        // La simulación matemática, los 11 jugadores, y el desempate (120 min)
        // deben ocurrir DENTRO de este método simular() de la clase Partido.
        partidosFaseActual[i/2]->simular(); // true indica que es eliminatoria (hay desempate)

        ronda16[indiceGanadores] = partidosFaseActual[i/2]->getGanador();
        indiceGanadores++;
    }
}
