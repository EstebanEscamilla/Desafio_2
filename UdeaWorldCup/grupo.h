#ifndef GRUPO_H
#define GRUPO_H

#include "equipo.h"

class Grupo {
private:
    char letraGrupo;
    Equipo** equipos;
    short int cantidadEquiposRegistrados;
public:
    Grupo(char _letra);
    ~Grupo();
    void agregarEquipo(Equipo* nuevoEquipo);
    void vaciarGrupo();
    char getLetra() const;
    short int getCantidadEquiposRegistrados() const;
    Equipo* getEquipo(int indice);
};
#endif // GRUPO_H
