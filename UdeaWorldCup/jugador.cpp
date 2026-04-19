#include "Jugador.h"

// 1. Constructor por defecto
Jugador::Jugador() {
    this->nombres = "";
    this->apellidos = "";
    this->numCamiseta = 0;
    this->statsTotales = new Estadistica();
}

// 2. Constructor parametrizado
Jugador::Jugador(std::string _nombres, std::string _apellidos, int _numCamiseta) {
    this->nombres = _nombres;
    this->apellidos = _apellidos;
    this->numCamiseta = _numCamiseta;
    this->statsTotales = new Estadistica();
}

// 3. Destructor (Limpiar la RAM)
Jugador::~Jugador() {
    if (this->statsTotales != nullptr) {
        delete this->statsTotales;
    }
}

// 4. El "Puente" hacia las estadísticas
void Jugador::actualizarEstadisticasJugador(int g, int a, int am, int r, int m) {
    this->statsTotales->actualizarStats(g, a, am, r, m);
}

// 5. Getters
std::string Jugador::getNombreCompleto() {
    return this->nombres + " " + this->apellidos;
}

int Jugador::getNumCamiseta() {
    return this->numCamiseta;
}

Estadistica* Jugador::getStats() {
    return this->statsTotales;
}
