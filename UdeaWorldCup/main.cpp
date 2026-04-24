#include <iostream>
#include "Mundial.h"

using namespace std;

// Función para cumplir con el Requisito V.b (Medición de consumo de memoria)
// Esto calcula los bytes aproximados de las estructuras dinámicas instanciadas.
long calcularMemoriaAproximada() {
    long memMundial = sizeof(Mundial);
    long memGrupos = 12 * sizeof(Grupo);
    long memEquipos = 48 * sizeof(Equipo);
    long memJugadores = (48 * 26) * sizeof(Jugador);
    // (A esto se le sumaría dinámicamente la memoria de los partidos jugados)
    return memMundial + memGrupos + memEquipos + memJugadores;
}

int main() {
    cout << "========================================" << endl;
    cout << "   INICIANDO SIMULADOR MUNDIAL 2026" << endl;
    cout << "========================================" << endl;

    // 1. Instanciamos el motor principal
    Mundial* simulador = new Mundial();

    int opcion = -1;

    while (opcion != 0) {
        cout << "\n========== MENU PRINCIPAL ==========" << endl;
        cout << "1. Cargar datos de equipos (CSV)" << endl;
        cout << "2. Realizar sorteo de Fase de Grupos" << endl;
        cout << "3. Simular Fase de Grupos" << endl;
        cout << "4. Simular Rondas Eliminatorias (R16 a Final)" << endl;
        cout << "5. Generar Estadisticas del Torneo" << endl;
        cout << "0. Salir" << endl;
        cout << "====================================" << endl;
        cout << "Seleccione una opcion: ";

        cin >> opcion;

        // Limpiar el buffer por si el usuario mete letras en vez de números
        if (cin.fail()) {
            cin.clear();
            while (cin.get() != '\n');
            opcion = -1;
            continue;
        }

        switch (opcion) {
        case 1: {
            // Ruta Santiago: "C:\\Users\\SANTIAGO\\Desktop\\Ing.Electronica_UdeA\\Semestre 2\\Informatica2\\Desafio2\\Desafio_2\\UdeaWorldCup\\selecciones_clasificadas_mundial.csv"
            // Ruta Esteban: "C:\\Users\\Esteban Escamilla\\Desktop\\UNIVERSIDAD\\SEMESTRES\\SEMESTRE 2026-1\\INFORMATICA II\\DESAFIO 1\\Desafio_2\\UdeaWorldCup\\selecciones_clasificadas_mundial.csv"

            simulador->cargarEquiposDesdeArchivo("C:\\Users\\SANTIAGO\\Desktop\\Ing.Electronica_UdeA\\Semestre 2\\Informatica2\\Desafio2\\Desafio_2\\UdeaWorldCup\\selecciones_clasificadas_mundial.csv");

            cout << "\n[METRICA] Memoria dinamica en uso: aprox " << calcularMemoriaAproximada() << " bytes." << endl;
            break;
        }
        case 2:
            simulador->realizarSorteo();
            cout << "\n[METRICA] Memoria dinamica en uso: aprox " << calcularMemoriaAproximada() << " bytes." << endl;
            break;
        case 3:
            simulador->simularFaseGrupos();
            simulador->mostrarTablasPosiciones(); // Mostramos cómo quedaron después de simular
            cout << "\n[METRICA] Memoria dinamica en uso: aprox " << calcularMemoriaAproximada() << " bytes." << endl;
            break;
        case 4:
            simulador->simularEliminatorias();
            // A medida que se crean objetos Partido, la memoria aumentaría
            cout << "\n[METRICA] Memoria dinamica en uso: aprox " << calcularMemoriaAproximada() << " bytes." << endl;
            break;
        case 5:
            // simulador->generarReporteFinal(); // Descomenta esto cuando programes el reporte final
            cout << "\n[METRICA] Memoria dinamica en uso: aprox " << calcularMemoriaAproximada() << " bytes." << endl;
            break;
        case 0:
            cout << "Saliendo del simulador... Limpiando memoria." << endl;
            break;
        default:
            cout << "Opcion invalida. Intente de nuevo." << endl;
            break;
        }
    }

    // Limpiamos la memoria del motor (Llama al destructor de Mundial y todo el efecto dominó)
    delete simulador;

    return 0;
}
