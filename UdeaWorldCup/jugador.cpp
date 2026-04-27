#include "jugador.h"

static int mi_strlen(const char* str) {
    int len = 0; while (str[len] != '\0') len++; return len;
}
static void mi_strcpy(char* dest, const char* src) {
    int i = 0; while (src[i] != '\0') { dest[i] = src[i]; i++; } dest[i] = '\0';
}
static void mi_strcat(char* dest, const char* src) {
    int i = 0; while (dest[i] != '\0') i++;
    int j = 0; while (src[j] != '\0') { dest[i] = src[j]; i++; j++; }
    dest[i] = '\0';
}

Jugador::Jugador() {
    this->nombres = new char[1]; this->nombres[0] = '\0';
    this->apellidos = new char[1]; this->apellidos[0] = '\0';
    this->nombreCompleto = new char[1]; this->nombreCompleto[0] = '\0';
    this->numCamiseta = 0;
    this->statsTotales = new Estadistica();
}

Jugador::Jugador(const char* _nombres, const char* _apellidos, int _numCamiseta) {
    this->nombres = new char[mi_strlen(_nombres) + 1];
    mi_strcpy(this->nombres, _nombres);

    this->apellidos = new char[mi_strlen(_apellidos) + 1];
    mi_strcpy(this->apellidos, _apellidos);

    this->nombreCompleto = new char[mi_strlen(_nombres) + mi_strlen(_apellidos) + 2];
    mi_strcpy(this->nombreCompleto, this->nombres);
    mi_strcat(this->nombreCompleto, " ");
    mi_strcat(this->nombreCompleto, this->apellidos);

    this->numCamiseta = _numCamiseta;
    this->statsTotales = new Estadistica();
}

Jugador::~Jugador() {
    delete[] this->nombres; delete[] this->apellidos; delete[] this->nombreCompleto;
    if (this->statsTotales != nullptr) delete this->statsTotales;
}

void Jugador::actualizarEstadisticasJugador(int g, int a, int am, int r, int m) {
    this->statsTotales->actualizarStats(g, a, am, r, m);
}

const char* Jugador::getNombreCompleto() const { return this->nombreCompleto; }
const char* Jugador::getNombres() const { return this->nombres; }
const char* Jugador::getApellidos() const { return this->apellidos; }
int Jugador::getNumCamiseta() const { return this->numCamiseta; }
Estadistica* Jugador::getStats() const { return this->statsTotales; }
