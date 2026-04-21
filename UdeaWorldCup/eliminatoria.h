#ifndef ELIMINATORIA_H
#define ELIMINATORIA_H

#include "Equipo.h"

class Eliminatoria {
private:
    // Arreglos nativos para cada ronda
    Equipo* ronda32[32];
    Equipo* ronda16[16];
    Equipo* cuartos[8];
    Equipo* semis[4];
    Equipo* final[2];
    Equipo* campeon;

public:
    Eliminatoria();
    ~Eliminatoria();

    // Recibe los 32 clasificados desde la clase Mundial
    void cargarClasificados(Equipo* clasificados[32]);

    // Métodos para ejecutar cada fase
    void simularRonda32();
    void simularRonda16();
    void simularCuartos();
    void simularSemis();
    void simularFinal();

    // Resultado
    void mostrarPodio();
};

#endif
