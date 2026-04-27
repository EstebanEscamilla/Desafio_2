#include "grupo.h"

Grupo::Grupo(char _letra) {
    this->letraGrupo = _letra;
    this->cantidadEquiposRegistrados = 0;
    this->equipos = new Equipo*[4];
    for (int i = 0; i < 4; i++) this->equipos[i] = nullptr;
}

Grupo::~Grupo() { delete[] this->equipos; }

void Grupo::agregarEquipo(Equipo* nuevoEquipo) {
    if (this->cantidadEquiposRegistrados < 4) {
        this->equipos[this->cantidadEquiposRegistrados] = nuevoEquipo;
        this->cantidadEquiposRegistrados++;
    }
}

void Grupo::vaciarGrupo() { this->cantidadEquiposRegistrados = 0; }
char Grupo::getLetra() const { return this->letraGrupo; }
short int Grupo::getCantidadEquiposRegistrados() const { return this->cantidadEquiposRegistrados; }
Equipo* Grupo::getEquipo(int indice) {
    if (indice >= 0 && indice < cantidadEquiposRegistrados) return this->equipos[indice];
    return nullptr;
}
