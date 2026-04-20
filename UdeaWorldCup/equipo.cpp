#include "Equipo.h"
#include <string>

// 1. CONSTRUCTOR
Equipo::Equipo(std::string _nombrePais, std::string _nombreEntrenador, int _rankingFIFA, std::string _confederacion) {
    // Asignamos los datos iniciales que nos llegan por parámetro
    this->nombrePais = _nombrePais;
    this->nombreEntrenador = _nombreEntrenador;
    this->rankingFIFA = _rankingFIFA;
    this->confederacion = _confederacion;

    // TODO COMIENZA EN CERO:
    // Completa la inicialización de los puntos, goles y el contador de jugadores
    this->puntosFaseGrupos = 0;
    this->golesFavor = 0;
    this->golesContra = 0;
    this->cantidadJugadoresRegistrados = 0;

    //Limpiar los 26 casilleros poniendo "nullptr"
    for (int i = 0; i < 26; i++) {
        this->plantilla[i] = nullptr;
    }
}

// 2. DESTRUCTOR
Equipo::~Equipo() {
    // Si el equipo desaparece, deberia destruir a los jugadores que tiene en su lista
    // Recorremos los casilleros que hemos ocupado hasta el momento:
    for (int i = 0; i < this->cantidadJugadoresRegistrados; i++) {
        if (this->plantilla[i] != nullptr) {
            delete this->plantilla[i];
        }
    }
}

// 3. AGREGAR JUGADOR
// Metodo para agregar jugador verificando que el equipo no esta lleno
void Equipo::agregarJugador(Jugador* nuevoJugador) {
    // Primero, verificamos que el equipo no esté lleno (máximo 26)
    if (this->cantidadJugadoresRegistrados < 26) {

        // Guardamos al jugador en la casilla actual
        this->plantilla[this->cantidadJugadoresRegistrados] = nuevoJugador;

        // Aumentamos el contador en 1 para que el próximo jugador vaya a la siguiente casilla
        this->cantidadJugadoresRegistrados++;
    }
}

// 4. ACTUALIZAR RESULTADOS (Después de un partido)
void Equipo::actualizarResultadosEquipo(int golesAnotados, int golesRecibidos, int puntosGanados) {
    this->golesFavor += golesAnotados;
    this->golesContra += golesRecibidos;
    this->puntosFaseGrupos += puntosGanados;
}

// 5. GETTERS BÁSICOS
std::string Equipo::getNombrePais() {
    return this->nombrePais;
}

std::string Equipo::getNombreEntrenador() {
    return this->nombreEntrenador;
}

int Equipo::getRankingFIFA() {
    return this->rankingFIFA;
}

std::string Equipo::getConfederacion() {
    return this->confederacion;
}

int Equipo::getPuntosFaseGrupos() {
    return this->puntosFaseGrupos;
}

int Equipo::getGolesFavor() {
    return this->golesFavor;
}

int Equipo::getGolesContra() {
    return this->golesContra;
}

// 6. GETTER ESPECIAL
Jugador* Equipo::getJugador(int indice) {
    // Devuelve el jugador que está en el casillero numero 'indice'
    return this->plantilla [indice];
}
