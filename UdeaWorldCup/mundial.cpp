#include "mundial.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

// CONSTRUCTOR
Mundial::Mundial() {
    this->totalEquiposCargados = 0;

    // 1. INICIALIZACIÓN DINÁMICA DE ARREGLOS
    this->todosLosEquipos = new Equipo*[48];
    for (int i = 0; i < 48; i++) {
        this->todosLosEquipos[i] = nullptr;
    }

    this->grupos = new Grupo*[12];
    char letras[12] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L'};
    for (int i = 0; i < 12; i++) {
        this->grupos[i] = new Grupo(letras[i]);
    }
}

// DESTRUCTOR
Mundial::~Mundial() {
    for (int i = 0; i < this->totalEquiposCargados; i++) {
        if (this->todosLosEquipos[i] != nullptr) {
            delete this->todosLosEquipos[i];
        }
    }
    delete[] this->todosLosEquipos;

    for (int i = 0; i < 12; i++) {
        if (this->grupos[i] != nullptr) {
            delete this->grupos[i];
        }
    }
    delete[] this->grupos;
}

// LECTOR DE CSV BLINDADO CONTRA LA STL
void Mundial::cargarEquiposDesdeArchivo(const char* rutaArchivo) {
    FILE* archivo = fopen(rutaArchivo, "r");

    if (archivo == nullptr) {
        cout << "[ERROR] No se pudo abrir el archivo: " << rutaArchivo << endl;
        return;
    }

    char linea[512];

    fgets(linea, 512, archivo);
    fgets(linea, 512, archivo);

    while (fgets(linea, 512, archivo) && totalEquiposCargados < 48) {
        char* rankStr = strtok(linea, ";");
        if (rankStr == nullptr) continue;

        char* pais = strtok(nullptr, ";");
        char* dt = strtok(nullptr, ";");
        char* federacion = strtok(nullptr, ";");
        char* conf = strtok(nullptr, ";");
        char* gfStr = strtok(nullptr, ";");
        char* gcStr = strtok(nullptr, ";");
        char* pgStr = strtok(nullptr, ";");
        char* peStr = strtok(nullptr, ";");
        char* ppStr = strtok(nullptr, "\n");

        if (pais == nullptr) continue;

        int ranking = atoi(rankStr);
        double gfTotal = atof(gfStr);
        double gcTotal = atof(gcStr);

        int pj = atoi(pgStr) + atoi(peStr) + atoi(ppStr);

        double promedioGF = (pj > 0) ? (gfTotal / pj) : 0.0;
        double promedioGC = (pj > 0) ? (gcTotal / pj) : 0.0;

        Equipo* nuevo = new Equipo(pais, dt, ranking, conf);
        nuevo->setPromedioGolesFavorHistorico(promedioGF);
        nuevo->setPromedioGolesContraHistorico(promedioGC);
        nuevo->generarJugadoresAutomaticamente((int)gfTotal);

        this->todosLosEquipos[totalEquiposCargados] = nuevo;
        this->totalEquiposCargados++;

        // AQUI ES DONDE VA LA IMPRESION DE LA TABLA (A PURO C++)
        cout << "[CARGADO ";
        if (totalEquiposCargados < 10) cout << " ";
        cout << totalEquiposCargados << "/48] ";

        cout << pais;
        int espaciosFaltantes = 22 - strlen(pais);
        for (int e = 0; e < espaciosFaltantes; e++) {
            cout << " ";
        }

        cout << " | Rank: ";
        if (ranking < 10) cout << "  ";
        else if (ranking < 100) cout << " ";
        cout << ranking << endl;
    }

    fclose(archivo);
    cout << "--- Proceso de carga finalizado con exito ---" << endl;
}

void Mundial::ordenarEquiposPorRanking(Equipo** arreglo, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arreglo[j]->getRankingFIFA() > arreglo[j+1]->getRankingFIFA()) {
                Equipo* temp = arreglo[j];
                arreglo[j] = arreglo[j+1];
                arreglo[j+1] = temp;
            }
        }
    }
}

bool Mundial::esValidoParaGrupo(Grupo* grupo, Equipo* equipoCandidato) {
    int contadorMismaConfederacion = 0;
    const char* confCandidato = equipoCandidato->getConfederacion();

    for (int i = 0; i < grupo->getCantidadEquiposRegistrados(); i++) {
        if (strcmp(grupo->getEquipo(i)->getConfederacion(), confCandidato) == 0) {
            contadorMismaConfederacion++;
        }
    }

    if (strcmp(confCandidato, "UEFA") == 0) {
        return contadorMismaConfederacion < 2;
    } else {
        return contadorMismaConfederacion < 1;
    }
}

