#include "Mundial.h"
#include <fstream>
#include <sstream>
#include <cstdlib> // Para atoi y atof
#include <iostream>

// CONSTRUCTOR
Mundial::Mundial() {
    this->totalEquiposCargados = 0;
    for (int i = 0; i < 48; i++) {
        this->todosLosEquipos[i] = nullptr;
    }

    char letras[12] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L'};
    for (int i = 0; i < 12; i++) {
        this->grupos[i] = new Grupo(letras[i]);
    }
}

Mundial::~Mundial() {
    for (int i = 0; i < 12; i++) {
        if (this->grupos[i] != nullptr) {
            delete this->grupos[i];
        }
    }
}


void Mundial::cargarEquiposDesdeArchivo(std::string rutaArchivo) {
    // Usamos .c_str() para compatibilidad con fstream nativo
    std::ifstream archivo(rutaArchivo.c_str());
    std::string linea;

    if (!archivo.is_open()) {
        std::cout << "[ERROR] No se pudo abrir el archivo: " << rutaArchivo << std::endl;
        return;
    }

    // 1. Saltamos las dos líneas de encabezado (Título y nombres de columnas)
    std::getline(archivo, linea);
    std::getline(archivo, linea);

    // 2. Leemos línea por línea hasta llegar a los 48 equipos
    while (std::getline(archivo, linea) && totalEquiposCargados < 48) {
        if (linea.empty()) continue; // Saltamos líneas en blanco accidentales

        std::stringstream ss(linea);
        std::string rankStr, pais, dt, federacion, conf, gfStr, gcStr, pgStr, peStr, ppStr;

        // 3. Extraemos los campos usando ';' como delimitador
        std::getline(ss, rankStr, ';');
        std::getline(ss, pais, ';');
        std::getline(ss, dt, ';');
        std::getline(ss, federacion, ';');
        std::getline(ss, conf, ';');
        std::getline(ss, gfStr, ';');
        std::getline(ss, gcStr, ';');
        std::getline(ss, pgStr, ';');
        std::getline(ss, peStr, ';');
        std::getline(ss, ppStr, ';');

        // Verificación básica de datos
        if (pais.empty()) continue;

        // 4. Conversión de datos de String a tipos numéricos
        int ranking = std::atoi(rankStr.c_str());
        double gfTotal = std::atof(gfStr.c_str());
        double gcTotal = std::atof(gcStr.c_str());

        // Calculamos partidos totales para el promedio
        int pj = std::atoi(pgStr.c_str()) + std::atoi(peStr.c_str()) + std::atoi(ppStr.c_str());

        // Calculamos promedios (Evitando división por cero)
        double promedioGF = (pj > 0) ? (gfTotal / pj) : 0.0;
        double promedioGC = (pj > 0) ? (gcTotal / pj) : 0.0;

        // 5. Instanciamos el Equipo en memoria dinámica
        Equipo* nuevo = new Equipo(pais, dt, ranking, conf);

        nuevo->setPromedioGolesFavorHistorico(promedioGF);
        nuevo->setPromedioGolesContraHistorico(promedioGC);

        // Le pasamos el total histórico crudo que leímos del archivo (gfTotal) convertido a entero
        nuevo->generarJugadoresAutomaticamente((int)gfTotal);
        // -------------------------

        // 7. Guardamos el puntero en el arreglo maestro del Mundial
        this->todosLosEquipos[totalEquiposCargados] = nuevo;
        this->totalEquiposCargados++;

        std::cout << "[CARGADO " << totalEquiposCargados << "/48] "
                  << pais << " | Rank: " << ranking
                  << " | GF Prom: " << promedioGF << std::endl;
    }

    archivo.close();
    std::cout << "--- Proceso de carga finalizado con exito ---" << std::endl;
}

