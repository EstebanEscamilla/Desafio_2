#include "partido.h"
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

// Constantes matemáticas del enunciado [cite: 92]
const double MU = 1.35;
const double ALPHA = 0.6;
const double BETA = 0.4;

// CONSTRUCTOR
Partido::Partido(Equipo* local, Equipo* visitante, const char* _fecha, bool _esEliminatoria) {
    this->equipoLocal = local;
    this->equipoVisitante = visitante;
    this->esEliminatoria = _esEliminatoria;
    this->ganador = nullptr;

    this->golesLocal = 0;
    this->golesVisitante = 0;
    this->posesionLocal = 50.0;
    this->posesionVisitante = 50.0;

    // 1. Asignación de textos exigidos por el enunciado [cite: 85]
    this->fecha = new char[strlen(_fecha) + 1];
    strcpy(this->fecha, _fecha);

    const char* defaultHora = "00:00";
    this->hora = new char[strlen(defaultHora) + 1];
    strcpy(this->hora, defaultHora);

    const char* defaultSede = "nombreSede";
    this->sede = new char[strlen(defaultSede) + 1];
    strcpy(this->sede, defaultSede);

    // Asignación de los 3 árbitros (arreglos dinámicos) [cite: 85]
    this->arbitros = new char*[3];
    const char* nombresArbitros[3] = {"codArbitro1", "codArbitro2", "codArbitro3"};
    for (int i = 0; i < 3; i++) {
        this->arbitros[i] = new char[strlen(nombresArbitros[i]) + 1];
        strcpy(this->arbitros[i], nombresArbitros[i]);
    }

    // Inicializar arreglos de alineación (11 jugadores)
    this->alineacionLocal = new Jugador*[11];
    this->alineacionVisitante = new Jugador*[11];
    for (int i = 0; i < 11; i++) {
        this->alineacionLocal[i] = nullptr;
        this->alineacionVisitante[i] = nullptr;
    }
}

// DESTRUCTOR (Limpiar la memoria del partido)
Partido::~Partido() {
    delete[] this->fecha;
    delete[] this->hora;
    delete[] this->sede;

    for (int i = 0; i < 3; i++) {
        delete[] this->arbitros[i];
    }
    delete[] this->arbitros;

    // NOTA CLAVE: Solo borramos el arreglo, NO los jugadores por dentro,
    // porque los jugadores le pertenecen a la clase Equipo.
    delete[] this->alineacionLocal;
    delete[] this->alineacionVisitante;
}

// ALGORITMO DE SELECCIÓN ALEATORIA DE 11 JUGADORES [cite: 93]
void Partido::elegirAlineaciones() {
    // Truco: Llenar un arreglo con indices del 0 al 25 y desordenarlo (Fisher-Yates)
    int indicesL[26];
    int indicesV[26];
    for(int i = 0; i < 26; i++) {
        indicesL[i] = i;
        indicesV[i] = i;
    }

    // Mezclar
    for(int i = 25; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = indicesL[i]; indicesL[i] = indicesL[j]; indicesL[j] = temp;

        int k = rand() % (i + 1);
        temp = indicesV[i]; indicesV[i] = indicesV[k]; indicesV[k] = temp;
    }

    // Tomar los primeros 11 [cite: 93]
    for(int i = 0; i < 11; i++) {
        this->alineacionLocal[i] = this->equipoLocal->getJugador(indicesL[i]);
        this->alineacionVisitante[i] = this->equipoVisitante->getJugador(indicesV[i]);
    }
}

// MODELO PREDICTIVO SIMPLE PARA POSESIÓN (Proporcional al Ranking FIFA)
// Lógica: Un ranking más BAJO (ej. 1) es MEJOR.
// Invertimos el peso para que el mejor tenga más posesión.
void Partido::calcularPosesion() {
    double rankL = (double)this->equipoLocal->getRankingFIFA();
    double rankV = (double)this->equipoVisitante->getRankingFIFA();

    double totalInverso = (1.0 / rankL) + (1.0 / rankV);

    this->posesionLocal = ((1.0 / rankL) / totalInverso) * 100.0;
    this->posesionVisitante = ((1.0 / rankV) / totalInverso) * 100.0;
}

// ECUACIÓN DE POISSON / GOLES ESPERADOS [cite: 88, 89]
int Partido::calcularGolesEsperados(Equipo* atacante, Equipo* defensor) {
    double gfA = atacante->getPromedioGolesFavorHistorico();
    double gcB = defensor->getPromedioGolesContraHistorico();

    // Evitar divisiones por cero si hay equipos sin historial
    if (gfA <= 0) gfA = 0.1;
    if (gcB <= 0) gcB = 0.1;

    double lambda = MU * pow((gfA / MU), ALPHA) * pow((gcB / MU), BETA);

        // Retornamos redondeado al entero más cercano como tope máximo
        return (int)round(lambda);
}

