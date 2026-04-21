#ifndef EQUIPO_H
#define EQUIPO_H

#include <string>
#include "Jugador.h"

class Equipo {
private:
    // 1. Datos básicos y de Clasificación
    double promedioGolesFavorHistorico;    // GF
    double promedioGolesContraHistorico; // GC
    std::string nombrePais;
    std::string nombreEntrenador;
    int rankingFIFA;
    std::string confederacion;
    int puntosFaseGrupos;
    int golesFavor;
    int golesContra;
    Jugador* plantilla[26]; // Una lista de punteros a jugador

    //Contador para saber cuantos jugadores tiene el equipo
    int cantidadJugadoresRegistrados;

public:
    // Constructor, las demas estadisticas van en ceros
    Equipo(std::string _nombrePais, std::string _nombreEntrenador, int _rankingFIFA, std::string _confederacion);
    //Destructor
    ~Equipo();

    // Metodos:
    void agregarJugador(Jugador* nuevoJugador);
    void actualizarResultadosEquipo(int golesAnotados, int golesRecibidos, int puntosGanados);
    void setPromedioGolesFavorHistorico(double _goles);
    void setPromedioGolesContraHistorico(double _goles);
    void generarJugadoresAutomaticamente(int golesTotalesEquipo);

    // --- GETTERS (Consultas) ---
    double getPromedioGolesFavorHistorico();
    double getPromedioGolesContraHistorico();
    std::string getNombrePais();
    std::string getNombreEntrenador();
    int getRankingFIFA();
    std::string getConfederacion();
    int getPuntosFaseGrupos();
    int getGolesFavor();
    int getGolesContra();

    // GETTER ESPECIAL: Es la "Ventana para acceder desde el main a los atributos privados"
    Jugador* getJugador(int indice);
};

#endif // EQUIPO_H
