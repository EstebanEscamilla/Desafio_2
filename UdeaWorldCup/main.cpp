#include <iostream>
#include "mundial.h"

using namespace std;

long calcularMemoriaAproximada() {
    long memMundial = sizeof(Mundial);
    long memGrupos = 12 * sizeof(Grupo);
    long memEquipos = 48 * sizeof(Equipo);
    long memJugadores = (48 * 26) * sizeof(Jugador);
    long memEstadisticas = (48 * 26) * sizeof(Estadistica);

    return memMundial + memGrupos + memEquipos + memJugadores + memEstadisticas;
}

int main() {
    cout << "========================================" << endl;
    cout << "   INICIANDO SIMULADOR MUNDIAL 2026" << endl;
    cout << "========================================" << endl;

    Mundial* simulador = new Mundial();
    int opcion = -1;

    while (opcion != 0) {
        cout << "\n========== MENU PRINCIPAL ==========" << endl;
        cout << "1. Cargar datos de equipos (CSV)" << endl;
        cout << "2. Realizar sorteo de Fase de Grupos" << endl;
        cout << "3. Simular Fase de Grupos y Mostrar Tablas" << endl;
        cout << "4. Simular Rondas Eliminatorias (R16 a Final)" << endl;
        cout << "5. Generar Estadisticas del Torneo" << endl;
        cout << "0. Salir y Exportar DB Historica" << endl;
        cout << "====================================" << endl;
        cout << "Seleccione una opcion: ";

        cin >> opcion;
        if (cin.fail()) { cin.clear(); while (cin.get() != '\n'); opcion = -1; continue; }

        switch (opcion) {
        case 1:
            simulador->cargarEquiposDesdeArchivo("C:\\Users\\SANTIAGO\\Desktop\\Ing.Electronica_UdeA\\Semestre 2\\Informatica2\\Desafio2\\Desafio_2\\UdeaWorldCup\\selecciones_clasificadas_mundial.csv");
            cout << "\n[METRICA] Memoria dinamica total reservada: aprox " << calcularMemoriaAproximada() << " bytes en Heap." << endl;
            break;
        case 2:
            simulador->realizarSorteo();
            cout << "\n[METRICA] Memoria dinamica total reservada: aprox " << calcularMemoriaAproximada() << " bytes en Heap." << endl;
            break;
        case 3:
            simulador->simularFaseGrupos();
            simulador->mostrarTablasPosiciones();
            cout << "\n[METRICA] Memoria dinamica total reservada: aprox " << calcularMemoriaAproximada() << " bytes en Heap." << endl;
            break;
        case 4:
            simulador->simularEliminatorias();
            cout << "\n[METRICA] Memoria dinamica total reservada: aprox " << calcularMemoriaAproximada() << " bytes en Heap." << endl;
            break;
        case 5:
            simulador->generarReporteFinal();
            cout << "\n[METRICA] Memoria dinamica total reservada: aprox " << calcularMemoriaAproximada() << " bytes en Heap." << endl;
            break;
        case 0:
            simulador->guardarHistoricoJugadores();
            cout << "Saliendo del simulador... Limpiando memoria y evitando fugas." << endl;
            break;
        default:
            cout << "Opcion invalida. Intente de nuevo." << endl;
            break;
        }
    }
    delete simulador;
    return 0;
}
