#include "equipo.h"

static int e_strlen(const char* str) {
    int len = 0; while (str[len] != '\0') len++; return len;
}
static void e_strcpy(char* dest, const char* src) {
    int i = 0; while (src[i] != '\0') { dest[i] = src[i]; i++; } dest[i] = '\0';
}
static int e_strcmp(const char* s1, const char* s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) return s1[i] - s2[i];
        i++;
    }
    return s1[i] - s2[i];
}
static void e_strcat(char* dest, const char* src) {
    int i = 0; while (dest[i] != '\0') i++;
    int j = 0; while (src[j] != '\0') { dest[i] = src[j]; i++; j++; }
    dest[i] = '\0';
}

Equipo::Equipo(const char* _nombrePais, const char* _nombreEntrenador, int _rankingFIFA, const char* _confederacion) {
    this->nombrePais = new char[e_strlen(_nombrePais) + 1]; e_strcpy(this->nombrePais, _nombrePais);
    this->nombreEntrenador = new char[e_strlen(_nombreEntrenador) + 1]; e_strcpy(this->nombreEntrenador, _nombreEntrenador);
    this->confederacion = new char[e_strlen(_confederacion) + 1]; e_strcpy(this->confederacion, _confederacion);
    this->rankingFIFA = _rankingFIFA;

    this->plantilla = new Jugador*[26];
    for (int i = 0; i < 26; i++) this->plantilla[i] = nullptr;
    this->cantidadJugadoresRegistrados = 0;

    this->puntosFaseGrupos = 0; this->golesFavorTorneo = 0; this->golesContraTorneo = 0;
    this->histGolesFavor = 0; this->histGolesContra = 0; this->histPartidosGanados = 0;
    this->histPartidosEmpatados = 0; this->histPartidosPerdidos = 0;
    this->histAmarillas = 0; this->histRojas = 0; this->histFaltas = 0;
}

Equipo::~Equipo() {
    delete[] nombrePais; delete[] nombreEntrenador; delete[] confederacion;
    for (int i = 0; i < this->cantidadJugadoresRegistrados; i++) {
        if (this->plantilla[i] != nullptr) delete this->plantilla[i];
    }
    delete[] plantilla;
}

Equipo& Equipo::operator=(const Equipo& otro) {
    if (this == &otro) return *this;
    delete[] nombrePais; delete[] nombreEntrenador; delete[] confederacion;
    nombrePais = new char[e_strlen(otro.nombrePais) + 1]; e_strcpy(nombrePais, otro.nombrePais);
    nombreEntrenador = new char[e_strlen(otro.nombreEntrenador) + 1]; e_strcpy(nombreEntrenador, otro.nombreEntrenador);
    confederacion = new char[e_strlen(otro.confederacion) + 1]; e_strcpy(confederacion, otro.confederacion);
    rankingFIFA = otro.rankingFIFA; puntosFaseGrupos = otro.puntosFaseGrupos;
    golesFavorTorneo = otro.golesFavorTorneo; golesContraTorneo = otro.golesContraTorneo;
    return *this;
}

bool Equipo::operator<(const Equipo& otro) const {
    if (this->puntosFaseGrupos != otro.puntosFaseGrupos) return this->puntosFaseGrupos < otro.puntosFaseGrupos;
    int difThis = this->golesFavorTorneo - this->golesContraTorneo;
    int difOtro = otro.golesFavorTorneo - otro.golesContraTorneo;
    if (difThis != difOtro) return difThis < difOtro;
    return this->golesFavorTorneo < otro.golesFavorTorneo;
}

bool Equipo::operator==(const Equipo& otro) const { return (e_strcmp(this->nombrePais, otro.nombrePais) == 0); }

void Equipo::agregarJugador(Jugador* nuevoJugador) {
    if (this->cantidadJugadoresRegistrados < 26) {
        this->plantilla[this->cantidadJugadoresRegistrados] = nuevoJugador;
        this->cantidadJugadoresRegistrados++;
    }
}

void Equipo::actualizarResultadosTorneo(int golesAnotados, int golesRecibidos, int puntosGanados) {
    this->golesFavorTorneo += golesAnotados; this->golesContraTorneo += golesRecibidos; this->puntosFaseGrupos += puntosGanados;
}

void Equipo::actualizarHistorico(int golesAnotados, int golesRecibidos, int ganados, int empatados, int perdidos, int amarillas, int rojas, int faltas) {
    this->histGolesFavor += golesAnotados; this->histGolesContra += golesRecibidos;
    this->histPartidosGanados += ganados; this->histPartidosEmpatados += empatados; this->histPartidosPerdidos += perdidos;
    this->histAmarillas += amarillas; this->histRojas += rojas; this->histFaltas += faltas;
}

void Equipo::generarJugadoresAutomaticamente(int golesTotalesEquipo) {
    int baseGoles = golesTotalesEquipo / 26;
    int residuoGoles = golesTotalesEquipo % 26;
    for (int i = 0; i < 26; i++) {
        int numeroCamiseta = i + 1;

        // CONSTRUCCIÓN MANUAL DE STRINGS SIN LIBRERÍAS
        char bufNombre[30] = "nombre";
        char bufApellido[30] = "apellido";

        char numStr[5];
        int temp = numeroCamiseta;
        int idx = 0;
        if (temp >= 10) { numStr[idx++] = (temp / 10) + '0'; temp %= 10; }
        numStr[idx++] = temp + '0';
        numStr[idx] = '\0';

        e_strcat(bufNombre, numStr);
        e_strcat(bufApellido, numStr);

        Jugador* nuevoJugador = new Jugador(bufNombre, bufApellido, numeroCamiseta);
        int golesParaEsteJugador = baseGoles;
        if (i < residuoGoles) golesParaEsteJugador++;
        nuevoJugador->getStats()->setGoles(golesParaEsteJugador);
        agregarJugador(nuevoJugador);
    }
}

void Equipo::setPromedioGolesFavorHistorico(double _goles) { this->promedioGolesFavorHistorico = _goles; }
void Equipo::setPromedioGolesContraHistorico(double _goles) { this->promedioGolesContraHistorico = _goles; }
double Equipo::getPromedioGolesFavorHistorico() const { return this->promedioGolesFavorHistorico; }
double Equipo::getPromedioGolesContraHistorico() const { return this->promedioGolesContraHistorico; }
const char* Equipo::getNombrePais() const { return this->nombrePais; }
const char* Equipo::getNombreEntrenador() const { return this->nombreEntrenador; }
const char* Equipo::getConfederacion() const { return this->confederacion; }
int Equipo::getRankingFIFA() const { return this->rankingFIFA; }
int Equipo::getPuntosFaseGrupos() const { return this->puntosFaseGrupos; }
int Equipo::getGolesFavorTorneo() const { return this->golesFavorTorneo; }
int Equipo::getGolesContraTorneo() const { return this->golesContraTorneo; }

Jugador* Equipo::getJugador(int indice) {
    if (indice >= 0 && indice < cantidadJugadoresRegistrados) return this->plantilla[indice];
    return nullptr;
}
