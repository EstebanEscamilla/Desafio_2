#include "eliminatoria.h"
#include <iostream>

using namespace std;

Eliminatoria::Eliminatoria() {}

Eliminatoria::~Eliminatoria() {}

void Eliminatoria::ejecutarEliminatorias(Grupo** grupos, Equipo** podio, int& iteraciones) {
    cout << "\n[SISTEMA] Entrando a eliminacion directa a traves de clase Eliminatoria..." << endl;

    // Arreglos dinámicos para clasificar
    Equipo** primeros = new Equipo*[12];
    Equipo** segundos = new Equipo*[12];
    Equipo** terceros = new Equipo*[12];

    for (int i = 0; i < 12; i++) {
        iteraciones++; Equipo* eq[4];
        for(int j=0; j<4; j++) { iteraciones++; eq[j] = grupos[i]->getEquipo(j); }
        for(int a=0; a<3; a++){
            for(int b=0; b<3-a; b++){
                iteraciones++; if( *eq[b] < *eq[b+1] ) { Equipo* temp = eq[b]; eq[b] = eq[b+1]; eq[b+1] = temp; }
            }
        }
        primeros[i] = eq[0]; segundos[i] = eq[1]; terceros[i] = eq[2];
    }

    for(int a=0; a<11; a++){
        for(int b=0; b<11-a; b++){ iteraciones++; if( *terceros[b] < *terceros[b+1] ) { Equipo* t = terceros[b]; terceros[b] = terceros[b+1]; terceros[b+1] = t; } }
    }
    for(int a=0; a<11; a++){
        for(int b=0; b<11-a; b++){ iteraciones++; if( *segundos[b] < *segundos[b+1] ) { Equipo* t = segundos[b]; segundos[b] = segundos[b+1]; segundos[b+1] = t; } }
    }

    Partido** llavesR16 = new Partido*[16]; const char* fecha = "10 07 2026";
    for(int i=0; i<8; i++) { llavesR16[i] = new Partido(primeros[i], terceros[i], fecha, true); iteraciones++; }
    for(int i=8; i<12; i++) { llavesR16[i] = new Partido(primeros[i], segundos[i], fecha, true); iteraciones++; }
    for(int i=0; i<4; i++) { llavesR16[12+i] = new Partido(segundos[i], segundos[7-i], fecha, true); iteraciones++; }

    cout << "\n--- DIECISEISAVOS DE FINAL ---" << endl; Equipo** ganadoresR16 = new Equipo*[16];
    for(int i=0; i<16; i++) {
        iteraciones++; llavesR16[i]->simular(); llavesR16[i]->imprimirResultado(); ganadoresR16[i] = llavesR16[i]->getGanador(); delete llavesR16[i];
    }
    cout << "\n--- OCTAVOS DE FINAL ---" << endl; Equipo** ganadoresOctavos = new Equipo*[8];
    for(int i=0; i<8; i++) {
        iteraciones++; Partido* p = new Partido(ganadoresR16[i*2], ganadoresR16[i*2+1], fecha, true); p->simular(); p->imprimirResultado(); ganadoresOctavos[i] = p->getGanador(); delete p;
    }
    cout << "\n--- CUARTOS DE FINAL ---" << endl; Equipo** ganadoresCuartos = new Equipo*[4];
    for(int i=0; i<4; i++) {
        iteraciones++; Partido* p = new Partido(ganadoresOctavos[i*2], ganadoresOctavos[i*2+1], fecha, true); p->simular(); p->imprimirResultado(); ganadoresCuartos[i] = p->getGanador(); delete p;
    }
    cout << "\n--- SEMIFINALES ---" << endl; Equipo** finalistas = new Equipo*[2]; Equipo** perdedoresSemi = new Equipo*[2];
    for(int i=0; i<2; i++) {
        iteraciones++; Partido* p = new Partido(ganadoresCuartos[i*2], ganadoresCuartos[i*2+1], fecha, true); p->simular(); p->imprimirResultado(); finalistas[i] = p->getGanador();
        perdedoresSemi[i] = (p->getGanador() == ganadoresCuartos[i*2]) ? ganadoresCuartos[i*2+1] : ganadoresCuartos[i*2]; delete p;
    }

    cout << "\n--- PARTIDO TERCER PUESTO ---" << endl;
    Partido* pTercero = new Partido(perdedoresSemi[0], perdedoresSemi[1], fecha, true); pTercero->simular(); pTercero->imprimirResultado();
    podio[2] = pTercero->getGanador(); podio[3] = (pTercero->getGanador() == perdedoresSemi[0]) ? perdedoresSemi[1] : perdedoresSemi[0]; delete pTercero;

    cout << "\n=== LA GRAN FINAL ===" << endl;
    Partido* pFinal = new Partido(finalistas[0], finalistas[1], fecha, true); pFinal->simular(); pFinal->imprimirResultado();
    podio[0] = pFinal->getGanador(); podio[1] = (pFinal->getGanador() == finalistas[0]) ? finalistas[1] : finalistas[0]; delete pFinal;

    cout << "\n[SISTEMA] Campeon: " << podio[0]->getNombrePais() << "!!!" << endl;

    // Limpieza
    delete[] primeros; delete[] segundos; delete[] terceros; delete[] llavesR16;
    delete[] ganadoresR16; delete[] ganadoresOctavos; delete[] ganadoresCuartos; delete[] finalistas; delete[] perdedoresSemi;
}
