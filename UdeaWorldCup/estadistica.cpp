#include "Estadistica.h"

//Constructor
Estadistica::Estadistica() {
    //Inicializar Estadisticas en cero
    this->goles = 0;
    this->asistencias = 0;
    this->tarjetasAmarillas=0;
    this->tarjetasRojas=0;
    this->minutos=0;
}

// Destructor
Estadistica::~Estadistica() {
}

// Declaracion del metodo para actualizar estadisticas
void Estadistica::actualizarStats(int golesNuevos, int asistNuevas, int amarillasNuevas, int rojasNuevas, int minsNuevos) {
    this->goles += golesNuevos;
    this->asistencias += asistNuevas;
    this->tarjetasAmarillas += amarillasNuevas;
    this->tarjetasRojas += rojasNuevas;
    this->minutos += minsNuevos;
}

//Getters
int Estadistica::getGoles() {
    return this->goles;
}
int Estadistica::getAsistencias() {
    return this->asistencias;
}
int Estadistica::getTarjetasAmarillas(){
    return this->tarjetasAmarillas;
}
int Estadistica::getTarjetasRojas(){
    return this->tarjetasRojas;
}
int Estadistica::getMinutos(){
    return this->minutos;
}
