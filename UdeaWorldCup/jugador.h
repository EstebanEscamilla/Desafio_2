#ifndef JUGADOR_H
#define JUGADOR_H

#include "estadistica.h"

class Jugador {
private:
    char* nombres;
    char* apellidos;
    char* nombreCompleto;
    int numCamiseta;
    Estadistica* statsTotales;

public:
    Jugador();
    Jugador(const char* _nombres, const char* _apellidos, int _numCamiseta);
    ~Jugador();

    void actualizarEstadisticasJugador(int golesNuevos, int asistNuevas, int amarillasNuevas, int rojasNuevas, int minsNuevos);

    const char* getNombreCompleto() const;
    const char* getNombres() const;
    const char* getApellidos() const;
    int getNumCamiseta() const;
    Estadistica* getStats() const;
};
#endif // JUGADOR_H
