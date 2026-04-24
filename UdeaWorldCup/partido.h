#ifndef PARTIDO_H
#define PARTIDO_H

#include "equipo.h"

class Partido {
private:
    // 1. Textos dinámicos
    char* fecha;
    char* hora;
    char* sede;

    // Arreglo dinámico de cadenas dinámicas (doble puntero)
    char** arbitros;

    // 2. Punteros a los equipos (No los creamos, solo los referenciamos)
    Equipo* equipoLocal;
    Equipo* equipoVisitante;

    // 3. Resultados
    int golesLocal;
    int golesVisitante;
    double posesionLocal;
    double posesionVisitante;
    bool esEliminatoria; // Para saber si puede haber prórroga (120 mins)
    Equipo* ganador;

    // 4. Arreglos dinámicos para las alineaciones (11 punteros a jugador)
    Jugador** alineacionLocal;
    Jugador** alineacionVisitante;

    // Métodos privados para organizar el código matemático
    void elegirAlineaciones();
    void calcularPosesion();
    int calcularGolesEsperados(Equipo* atacante, Equipo* defensor);

    // Método que lanza los "dados" para generar los sucesos del partido
    void simularEventosJugadores(Jugador** alineacion, int golesEsperados, int& golesRealesAnotados, int minutosJugados);

public:
    // Constructor
    Partido(Equipo* local, Equipo* visitante, const char* _fecha, bool _esEliminatoria);

    // Destructor
    ~Partido();

    // El motor que ejecuta la simulación completa
    void simular();

    // Getters
    Equipo* getGanador() const;
    int getGolesLocal() const;
    int getGolesVisitante() const;
    void imprimirResultado() const;
};

#endif // PARTIDO_H
