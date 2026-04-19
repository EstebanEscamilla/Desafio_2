#include <iostream>
#include "Estadistica.h" // 1. Traemos Estadistica.h para que el main conozca la clase

using namespace std; // Para no tener que escribir std::cout a cada rato

int main() {
    cout << "--- LABORATORIO DE PRUEBAS ---" << endl;

    // 2. CREAR EL OBJETO
    Estadistica* libretaMbappe = new Estadistica();

    // 3. CONSULTAR EL ESTADO INICIAL
    // Como es un puntero (*), usamos una flecha (->) para llamar a sus métodos.
    cout << "\nGoles al iniciar: " << libretaMbappe->getGoles() << endl;

    // 4. USAR LOS MÉTODOS
    cout << "\nSimulando un partido donde hace 3 goles y juega 90 mins..." << endl;
    // Parámetros: golesNuevos=3, asistNuevas=0, amarillas=1, rojas=0, mins=90
    libretaMbappe->actualizarStats(3, 0, 1, 0, 90);

    // 5. CONSULTAR EL NUEVO ESTADO
    cout << "Goles actualizados: " << libretaMbappe->getGoles() << endl;
    cout << "Amarillas actuales: " << libretaMbappe->getTarjetasAmarillas() << endl;
    cout << "Minutos jugados: " << libretaMbappe->getMinutos() << endl;

    // Simulemos un segundo partido
    cout << "\nSimulando segundo partido (anota 1 gol mas)..." << endl;
    libretaMbappe->actualizarStats(1, 0, 2, 1, 90);

    cout << "Goles totales ahora: " << libretaMbappe->getGoles() << endl;
    cout << "Amarillas totales ahora: " << libretaMbappe->getTarjetasAmarillas()<<endl;
    cout << "Rojas totales ahora: " << libretaMbappe->getTarjetasRojas()<<endl;
    cout << "Minutos totales ahora: " << libretaMbappe->getMinutos() << endl;

    // 6. DESTRUIR EL OBJETO
    delete libretaMbappe;

    cout << "\nPrueba finalizada. Memoria liberada." << endl;

    return 0;
}
