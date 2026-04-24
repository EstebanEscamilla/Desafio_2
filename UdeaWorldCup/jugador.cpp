#include "jugador.h"
#include <cstring> // Vital para strcpy, strcat, strlen

// 1. Constructor por defecto
Jugador::Jugador() {
    // Para cadenas vacías, reservamos 1 byte de memoria dinámica para el carácter nulo '\0'
    this->nombres = new char[1];
    this->nombres[0] = '\0';

    this->apellidos = new char[1];
    this->apellidos[0] = '\0';

    this->nombreCompleto = new char[1];
    this->nombreCompleto[0] = '\0';

    this->numCamiseta = 0;
    this->statsTotales = new Estadistica();
}

// 2. Constructor parametrizado
Jugador::Jugador(const char* _nombres, const char* _apellidos, int _numCamiseta) {
    // Reservar y copiar Nombres
    this->nombres = new char[strlen(_nombres) + 1];
    strcpy(this->nombres, _nombres);

    // Reservar y copiar Apellidos
    this->apellidos = new char[strlen(_apellidos) + 1];
    strcpy(this->apellidos, _apellidos);

    // CREACIÓN SEGURA DEL NOMBRE COMPLETO (Sustituye al + de std::string)
    // Tamaño = longitud nombre + espacio (1) + longitud apellido + carácter nulo (1)
    this->nombreCompleto = new char[strlen(_nombres) + strlen(_apellidos) + 2];
    strcpy(this->nombreCompleto, this->nombres); // Primero copiamos el nombre
    strcat(this->nombreCompleto, " ");           // Le concatenamos un espacio
    strcat(this->nombreCompleto, this->apellidos); // Le concatenamos el apellido

    this->numCamiseta = _numCamiseta;
    this->statsTotales = new Estadistica();
}

// 3. Destructor (Limpiar TODA la RAM)
Jugador::~Jugador() {
    delete[] this->nombres;
    delete[] this->apellidos;
    delete[] this->nombreCompleto;

    if (this->statsTotales != nullptr) {
        delete this->statsTotales;
    }
}

// 4. Puente hacia las estadísticas
void Jugador::actualizarEstadisticasJugador(int g, int a, int am, int r, int m) {
    this->statsTotales->actualizarStats(g, a, am, r, m);
}

// 5. Getters
const char* Jugador::getNombreCompleto() const {
    return this->nombreCompleto;
}

const char* Jugador::getNombres() const {
    return this->nombres;
}

const char* Jugador::getApellidos() const {
    return this->apellidos;
}

int Jugador::getNumCamiseta() const {
    return this->numCamiseta;
}

Estadistica* Jugador::getStats() const {
    return this->statsTotales;
}
