#include "Grupo.h"

//CONSTRUCTOR
Grupo::Grupo(char _letra) {
    this->letraGrupo = _letra;
    this->cantidadEquiposRegistrados = 0;
    for (int i = 0; i < 4; i++) {
        this->equipos[i] = nullptr;
    }
}

//DESTRUCTOR
Grupo::~Grupo() {
    for (int i = 0; i < this->cantidadEquiposRegistrados; i++) {
        if (this->equipos[i] != nullptr) {
            delete this->equipos[i];
        }
    }
}

//AGREGAR EQUIPO (Máximo 4 por grupo)
void Grupo::agregarEquipo(Equipo* nuevoEquipo) {
    if (this->cantidadEquiposRegistrados < 4) {
        this->equipos[this->cantidadEquiposRegistrados] = nuevoEquipo;
        this->cantidadEquiposRegistrados++;
    }
}

//GETTERS
char Grupo::getLetra() {
    return this->letraGrupo;
}

short int Grupo::getCantidadEquiposRegistrados() {
    return this->cantidadEquiposRegistrados;
}

//GETTER ESPECIAL
Equipo* Grupo::getEquipo(int indice) {
    return this->equipos[indice];
}
