#include "mundial.h"
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

static int m_strlen(const char* str) {
    int len = 0; while (str[len] != '\0') len++; return len;
}
static int m_strcmp(const char* s1, const char* s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) return s1[i] - s2[i];
        i++;
    }
    return s1[i] - s2[i];
}
static int convertirAEntero(const char* str) {
    int resultado = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] >= '0' && str[i] <= '9') resultado = resultado * 10 + (str[i] - '0');
    }
    return resultado;
}
static double convertirADecimal(const char* str) {
    double resultado = 0.0; double divisor = 1.0; bool enDec = false;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] == '.') { enDec = true; continue; }
        if (str[i] >= '0' && str[i] <= '9') {
            if (!enDec) resultado = resultado * 10.0 + (str[i] - '0');
            else { divisor /= 10.0; resultado = resultado + (str[i] - '0') * divisor; }
        }
    }
    return resultado;
}

Mundial::Mundial() {
    this->totalEquiposCargados = 0;
    this->todosLosEquipos = new Equipo*[48];
    for (int i = 0; i < 48; i++) this->todosLosEquipos[i] = nullptr;

    this->grupos = new Grupo*[12];
    char letras[12] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L'};
    for (int i = 0; i < 12; i++) this->grupos[i] = new Grupo(letras[i]);

    this->podio = new Equipo*[4];
    for(int i=0; i<4; i++) this->podio[i] = nullptr;
}

Mundial::~Mundial() {
    for (int i = 0; i < this->totalEquiposCargados; i++) {
        if (this->todosLosEquipos[i] != nullptr) delete this->todosLosEquipos[i];
    }
    delete[] this->todosLosEquipos;
    for (int i = 0; i < 12; i++) {
        if (this->grupos[i] != nullptr) delete this->grupos[i];
    }
    delete[] this->grupos;
    delete[] this->podio;
}

void Mundial::cargarEquiposDesdeArchivo(const char* rutaArchivo) {
    int iteraciones = 0;
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cout << "[ERROR] No se pudo abrir el archivo: " << rutaArchivo << endl;
        return;
    }

    char linea[512];
    archivo.getline(linea, 512);
    archivo.getline(linea, 512);

    while (archivo.getline(linea, 512) && totalEquiposCargados < 48) {
        iteraciones++;

        char* campos[10]; int idxCampo = 0;
        campos[0] = linea;

        for (int i = 0; linea[i] != '\0'; i++) {
            iteraciones++;
            if (linea[i] == ';') {
                linea[i] = '\0'; idxCampo++; campos[idxCampo] = &linea[i + 1];
            }
            if (linea[i] == '\n' || linea[i] == '\r') linea[i] = '\0';
        }

        if (idxCampo < 9) continue;

        char* rankStr = campos[0]; char* pais = campos[1]; char* dt = campos[2]; char* conf = campos[4];
        char* gfStr = campos[5]; char* gcStr = campos[6]; char* pgStr = campos[7]; char* peStr = campos[8]; char* ppStr = campos[9];

        int ranking = convertirAEntero(rankStr);
        double gfTotal = convertirADecimal(gfStr); double gcTotal = convertirADecimal(gcStr);
        int pj = convertirAEntero(pgStr) + convertirAEntero(peStr) + convertirAEntero(ppStr);

        double promedioGF = (pj > 0) ? (gfTotal / pj) : 0.0;
        double promedioGC = (pj > 0) ? (gcTotal / pj) : 0.0;

        Equipo* nuevo = new Equipo(pais, dt, ranking, conf);
        nuevo->setPromedioGolesFavorHistorico(promedioGF);
        nuevo->setPromedioGolesContraHistorico(promedioGC);
        nuevo->generarJugadoresAutomaticamente((int)gfTotal);

        this->todosLosEquipos[totalEquiposCargados] = nuevo;
        this->totalEquiposCargados++;

        cout << "[CARGADO ";
        if (totalEquiposCargados < 10) cout << " ";
        cout << totalEquiposCargados << "/48] " << pais;

        int espaciosFaltantes = 22 - m_strlen(pais);
        for (int e = 0; e < espaciosFaltantes; e++) { iteraciones++; cout << " "; }

        cout << " | Rank: ";
        if (ranking < 10) cout << "  "; else if (ranking < 100) cout << " ";
        cout << ranking << endl;
    }
    archivo.close();
    cout << "--- Proceso de carga finalizado con exito ---" << endl;
    cout << "[METRICA] Iteraciones en extraccion manual: " << iteraciones << endl;
}

