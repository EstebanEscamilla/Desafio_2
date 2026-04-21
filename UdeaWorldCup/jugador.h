#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include "Estadistica.h"



class Jugador {
private:
    std::string nombres;
    std::string apellidos;
    int numCamiseta;
    Estadistica* statsTotales;

public:

    // Constructores sobrecarga #1
    Jugador(); // Constructor por defecto (crea un jugador vacío)
    Jugador(std::string _nombres, std::string _apellidos, int _numCamiseta); // Constructor con datos iniciales
    ~Jugador(); //Destructor

    // Metodo puente para actualizar stats del jugador
    void actualizarEstadisticasJugador(int golesNuevos, int asistNuevas, int amarillasNuevas, int rojasNuevas, int minsNuevos);

    // Getters para consultar atributos del jugador
    std::string getNombreCompleto();
    int getNumCamiseta();
    Estadistica* getStats();
};

#endif // JUGADOR_H
