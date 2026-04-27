#ifndef PARTIDO_H
#define PARTIDO_H

#include "equipo.h"

class Partido {
private:
    char* fecha; char* hora; char* sede; char** arbitros;
    Equipo* equipoLocal; Equipo* equipoVisitante;
    int golesLocal; int golesVisitante;
    double posesionLocal; double posesionVisitante;
    bool esEliminatoria;
    Equipo* ganador;
    Jugador** alineacionLocal; Jugador** alineacionVisitante;

    void elegirAlineaciones();
    void calcularPosesion();
    int calcularGolesEsperados(Equipo* atacante, Equipo* defensor);
    void simularEventosJugadores(Jugador** alineacion, int golesEsperados, int& golesRealesAnotados, int minutosJugados);

public:
    Partido(Equipo* local, Equipo* visitante, const char* _fecha, bool _esEliminatoria);
    ~Partido();
    void simular();
    Equipo* getGanador() const;
    int getGolesLocal() const; int getGolesVisitante() const;
    void imprimirResultado() const;
};
#endif // PARTIDO_H
