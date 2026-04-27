#ifndef EQUIPO_H
#define EQUIPO_H

#include "jugador.h"

class Equipo {
private:
    char* nombrePais; char* nombreEntrenador; char* confederacion;
    int rankingFIFA;
    Jugador** plantilla;
    int cantidadJugadoresRegistrados;

    int puntosFaseGrupos; int golesFavorTorneo; int golesContraTorneo;
    int histGolesFavor; int histGolesContra; int histPartidosGanados;
    int histPartidosEmpatados; int histPartidosPerdidos;
    int histAmarillas; int histRojas; int histFaltas;

    double promedioGolesFavorHistorico; double promedioGolesContraHistorico;

public:
    Equipo(const char* _nombrePais, const char* _nombreEntrenador, int _rankingFIFA, const char* _confederacion);
    ~Equipo();

    Equipo& operator=(const Equipo& otro);
    bool operator<(const Equipo& otro) const;
    bool operator==(const Equipo& otro) const;

    void agregarJugador(Jugador* nuevoJugador);
    void actualizarResultadosTorneo(int golesAnotados, int golesRecibidos, int puntosGanados);
    void actualizarHistorico(int golesAnotados, int golesRecibidos, int ganados, int empatados, int perdidos, int amarillas, int rojas, int faltas);
    void generarJugadoresAutomaticamente(int golesTotalesEquipo);

    void setPromedioGolesFavorHistorico(double _goles);
    void setPromedioGolesContraHistorico(double _goles);

    const char* getNombrePais() const; const char* getNombreEntrenador() const; const char* getConfederacion() const;
    int getRankingFIFA() const; int getPuntosFaseGrupos() const;
    int getGolesFavorTorneo() const; int getGolesContraTorneo() const;
    double getPromedioGolesFavorHistorico() const; double getPromedioGolesContraHistorico() const;
    Jugador* getJugador(int indice);
};
#endif // EQUIPO_H
