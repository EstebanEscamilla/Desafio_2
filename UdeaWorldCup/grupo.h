#ifndef GRUPO_H
#define GRUPO_H


#include "Equipo.h"

class Grupo {
private:
    char letraGrupo;
    Equipo* equipos[4];
    short int cantidadEquiposRegistrados;

public:
    Grupo(char _letra); //Constructor
    ~Grupo();           // Destructor

    // Metodo
    void agregarEquipo(Equipo* nuevoEquipo);

    // Getter
    char getLetra();
    short int getCantidadEquiposRegistrados();

    // GEtter especail para consultar el equipo por indice
    Equipo* getEquipo(int indice);
};

#endif // GRUPO_H