void Mundial::ordenarEquiposPorRanking(Equipo* arreglo[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            // Si el ranking del actual es mayor (peor) que el siguiente, se intercambian
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
    string confCandidato = equipoCandidato->getConfederacion();

    // Contamos cuántos de la misma confederación ya están en el grupo
    for (int i = 0; i < grupo->getCantidadEquiposActuales(); i++) {
        if (grupo->getEquipo(i)->getConfederacion() == confCandidato) {
            contadorMismaConfederacion++;
        }
    }

    // Regla: UEFA máximo 2, los demás máximo 1
    if (confCandidato == "UEFA") {
        return contadorMismaConfederacion < 2;
    } else {
        return contadorMismaConfederacion < 1;
    }
}


// ---------------------------------------------------------
// 3. EL MOTOR PRINCIPAL: EL SORTEO
// ---------------------------------------------------------
void Mundial::realizarSorteo() {
    srand(time(0)); // Inicializamos la semilla de aletoriedad

    cout << "\n[SISTEMA] Preparando los bombos para el sorteo..." << endl;

    Equipo* bombo1[12]; Equipo* bombo2[12];
    Equipo* bombo3[12]; Equipo* bombo4[12];

    Equipo* restoEquipos[47];
    int indexResto = 0;

    // 1. Separar al Anfitrión (United States) y agrupar al resto
    for (int i = 0; i < 48; i++) {
        if (todosLosEquipos[i]->getNombrePais() == "United States" || todosLosEquipos[i]->getNombrePais() == "USA") {
            bombo1[0] = todosLosEquipos[i]; // El anfitrión va de primero
        } else {
            restoEquipos[indexResto] = todosLosEquipos[i];
            indexResto++;
        }
    }

    // 2. Ordenar a los 47 restantes por Ranking FIFA
    ordenarEquiposPorRanking(restoEquipos, 47);

    // 3. Llenar los Bombos matemáticamente
    for (int i = 0; i < 47; i++) {
        if (i < 11) {
            bombo1[i + 1] = restoEquipos[i];   // Termina de llenar el Bombo 1
        } else if (i < 23) {
            bombo2[i - 11] = restoEquipos[i];  // Llena el Bombo 2
        } else if (i < 35) {
            bombo3[i - 23] = restoEquipos[i];  // Llena el Bombo 3
        } else {
            bombo4[i - 35] = restoEquipos[i];  // Llena el Bombo 4
        }
    }

    cout << "[SISTEMA] Bombos creados. Iniciando extraccion al azar..." << endl;

    // 4. EL SORTEO CON PROTECCIÓN ANTI-DEADLOCK
    bool sorteoExitoso = false;
    int reinicios = 0;

    while (!sorteoExitoso) {
        sorteoExitoso = true;

        // Vaciar todos los grupos antes de empezar o reiniciar
        for(int i = 0; i < 12; i++) {
            grupos[i]->vaciarGrupo();
        }

        bool usadoB1[12] = {false}; bool usadoB2[12] = {false};
        bool usadoB3[12] = {false}; bool usadoB4[12] = {false};

        // Recorrer los 12 grupos
        for (int g = 0; g < 12; g++) {
            int index, intentos;
            bool asignado;

            // --- Extraer del BOMBO 1 --- (Sin restricciones porque el grupo está vacío)
            do { index = rand() % 12; } while (usadoB1[index]);
            usadoB1[index] = true;
            grupos[g]->agregarEquipo(bombo1[index]);

            // --- Extraer del BOMBO 2 ---
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
            if (intentos >= 100) { sorteoExitoso = false; break; } // Deadlock detectado

            // --- Extraer del BOMBO 3 ---
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
            if (intentos >= 100) { sorteoExitoso = false; break; } // Deadlock detectado

            // --- Extraer del BOMBO 4 ---
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
            if (intentos >= 100) { sorteoExitoso = false; break; } // Deadlock detectado
        }

        if (!sorteoExitoso) {
            reinicios++; // Incrementa contador y el While vuelve a empezar automáticamente
        }
    }

    cout << "\n========================================" << endl;
    cout << "   SORTEO FINALIZADO CON EXITO" << endl;
    cout << "   (Reinicios anti-bloqueo: " << reinicios << ")" << endl;
    cout << "========================================\n" << endl;
}

void Mundial::mostrarTablasPosiciones() {
    // Recorreremos los 12 grupos y le pediremos a cada uno que muestre a sus equipos
    std::cout << "\n=== TABLAS DE POSICIONES ===" << std::endl;
}

void Mundial::simularFaseGrupos() {
    // Lógica matemática para enfrentar a los 4 equipos de cada grupo entre sí
    std::cout << "[SISTEMA] Simulando partidos de Fase de Grupos..." << std::endl;
}

void Mundial::simularEliminatorias() {
    // Llaves de dieciseisavos, octavos, cuartos, semis y final
    std::cout << "[SISTEMA] Entrando a rondas de muerte subita..." << std::endl;
}
