#ifndef MUNDIAL_H
#define MUNDIAL_H

#include "grupo.h"
#include "equipo.h"

class Mundial {
private:
    // 1. OBLIGATORIO: Punteros dobles para arreglos dinámicos
    Grupo** grupos;
    Equipo** todosLosEquipos;

    short int totalEquiposCargados;

    void ordenarEquiposPorRanking(Equipo** arreglo, int size);
    bool esValidoParaGrupo(Grupo* grupo, Equipo* equipoCandidato);

public:
    Mundial();
    ~Mundial();

    // Reemplazo de std::string por const char*
    void cargarEquiposDesdeArchivo(const char* rutaArchivo);
    void realizarSorteo();
    void mostrarTablasPosiciones();

    void simularFaseGrupos();
    void simularEliminatorias();
};

#endif // MUNDIAL_H
