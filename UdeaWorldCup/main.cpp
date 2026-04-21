#include <iostream>
#include "Mundial.h"

using namespace std;

int main() {
    cout << "========================================" << endl;
    cout << "   INICIANDO SIMULADOR MUNDIAL 2026" << endl;
    cout << "========================================" << endl;

    // 1. Instanciamos el motor principal
    Mundial* simulador = new Mundial();

    // 2. Ejecutamos la carga (Asegúrate de poner el nombre real de tu archivo CSV)
    // Si tu archivo está en la misma carpeta, pon solo el nombre.
    simulador->cargarEquiposDesdeArchivo("C:\\Users\\Esteban Escamilla\\Desktop\\UNIVERSIDAD\\SEMESTRES\\SEMESTRE 2026-1\\INFORMATICA II\\DESAFIO 1\\Desafio_2\\UdeaWorldCup\\selecciones_clasificadas_mundial.csv");

    // 3. Pequeña prueba de validación (El Laboratorio)
    // Vamos a imprimir al primer equipo cargado para ver si fabricó a sus jugadores
    // Nota: Esto asume que tienes un getter getEquipo(int index) o que puedes acceder a ellos.
    // Si no lo tienes, puedes poner un cout dentro de Mundial.cpp solo para ver la magia.

    cout << "\nPresiona ENTER para salir..." << endl;
    cin.get();

    // Limpiamos la memoria
    delete simulador;

    return 0;
}
