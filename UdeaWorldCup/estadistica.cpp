#include "estadistica.h"

Estadistica::Estadistica() : goles(0), asistencias(0), tarjetasAmarillas(0), tarjetasRojas(0), minutos(0) {}
Estadistica::~Estadistica() {}

void Estadistica::actualizarStats(int golesNuevos, int asistNuevas, int amarillasNuevas, int rojasNuevas, int minsNuevos) {
    this->goles += golesNuevos;
    this->asistencias += asistNuevas;
    this->tarjetasAmarillas += amarillasNuevas;
    this->tarjetasRojas += rojasNuevas;
    this->minutos += minsNuevos;
}

Estadistica& Estadistica::operator+=(const Estadistica& statsPartido) {
    this->goles += statsPartido.goles;
    this->asistencias += statsPartido.asistencias;
    this->tarjetasAmarillas += statsPartido.tarjetasAmarillas;
    this->tarjetasRojas += statsPartido.tarjetasRojas;
    this->minutos += statsPartido.minutos;
    return *this;
}

void Estadistica::setGoles(int _goles) { this->goles = _goles; }
int Estadistica::getGoles() const { return this->goles; }
int Estadistica::getAsistencias() const { return this->asistencias; }
int Estadistica::getTarjetasAmarillas() const { return this->tarjetasAmarillas; }
int Estadistica::getTarjetasRojas() const { return this->tarjetasRojas; }
int Estadistica::getMinutos() const { return this->minutos; }
