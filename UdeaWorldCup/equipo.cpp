#include "equipo.h"
#include <cstring> // Reemplaza a <string>, permite usar strcpy, strlen
#include <cstdio>  // Permite usar snprintf para concatenar textos sin sstream

// 1. CONSTRUCTOR
Equipo::Equipo(const char* _nombrePais, const char* _nombreEntrenador, int _rankingFIFA, const char* _confederacion) {
    // ASIGNACIÓN DINÁMICA DE TEXTOS
    this->nombrePais = new char[strlen(_nombrePais) + 1];
    strcpy(this->nombrePais, _nombrePais);

    this->nombreEntrenador = new char[strlen(_nombreEntrenador) + 1];
    strcpy(this->nombreEntrenador, _nombreEntrenador);

    this->confederacion = new char[strlen(_confederacion) + 1];
    strcpy(this->confederacion, _confederacion);

    this->rankingFIFA = _rankingFIFA;

    // ASIGNACIÓN DINÁMICA DEL ARREGLO DE JUGADORES
    this->plantilla = new Jugador*[26];
    for (int i = 0; i < 26; i++) {
        this->plantilla[i] = nullptr;
    }
    this->cantidadJugadoresRegistrados = 0;

    // Inicializar Torneo
    this->puntosFaseGrupos = 0;
    this->golesFavorTorneo = 0;
    this->golesContraTorneo = 0;

    // Inicializar Históricos (Se sobreescribirán al leer el CSV)
    this->histGolesFavor = 0; this->histGolesContra = 0;
    this->histPartidosGanados = 0; this->histPartidosEmpatados = 0; this->histPartidosPerdidos = 0;
    this->histAmarillas = 0; this->histRojas = 0; this->histFaltas = 0;
}

// 2. DESTRUCTOR (Liberación de memoria para evitar anulación)
Equipo::~Equipo() {
    delete[] nombrePais;
    delete[] nombreEntrenador;
    delete[] confederacion;

    for (int i = 0; i < this->cantidadJugadoresRegistrados; i++) {
        if (this->plantilla[i] != nullptr) {
            delete this->plantilla[i];
        }
    }
    delete[] plantilla; // Borramos el arreglo principal
}

// 3. SOBRECARGA DE OPERADORES
Equipo& Equipo::operator=(const Equipo& otro) {
    if (this == &otro) return *this; // Evitar autoasignación

    // Liberar memoria actual
    delete[] nombrePais;
    delete[] nombreEntrenador;
    delete[] confederacion;

    // Copia profunda
    nombrePais = new char[strlen(otro.nombrePais) + 1];
    strcpy(nombrePais, otro.nombrePais);
    nombreEntrenador = new char[strlen(otro.nombreEntrenador) + 1];
    strcpy(nombreEntrenador, otro.nombreEntrenador);
    confederacion = new char[strlen(otro.confederacion) + 1];
    strcpy(confederacion, otro.confederacion);

    rankingFIFA = otro.rankingFIFA;
    puntosFaseGrupos = otro.puntosFaseGrupos;
    golesFavorTorneo = otro.golesFavorTorneo;
    golesContraTorneo = otro.golesContraTorneo;
    // (Aquí irían las copias de los datos históricos también)

    return *this;
}

// Esta sobrecarga te resuelve el "Criterio de Desempate" del documento automáticamente
bool Equipo::operator<(const Equipo& otro) const {
    if (this->puntosFaseGrupos != otro.puntosFaseGrupos) {
        return this->puntosFaseGrupos < otro.puntosFaseGrupos;
    }
    // Desempate 1: Diferencia de goles
    int difThis = this->golesFavorTorneo - this->golesContraTorneo;
    int difOtro = otro.golesFavorTorneo - otro.golesContraTorneo;
    if (difThis != difOtro) {
        return difThis < difOtro;
    }
    // Desempate 2: Goles a favor
    return this->golesFavorTorneo < otro.golesFavorTorneo;
}

bool Equipo::operator==(const Equipo& otro) const {
    return (strcmp(this->nombrePais, otro.nombrePais) == 0);
}

// 4. MÉTODOS
void Equipo::agregarJugador(Jugador* nuevoJugador) {
    if (this->cantidadJugadoresRegistrados < 26) {
        this->plantilla[this->cantidadJugadoresRegistrados] = nuevoJugador;
        this->cantidadJugadoresRegistrados++;
    }
}

void Equipo::actualizarResultadosTorneo(int golesAnotados, int golesRecibidos, int puntosGanados) {
    this->golesFavorTorneo += golesAnotados;
    this->golesContraTorneo += golesRecibidos;
    this->puntosFaseGrupos += puntosGanados;
}

void Equipo::actualizarHistorico(int golesAnotados, int golesRecibidos, int ganados, int empatados, int perdidos, int amarillas, int rojas, int faltas) {
    this->histGolesFavor += golesAnotados;
    this->histGolesContra += golesRecibidos;
    this->histPartidosGanados += ganados;
    this->histPartidosEmpatados += empatados;
    this->histPartidosPerdidos += perdidos;
    this->histAmarillas += amarillas;
    this->histRojas += rojas;
    this->histFaltas += faltas;
}

void Equipo::generarJugadoresAutomaticamente(int golesTotalesEquipo) {
    int baseGoles = golesTotalesEquipo / 26;
    int residuoGoles = golesTotalesEquipo % 26;

    for (int i = 0; i < 26; i++) {
        int numeroCamiseta = i + 1;

        // Reemplazo de sstream: C-strings nativos
        char bufNombre[30];
        char bufApellido[30];
        snprintf(bufNombre, sizeof(bufNombre), "nombre%d", numeroCamiseta);
        snprintf(bufApellido, sizeof(bufApellido), "apellido%d", numeroCamiseta);

        Jugador* nuevoJugador = new Jugador(bufNombre, bufApellido, numeroCamiseta);

        int golesParaEsteJugador = baseGoles;
        if (i < residuoGoles) golesParaEsteJugador++;

        // Aquí debes tener cuidado según cómo armemos la clase Jugador
        // nuevoJugador->getStats()->setGoles(golesParaEsteJugador);

        agregarJugador(nuevoJugador);
    }
}

// 5. GETTERS Y SETTERS
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
    if (indice >= 0 && indice < cantidadJugadoresRegistrados) {
        return this->plantilla[indice];
    }
    return nullptr;
}