// EL MOTOR DE SUCESOS POR PROBABILIDADES [cite: 94, 95]
void Partido::simularEventosJugadores(Jugador** alineacion, int golesEsperados, int& golesRealesAnotados, int minutosJugados) {
    golesRealesAnotados = 0;

    for (int i = 0; i < 11; i++) {
        Jugador* j = alineacion[i];
        if (j == nullptr) continue;

        int goles = 0, amarillas = 0, rojas = 0, faltas = 0;

        // 1. Simulación de Faltas (13%, 2.75%, 0.7%)
        if (rand() % 10000 < 1300) { // 13.00%
            faltas++;
            if (rand() % 10000 < 275) { // 2.75%
                faltas++;
                if (rand() % 10000 < 70) { // 0.70%
                    faltas++;
                }
            }
        }

        // 2. Simulación de Tarjetas (6%, 1.15%)
        if (rand() % 10000 < 600) { // 6.00%
            amarillas++;
            if (rand() % 10000 < 115) { // 1.15%
                amarillas++;
                rojas = 1; // Dos amarillas dan una roja automáticamente
            }
        }

        // 3. Simulación de Goles (4% chance por jugador) hasta tope esperado
        // Hacemos múltiples intentos (simulando 90 mins)
        for (int m = 0; m < 5; m++) { // Damos 5 "oportunidades" claras por jugador
            if (golesRealesAnotados < golesEsperados) {
                if (rand() % 10000 < 400) { // 4.00%
                    goles++;
                    golesRealesAnotados++;
                }
            }
        }

        // 4. Actualizamos las estadísticas históricas de este jugador [cite: 48, 53]
        j->actualizarEstadisticasJugador(goles, 0, amarillas, rojas, minutosJugados);
    }
}

// MÉTODO PRINCIPAL QUE ORQUESTA TODO
void Partido::simular() {
    elegirAlineaciones();
    calcularPosesion();

    int lambdaLocal = calcularGolesEsperados(this->equipoLocal, this->equipoVisitante);
    int lambdaVisitante = calcularGolesEsperados(this->equipoVisitante, this->equipoLocal);

    // Tiempo estándar de juego [cite: 94]
    int minutosPartido = 90;

    // Simulamos los eventos individuales (que suman los goles totales)
    simularEventosJugadores(this->alineacionLocal, lambdaLocal, this->golesLocal, minutosPartido);
    simularEventosJugadores(this->alineacionVisitante, lambdaVisitante, this->golesVisitante, minutosPartido);

    // Lógica de desempate si es eliminatoria [cite: 199, 202]
    if (this->esEliminatoria && this->golesLocal == this->golesVisitante) {
        minutosPartido = 120; // Prórroga [cite: 202]

        // Sumar los 30 mins extra a los jugadores
        for(int i=0; i<11; i++) {
            if(alineacionLocal[i] != nullptr) alineacionLocal[i]->actualizarEstadisticasJugador(0,0,0,0,30);
            if(alineacionVisitante[i] != nullptr) alineacionVisitante[i]->actualizarEstadisticasJugador(0,0,0,0,30);
        }

        // Desempate sesgado por Ranking FIFA [cite: 200, 201]
        // Mientras mejor (menor) ranking, más chances.
        double probLocal = this->posesionLocal; // Reusamos la probabilidad del ranking
        if ((rand() % 100) < probLocal) {
            this->golesLocal++;
        } else {
            this->golesVisitante++;
        }
    }

    // Determinar ganador para retornar
    if (this->golesLocal > this->golesVisitante) {
        this->ganador = this->equipoLocal;
    } else if (this->golesVisitante > this->golesLocal) {
        this->ganador = this->equipoVisitante;
    } else {
        this->ganador = nullptr; // Solo pasa en Fase de Grupos
    }

    // Actualizar Estadísticas a nivel de EQUIPO
    int puntosL = 0, puntosV = 0;
    int ganadosL = 0, empatesL = 0, perdidosL = 0;
    int ganadosV = 0, empatesV = 0, perdidosV = 0;

    if (golesLocal > golesVisitante) { puntosL = 3; ganadosL = 1; perdidosV = 1; }
        else if (golesVisitante > golesLocal) { puntosV = 3; ganadosV = 1; perdidosL = 1; }
        else { puntosL = 1; puntosV = 1; empatesL = 1; empatesV = 1; }

        // Actualizamos torneo actual [cite: 99]
        equipoLocal->actualizarResultadosTorneo(golesLocal, golesVisitante, puntosL);
    equipoVisitante->actualizarResultadosTorneo(golesVisitante, golesLocal, puntosV);

    // Actualizamos histórico (Asumimos faltas/tarjetas globales = 0 para simplificar al equipo) [cite: 53, 96]
    equipoLocal->actualizarHistorico(golesLocal, golesVisitante, ganadosL, empatesL, perdidosL, 0, 0, 0);
    equipoVisitante->actualizarHistorico(golesVisitante, golesLocal, ganadosV, empatesV, perdidosV, 0, 0, 0);
}

Equipo* Partido::getGanador() const { return this->ganador; }
int Partido::getGolesLocal() const { return this->golesLocal; }
int Partido::getGolesVisitante() const { return this->golesVisitante; }

void Partido::imprimirResultado() const {
    cout << "[" << fecha << "] " << equipoLocal->getNombrePais() << " (" << golesLocal << ") vs ("
         << golesVisitante << ") " << equipoVisitante->getNombrePais() << endl;
    cout << "    Posesion: " << posesionLocal << "% - " << posesionVisitante << "%" << endl;
}