void Mundial::ordenarEquiposPorRanking(Equipo** arreglo, int size, int& iteraciones) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            iteraciones++;
            if (arreglo[j]->getRankingFIFA() > arreglo[j+1]->getRankingFIFA()) {
                Equipo* temp = arreglo[j]; arreglo[j] = arreglo[j+1]; arreglo[j+1] = temp;
            }
        }
    }
}

bool Mundial::esValidoParaGrupo(Grupo* grupo, Equipo* equipoCandidato, int& iteraciones) {
    int contador = 0; const char* confCandidato = equipoCandidato->getConfederacion();
    for (int i = 0; i < grupo->getCantidadEquiposRegistrados(); i++) {
        iteraciones++;
        if (m_strcmp(grupo->getEquipo(i)->getConfederacion(), confCandidato) == 0) contador++;
    }
    if (m_strcmp(confCandidato, "UEFA") == 0) return contador < 2;
    else return contador < 1;
}

void Mundial::realizarSorteo() {
    int iteraciones = 0; srand(time(0));
    cout << "\n[SISTEMA] Preparando los bombos para el sorteo..." << endl;
    Equipo** bombo1 = new Equipo*[12]; Equipo** bombo2 = new Equipo*[12];
    Equipo** bombo3 = new Equipo*[12]; Equipo** bombo4 = new Equipo*[12];
    Equipo** restoEquipos = new Equipo*[47];
    int indexResto = 0;

    for (int i = 0; i < 48; i++) {
        iteraciones++;
        if (m_strcmp(todosLosEquipos[i]->getNombrePais(), "United States") == 0 ||
            m_strcmp(todosLosEquipos[i]->getNombrePais(), "USA") == 0) {
            bombo1[0] = todosLosEquipos[i];
        } else {
            restoEquipos[indexResto] = todosLosEquipos[i]; indexResto++;
        }
    }
    ordenarEquiposPorRanking(restoEquipos, 47, iteraciones);

    for (int i = 0; i < 47; i++) {
        iteraciones++;
        if (i < 11)      bombo1[i + 1] = restoEquipos[i];
        else if (i < 23) bombo2[i - 11] = restoEquipos[i];
        else if (i < 35) bombo3[i - 23] = restoEquipos[i];
        else             bombo4[i - 35] = restoEquipos[i];
    }

    bool sorteoExitoso = false; int reinicios = 0;
    while (!sorteoExitoso) {
        iteraciones++; sorteoExitoso = true;
        for(int i = 0; i < 12; i++) { iteraciones++; grupos[i]->vaciarGrupo(); }

        bool usadoB1[12] = {false}; bool usadoB2[12] = {false};
        bool usadoB3[12] = {false}; bool usadoB4[12] = {false};

        for (int g = 0; g < 12; g++) {
            iteraciones++; int index, intentos; bool asignado;
            do { iteraciones++; index = rand() % 12; } while (usadoB1[index]);
            usadoB1[index] = true; grupos[g]->agregarEquipo(bombo1[index]);

            intentos = 0; asignado = false;
            while (!asignado && intentos < 100) {
                iteraciones++; index = rand() % 12;
                if (!usadoB2[index] && esValidoParaGrupo(grupos[g], bombo2[index], iteraciones)) {
                    usadoB2[index] = true; grupos[g]->agregarEquipo(bombo2[index]); asignado = true;
                }
                intentos++;
            }
            if (intentos >= 100) { sorteoExitoso = false; break; }

            intentos = 0; asignado = false;
            while (!asignado && intentos < 100) {
                iteraciones++; index = rand() % 12;
                if (!usadoB3[index] && esValidoParaGrupo(grupos[g], bombo3[index], iteraciones)) {
                    usadoB3[index] = true; grupos[g]->agregarEquipo(bombo3[index]); asignado = true;
                }
                intentos++;
            }
            if (intentos >= 100) { sorteoExitoso = false; break; }

            intentos = 0; asignado = false;
            while (!asignado && intentos < 100) {
                iteraciones++; index = rand() % 12;
                if (!usadoB4[index] && esValidoParaGrupo(grupos[g], bombo4[index], iteraciones)) {
                    usadoB4[index] = true; grupos[g]->agregarEquipo(bombo4[index]); asignado = true;
                }
                intentos++;
            }
            if (intentos >= 100) { sorteoExitoso = false; break; }
        }
        if (!sorteoExitoso) reinicios++;
    }

    delete[] bombo1; delete[] bombo2; delete[] bombo3; delete[] bombo4; delete[] restoEquipos;
    cout << "\n========================================" << endl;
    cout << "   SORTEO FINALIZADO CON EXITO (Reinicios: " << reinicios << ")" << endl;
    cout << "[METRICA] Iteraciones: " << iteraciones << "\n========================================\n" << endl;
}

