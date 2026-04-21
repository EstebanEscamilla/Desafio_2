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

void Mundial::realizarSorteo() {
    // Aquí tomaremos los 48 equipos y los repartiremos en los 12 grupos
    std::cout << "[SISTEMA] Inicializando bombos y sorteo..." << std::endl;
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
