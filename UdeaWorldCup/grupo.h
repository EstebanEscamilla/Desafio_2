#ifndef GRUPO_H
#define GRUPO_H

#include "equipo.h"

class Grupo {
private:
    char letraGrupo;

    // 1. USO OBLIGATORIO DE MEMORIA DINÁMICA (Puntero doble)
    Equipo** equipos;

    short int cantidadEquiposRegistrados;

public:
    Grupo(char _letra); // Constructor
    ~Grupo();           // Destructor

    void agregarEquipo(Equipo* nuevoEquipo);
    void vaciarGrupo(); // <-- ADENTRO DE LA CLASE

    // Getters constantes (Buenas prácticas)
    char getLetra() const;
    short int getCantidadEquiposRegistrados() const;

    // Getter especial para consultar el equipo por índice
    Equipo* getEquipo(int indice);
};

#endif // GRUPO_H
