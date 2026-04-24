#ifndef ELIMINATORIA_H
#define ELIMINATORIA_H

#include "equipo.h"
#include "partido.h" // MUY IMPORTANTE: Eliminatoria debe crear Partidos

class Eliminatoria {
private:
    // 1. USO OBLIGATORIO DE MEMORIA DINÁMICA (Punteros dobles)
    Equipo** ronda32;
    Equipo** ronda16;
    Equipo** cuartos;
    Equipo** semis;
    Equipo** finalTorneo; // 'final' es palabra reservada en C++11 a veces, mejor usar finalTorneo
    Equipo* campeon;

    // Arreglo dinámico para guardar los partidos de la fase actual y poder borrarlos
    Partido** partidosFaseActual;
    int cantidadPartidosActual;

    void limpiarPartidos(); // Función auxiliar para liberar memoria

public:
    Eliminatoria();
    ~Eliminatoria(); // Aquí irá la destrucción de los arreglos dinámicos

    void cargarClasificados(Equipo** clasificados); // Recibe un puntero doble

    // Métodos para ejecutar cada fase
    void simularRonda32();
    void simularRonda16();
    void simularCuartos();
    void simularSemis();
    void simularFinal();

    void mostrarPodio();
};

#endif