void Mundial::simularFaseGrupos() {
    int iteraciones = 0;
    cout << "\n[SISTEMA] Iniciando simulacion de Fase de Grupos..." << endl;
    const char* fecha = "20/06/2026";

    for (int i = 0; i < 12; i++) {
        iteraciones++; Equipo* eq[4];
        for(int j=0; j<4; j++) { iteraciones++; eq[j] = grupos[i]->getEquipo(j); }
        int cruces[6][2] = {{0,1}, {2,3}, {0,2}, {1,3}, {0,3}, {1,2}};

        cout << "\n--- JUGANDO GRUPO " << grupos[i]->getLetra() << " ---" << endl;
        for(int c=0; c<6; c++) {
            iteraciones++; Partido* p = new Partido(eq[cruces[c][0]], eq[cruces[c][1]], fecha, false);
            p->simular(); p->imprimirResultado(); delete p;
        }
    }
    cout << "\n[SISTEMA] Fase de grupos completada. [METRICA] Iteraciones: " << iteraciones << endl;
}

void Mundial::mostrarTablasPosiciones() {
    int iteraciones = 0; cout << "\n=== TABLAS DE POSICIONES OFICIALES ===" << endl;
    for (int i = 0; i < 12; i++) {
        iteraciones++;
        cout << "\nGRUPO " << grupos[i]->getLetra() << "\n------------------------------------------------\nEQUIPO                 | PTS | GF | GC | DIF\n------------------------------------------------" << endl;
        Equipo* eq[4];
        for(int j=0; j<4; j++) { iteraciones++; eq[j] = grupos[i]->getEquipo(j); }

        for(int a=0; a<3; a++){
            for(int b=0; b<3-a; b++){
                iteraciones++;
                if( *eq[b] < *eq[b+1] ) { Equipo* temp = eq[b]; eq[b] = eq[b+1]; eq[b+1] = temp; }
            }
        }

        for (int j = 0; j < 4; j++) {
            iteraciones++; if(eq[j] == nullptr) continue;
            int dif = eq[j]->getGolesFavorTorneo() - eq[j]->getGolesContraTorneo();
            cout << eq[j]->getNombrePais();
            int espacios = 22 - m_strlen(eq[j]->getNombrePais());
            for(int e=0; e<espacios; e++) { iteraciones++; cout << " "; }
            cout << " |  "; if (eq[j]->getPuntosFaseGrupos() < 10) cout << " "; cout << eq[j]->getPuntosFaseGrupos() << "  | ";
            if (eq[j]->getGolesFavorTorneo() < 10) cout << " "; cout << eq[j]->getGolesFavorTorneo() << " | ";
            if (eq[j]->getGolesContraTorneo() < 10) cout << " "; cout << eq[j]->getGolesContraTorneo() << " |  ";
            if (dif >= 0 && dif < 10) cout << " "; cout << dif << endl;
        }
    }
    cout << "\n[METRICA] Iteraciones de ordenamiento: " << iteraciones << endl;
}

