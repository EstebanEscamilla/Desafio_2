#include "partido.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

static int p_strlen(const char* str) {
    int len = 0; while (str[len] != '\0') len++; return len;
}
static void p_strcpy(char* dest, const char* src) {
    int i = 0; while (src[i] != '\0') { dest[i] = src[i]; i++; } dest[i] = '\0';
}

const double MU = 1.35;
const double ALPHA = 0.6;
const double BETA = 0.4;

Partido::Partido(Equipo* local, Equipo* visitante, const char* _fecha, bool _esEliminatoria) {
    this->equipoLocal = local; this->equipoVisitante = visitante;
    this->esEliminatoria = _esEliminatoria; this->ganador = nullptr;
    this->golesLocal = 0; this->golesVisitante = 0;
    this->posesionLocal = 50.0; this->posesionVisitante = 50.0;

    this->fecha = new char[p_strlen(_fecha) + 1]; p_strcpy(this->fecha, _fecha);
    const char* defaultHora = "00:00"; this->hora = new char[p_strlen(defaultHora) + 1]; p_strcpy(this->hora, defaultHora);
    const char* defaultSede = "nombreSede"; this->sede = new char[p_strlen(defaultSede) + 1]; p_strcpy(this->sede, defaultSede);

    this->arbitros = new char*[3];
    const char* nombresArbitros[3] = {"codArbitro1", "codArbitro2", "codArbitro3"};
    for (int i = 0; i < 3; i++) {
        this->arbitros[i] = new char[p_strlen(nombresArbitros[i]) + 1];
        p_strcpy(this->arbitros[i], nombresArbitros[i]);
    }

    this->alineacionLocal = new Jugador*[11]; this->alineacionVisitante = new Jugador*[11];
    for (int i = 0; i < 11; i++) {
        this->alineacionLocal[i] = nullptr; this->alineacionVisitante[i] = nullptr;
    }
}

Partido::~Partido() {
    delete[] this->fecha; delete[] this->hora; delete[] this->sede;
    for (int i = 0; i < 3; i++) delete[] this->arbitros[i];
    delete[] this->arbitros;
    delete[] this->alineacionLocal; delete[] this->alineacionVisitante;
}

void Partido::elegirAlineaciones() {
    int indicesL[26]; int indicesV[26];
    for(int i = 0; i < 26; i++) { indicesL[i] = i; indicesV[i] = i; }
    for(int i = 25; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = indicesL[i]; indicesL[i] = indicesL[j]; indicesL[j] = temp;
        int k = rand() % (i + 1);
        temp = indicesV[i]; indicesV[i] = indicesV[k]; indicesV[k] = temp;
    }
    for(int i = 0; i < 11; i++) {
        this->alineacionLocal[i] = this->equipoLocal->getJugador(indicesL[i]);
        this->alineacionVisitante[i] = this->equipoVisitante->getJugador(indicesV[i]);
    }
}

void Partido::calcularPosesion() {
    double rankL = (double)this->equipoLocal->getRankingFIFA();
    double rankV = (double)this->equipoVisitante->getRankingFIFA();
    double totalInverso = (1.0 / rankL) + (1.0 / rankV);
    this->posesionLocal = ((1.0 / rankL) / totalInverso) * 100.0;
    this->posesionVisitante = ((1.0 / rankV) / totalInverso) * 100.0;
}

int Partido::calcularGolesEsperados(Equipo* atacante, Equipo* defensor) {
    double gfA = atacante->getPromedioGolesFavorHistorico(); double gcB = defensor->getPromedioGolesContraHistorico();
    if (gfA <= 0) gfA = 0.1; if (gcB <= 0) gcB = 0.1;
    double lambda = MU * pow((gfA / MU), ALPHA) * pow((gcB / MU), BETA);
    return (int)round(lambda);
}

void Partido::simularEventosJugadores(Jugador** alineacion, int golesEsperados, int& golesRealesAnotados, int minutosJugados) {
    golesRealesAnotados = 0;
    for (int i = 0; i < 11; i++) {
        Jugador* j = alineacion[i];
        if (j == nullptr) continue;
        int goles = 0, amarillas = 0, rojas = 0, faltas = 0;
        if (rand() % 10000 < 1300) {
            faltas++;
            if (rand() % 10000 < 275) { faltas++; if (rand() % 10000 < 70) faltas++; }
        }
        if (rand() % 10000 < 600) {
            amarillas++;
            if (rand() % 10000 < 115) { amarillas++; rojas = 1; }
        }
        for (int m = 0; m < 5; m++) {
            if (golesRealesAnotados < golesEsperados) {
                if (rand() % 10000 < 400) { goles++; golesRealesAnotados++; }
            }
        }
        j->actualizarEstadisticasJugador(goles, 0, amarillas, rojas, minutosJugados);
    }
}

void Partido::simular() {
    elegirAlineaciones(); calcularPosesion();
    int lambdaLocal = calcularGolesEsperados(this->equipoLocal, this->equipoVisitante);
    int lambdaVisitante = calcularGolesEsperados(this->equipoVisitante, this->equipoLocal);
    int minutosPartido = 90;

    simularEventosJugadores(this->alineacionLocal, lambdaLocal, this->golesLocal, minutosPartido);
    simularEventosJugadores(this->alineacionVisitante, lambdaVisitante, this->golesVisitante, minutosPartido);

    if (this->esEliminatoria && this->golesLocal == this->golesVisitante) {
        minutosPartido = 120;
        for(int i=0; i<11; i++) {
            if(alineacionLocal[i] != nullptr) alineacionLocal[i]->actualizarEstadisticasJugador(0,0,0,0,30);
            if(alineacionVisitante[i] != nullptr) alineacionVisitante[i]->actualizarEstadisticasJugador(0,0,0,0,30);
        }
        double probLocal = this->posesionLocal;
        if ((rand() % 100) < probLocal) this->golesLocal++; else this->golesVisitante++;
    }

    if (this->golesLocal > this->golesVisitante) this->ganador = this->equipoLocal;
    else if (this->golesVisitante > this->golesLocal) this->ganador = this->equipoVisitante;
    else this->ganador = nullptr;

    int puntosL = 0, puntosV = 0, ganadosL = 0, empatesL = 0, perdidosL = 0, ganadosV = 0, empatesV = 0, perdidosV = 0;
    if (golesLocal > golesVisitante) { puntosL = 3; ganadosL = 1; perdidosV = 1; }
    else if (golesVisitante > golesLocal) { puntosV = 3; ganadosV = 1; perdidosL = 1; }
    else { puntosL = 1; puntosV = 1; empatesL = 1; empatesV = 1; }

    equipoLocal->actualizarResultadosTorneo(golesLocal, golesVisitante, puntosL);
    equipoVisitante->actualizarResultadosTorneo(golesVisitante, golesLocal, puntosV);
    equipoLocal->actualizarHistorico(golesLocal, golesVisitante, ganadosL, empatesL, perdidosL, 0, 0, 0);
    equipoVisitante->actualizarHistorico(golesVisitante, golesLocal, ganadosV, empatesV, perdidosV, 0, 0, 0);
}

Equipo* Partido::getGanador() const { return this->ganador; }
int Partido::getGolesLocal() const { return this->golesLocal; }
int Partido::getGolesVisitante() const { return this->golesVisitante; }
void Partido::imprimirResultado() const {
    cout << "[" << fecha << "] " << equipoLocal->getNombrePais() << " (" << golesLocal << ") vs ("
         << golesVisitante << ") " << equipoVisitante->getNombrePais() << " | Pos: " << posesionLocal << "% - " << posesionVisitante << "%" << endl;
}
