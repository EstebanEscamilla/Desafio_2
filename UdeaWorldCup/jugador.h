#ifndef JUGADOR_H
#define JUGADOR_H

#include "estadistica.h" // Observa que incluimos con minúsculas (buenas prácticas en Linux/Mac)

class Jugador {
private:
    // 1. Reemplazo absoluto de std::string por punteros dinámicos
    char* nombres;
    char* apellidos;
    char* nombreCompleto; // Almacenará "nombres + apellidos" de forma segura

    int numCamiseta;
    Estadistica* statsTotales;

public:
    // Constructores (Reciben const char*)
    Jugador();
    Jugador(const char* _nombres, const char* _apellidos, int _numCamiseta);

    // Destructor
    ~Jugador();

    // Metodo puente
    void actualizarEstadisticasJugador(int golesNuevos, int asistNuevas, int amarillasNuevas, int rojasNuevas, int minsNuevos);

    // Getters
    const char* getNombreCompleto() const;
    const char* getNombres() const;
    const char* getApellidos() const;
    int getNumCamiseta() const;
    Estadistica* getStats() const;
};

#endif // JUGADOR_H