void Mundial::simularEliminatorias() {
    int iteraciones = 0;

    // Instanciamos dinámicamente tu clase
    Eliminatoria* faseEliminatoria = new Eliminatoria();

    // Le pasamos los datos por referencia y delegamos la tarea
    faseEliminatoria->ejecutarEliminatorias(this->grupos, this->podio, iteraciones);

    delete faseEliminatoria; // Limpiamos memoria

    cout << "[METRICA] Iteraciones totales en eliminatorias: " << iteraciones << endl;
}

void Mundial::generarReporteFinal() {
    int iteraciones = 0;
    if (this->podio[0] == nullptr) { cout << "[ERROR] Simula las eliminatorias primero." << endl; return; }

    cout << "\n==================================================\n           ESTADISTICAS FINALES DEL TORNEO\n==================================================" << endl;
    cout << "1. RANKING TOP 4:\n   CAMPEON: " << podio[0]->getNombrePais() << "\n   Subcampeon: " << podio[1]->getNombrePais()
         << "\n   Tercer Puesto: " << podio[2]->getNombrePais() << "\n   Cuarto Puesto: " << podio[3]->getNombrePais() << endl;

    Jugador** todosJugadores = new Jugador*[48 * 26]; int idx = 0;
    for(int i=0; i<48; i++) { iteraciones++; for(int j=0; j<26; j++) { iteraciones++; todosJugadores[idx] = todosLosEquipos[i]->getJugador(j); idx++; } }
    for(int a=0; a<idx-1; a++){
        for(int b=0; b<idx-a-1; b++){
            iteraciones++; if(todosJugadores[b]->getStats()->getGoles() < todosJugadores[b+1]->getStats()->getGoles()) { Jugador* temp = todosJugadores[b]; todosJugadores[b] = todosJugadores[b+1]; todosJugadores[b+1] = temp; }
        }
    }

    cout << "\n2. TOP 3 GOLEADORES:" << endl;
    for(int i=0; i<3; i++) cout << "   " << i+1 << ". " << todosJugadores[i]->getNombreCompleto() << " - " << todosJugadores[i]->getStats()->getGoles() << " goles." << endl;

    cout << "\n3. MAXIMO GOLEADOR DEL CAMPEON:" << endl;
    Jugador* goleadorCampeon = podio[0]->getJugador(0);
    for(int i=1; i<26; i++) { iteraciones++; if(podio[0]->getJugador(i)->getStats()->getGoles() > goleadorCampeon->getStats()->getGoles()) goleadorCampeon = podio[0]->getJugador(i); }
    cout << "   " << goleadorCampeon->getNombreCompleto() << " (" << goleadorCampeon->getStats()->getGoles() << " goles)\n[METRICA] Iteraciones: " << iteraciones << "\n==================================================\n" << endl;
    delete[] todosJugadores;
}

void Mundial::guardarHistoricoJugadores() {
    int iteraciones = 0; cout << "[SISTEMA] Exportando base de datos..." << endl;
    ofstream archivo("C:\\Users\\SANTIAGO\\Desktop\\Ing.Electronica_UdeA\\Semestre 2\\Informatica2\\Desafio2\\Desafio_2\\UdeaWorldCup\\historico_jugadores_actualizado.csv");
    if (!archivo.is_open()) return;

    archivo << "Pais,Camiseta,Nombres,Apellidos,GolesTotales,AmarillasTotales,RojasTotales,MinutosJugados\n";
    for (int i = 0; i < 48; i++) {
        iteraciones++;
        for (int j = 0; j < 26; j++) {
            iteraciones++; Jugador* jug = todosLosEquipos[i]->getJugador(j); Estadistica* st = jug->getStats();
            archivo << todosLosEquipos[i]->getNombrePais() << "," << jug->getNumCamiseta() << "," << jug->getNombres() << ","
                    << jug->getApellidos() << "," << st->getGoles() << "," << st->getTarjetasAmarillas() << ","
                    << st->getTarjetasRojas() << "," << st->getMinutos() << "\n";
        }
    }
    archivo.close(); cout << "[SISTEMA] Exportacion exitosa. [METRICA] Iteraciones: " << iteraciones << endl;
}
