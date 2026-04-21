#ifndef MUNDIAL_H
#define MUNDIAL_H

#include <string>
#include "Grupo.h"

class Mundial {
private:
    Grupo* grupos[12];
    Equipo* todosLosEquipos[48];
    short int totalEquiposCargados;

public:
    // Constructor y Destructor
    Mundial();
    ~Mundial();

    // Metodos
    void cargarEquiposDesdeArchivo(std::string rutaArchivo);
    void realizarSorteo();
    void mostrarTablasPosiciones();

    // Lógica de torneo
    void simularFaseGrupos();
    void simularEliminatorias();
};

#endif // MUNDIAL_H
