#ifndef ELIMINATORIA_H
#define ELIMINATORIA_H

#include "grupo.h"
#include "equipo.h"
#include "partido.h"

class Eliminatoria {
public:
    Eliminatoria();
    ~Eliminatoria();

    // Método que recibe los grupos y el arreglo del podio por referencia
    void ejecutarEliminatorias(Grupo** grupos, Equipo** podio, int& iteraciones);
};

#endif // ELIMINATORIA_H
