#ifndef MUNDIAL_H
#define MUNDIAL_H

#include "grupo.h"
#include "equipo.h"
#include "partido.h"
#include "eliminatoria.h"

class Mundial {
private:
    Grupo** grupos;
    Equipo** todosLosEquipos;
    short int totalEquiposCargados;
    Equipo** podio;

    void ordenarEquiposPorRanking(Equipo** arreglo, int size, int& iteraciones);
    bool esValidoParaGrupo(Grupo* grupo, Equipo* equipoCandidato, int& iteraciones);

public:
    Mundial();
    ~Mundial();

    void cargarEquiposDesdeArchivo(const char* rutaArchivo);
    void realizarSorteo();
    void simularFaseGrupos();
    void mostrarTablasPosiciones();
    void simularEliminatorias();
    void generarReporteFinal();
    void guardarHistoricoJugadores();
};
#endif // MUNDIAL_H
