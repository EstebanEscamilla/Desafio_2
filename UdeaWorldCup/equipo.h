#ifndef EQUIPO_H
#define EQUIPO_H

#include "jugador.h"

class Equipo {
private:
    // 1. Uso estricto de punteros para texto (Cero std::string)
    char* nombrePais;
    char* nombreEntrenador;
    char* confederacion;
    int rankingFIFA;

    // 2. Uso estricto de memoria dinámica para el arreglo
    Jugador** plantilla;
    int cantidadJugadoresRegistrados;

    // 3. ESTADÍSTICAS DEL TORNEO (Fase de grupos actual, se reinician)
    int puntosFaseGrupos;
    int golesFavorTorneo;
    int golesContraTorneo;

    // 4. ESTADÍSTICAS HISTÓRICAS (Vienen del CSV, se acumulan siempre)
    int histGolesFavor;
    int histGolesContra;
    int histPartidosGanados;
    int histPartidosEmpatados;
    int histPartidosPerdidos;
    int histAmarillas;
    int histRojas;
    int histFaltas;

    // Las variables para la ecuación de Poisson
    double promedioGolesFavorHistorico;
    double promedioGolesContraHistorico;

public:
    // Constructor (recibe const char* en lugar de string)
    Equipo(const char* _nombrePais, const char* _nombreEntrenador, int _rankingFIFA, const char* _confederacion);

    // Destructor
    ~Equipo();

    // --- SOBRECARGA DE OPERADORES OBLIGATORIA ---
    // 1. Operador de asignación (vital para copiar memoria dinámica)
    Equipo& operator=(const Equipo& otro);
    // 2. Operador menor que (¡TE ORDENARÁ LA TABLA DE POSICIONES SOLAMENTE CON ESTO!)
    bool operator<(const Equipo& otro) const;
    // 3. Operador de igualdad
    bool operator==(const Equipo& otro) const;

    // Métodos
    void agregarJugador(Jugador* nuevoJugador);
    void actualizarResultadosTorneo(int golesAnotados, int golesRecibidos, int puntosGanados);
    void actualizarHistorico(int golesAnotados, int golesRecibidos, int ganados, int empatados, int perdidos, int amarillas, int rojas, int faltas);
    void generarJugadoresAutomaticamente(int golesTotalesEquipo);

    // Setters Matemáticos
    void setPromedioGolesFavorHistorico(double _goles);
    void setPromedioGolesContraHistorico(double _goles);

    // Getters de Texto (Retornan const char*)
    const char* getNombrePais() const;
    const char* getNombreEntrenador() const;
    const char* getConfederacion() const;

    // Getters Numéricos
    int getRankingFIFA() const;
    int getPuntosFaseGrupos() const;
    int getGolesFavorTorneo() const;
    int getGolesContraTorneo() const;
    double getPromedioGolesFavorHistorico() const;
    double getPromedioGolesContraHistorico() const;

    Jugador* getJugador(int indice);
};

#endif // EQUIPO_H