void Mundial::realizarSorteo() {
    srand(time(0));

    cout << "\n[SISTEMA] Preparando los bombos para el sorteo..." << endl;

    Equipo** bombo1 = new Equipo*[12];
    Equipo** bombo2 = new Equipo*[12];
    Equipo** bombo3 = new Equipo*[12];
    Equipo** bombo4 = new Equipo*[12];
    Equipo** restoEquipos = new Equipo*[47];

    int indexResto = 0;

    for (int i = 0; i < 48; i++) {
        if (strcmp(todosLosEquipos[i]->getNombrePais(), "United States") == 0 ||
            strcmp(todosLosEquipos[i]->getNombrePais(), "USA") == 0) {
            bombo1[0] = todosLosEquipos[i];
        } else {
            restoEquipos[indexResto] = todosLosEquipos[i];
            indexResto++;
        }
    }

    ordenarEquiposPorRanking(restoEquipos, 47);

    for (int i = 0; i < 47; i++) {
        if (i < 11)      bombo1[i + 1] = restoEquipos[i];
        else if (i < 23) bombo2[i - 11] = restoEquipos[i];
        else if (i < 35) bombo3[i - 23] = restoEquipos[i];
        else             bombo4[i - 35] = restoEquipos[i];
    }

    cout << "[SISTEMA] Bombos creados. Iniciando extraccion al azar..." << endl;

    bool sorteoExitoso = false;
    int reinicios = 0;

    while (!sorteoExitoso) {
        sorteoExitoso = true;

        for(int i = 0; i < 12; i++) {
            grupos[i]->vaciarGrupo();
        }

        bool usadoB1[12] = {false}; bool usadoB2[12] = {false};
        bool usadoB3[12] = {false}; bool usadoB4[12] = {false};

        for (int g = 0; g < 12; g++) {
            int index, intentos;
            bool asignado;

            // Bombo 1
            do { index = rand() % 12; } while (usadoB1[index]);
            usadoB1[index] = true;
            grupos[g]->agregarEquipo(bombo1[index]);

            // Bombo 2
            intentos = 0; asignado = false;
            while (!asignado && intentos < 100) {
                index = rand() % 12;
                if (!usadoB2[index] && esValidoParaGrupo(grupos[g], bombo2[index])) {
                    usadoB2[index] = true;
                    grupos[g]->agregarEquipo(bombo2[index]);
                    asignado = true;
                }
                intentos++;
            }
            if (intentos >= 100) { sorteoExitoso = false; break; }

            // Bombo 3
            intentos = 0; asignado = false;
            while (!asignado && intentos < 100) {
                index = rand() % 12;
                if (!usadoB3[index] && esValidoParaGrupo(grupos[g], bombo3[index])) {
                    usadoB3[index] = true;
                    grupos[g]->agregarEquipo(bombo3[index]);
                    asignado = true;
                }
                intentos++;
            }
            if (intentos >= 100) { sorteoExitoso = false; break; }

            // Bombo 4 (¡YA CORREGIDO, DEVOLVIMOS LA LÓGICA DEL SORTEO!)
            intentos = 0; asignado = false;
            while (!asignado && intentos < 100) {
                index = rand() % 12;
                if (!usadoB4[index] && esValidoParaGrupo(grupos[g], bombo4[index])) {
                    usadoB4[index] = true;
                    grupos[g]->agregarEquipo(bombo4[index]);
                    asignado = true;
                }
                intentos++;
            }
            if (intentos >= 100) { sorteoExitoso = false; break; }
        }

        if (!sorteoExitoso) reinicios++;
    }

    delete[] bombo1; delete[] bombo2; delete[] bombo3; delete[] bombo4; delete[] restoEquipos;

    cout << "\n========================================" << endl;
    cout << "   SORTEO FINALIZADO CON EXITO" << endl;
    cout << "   (Reinicios anti-bloqueo: " << reinicios << ")" << endl;
    cout << "========================================\n" << endl;
}

void Mundial::mostrarTablasPosiciones() {
    cout << "\n=== TABLAS DE POSICIONES ===" << endl;
}

void Mundial::simularFaseGrupos() {
    cout << "[SISTEMA] Simulando partidos de Fase de Grupos..." << endl;
}

void Mundial::simularEliminatorias() {
    cout << "[SISTEMA] Entrando a rondas de muerte subita..." << endl;
}
