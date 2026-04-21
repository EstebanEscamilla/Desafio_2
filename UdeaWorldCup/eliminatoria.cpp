#include <cmath> // Necesario para la función pow()

// Definimos las constantes del desafío
const double MU = 1.35;
const double ALPHA = 0.6;
const double BETA = 0.4;

Equipo* jugarPartidoUnico(Equipo* e1, Equipo* e2) {
    // Formulas de goles esperados de A y B
    double lambda1 = MU * pow((e1->getGF() / MU), ALPHA) * pow((e2->getGC() / MU), BETA);
    double lambda2 = MU * pow((e2->getGF() / MU), ALPHA) * pow((e1->getGC() / MU), BETA);

    // Convertir los goles a enteros
    int goles1 = round(lambda1);
    int goles2 = round(lambda2);

    cout << "[ESTADÍSTICA] " << e1->getNombrePais() << " (Exp: " << lambda1 << ") vs "
         << e2->getNombrePais() << " (Exp: " << lambda2 << ")" << endl;

    // 4. LÓGICA DE DESEMPATE (La cláusula del Ranking FIFA)
    if (goles1 == goles2) {
        cout << " -> EMPATE TÉCNICO (" << goles1 << "-" << goles2 << "). Aplicando sesgo por Ranking FIFA..." << endl;

        if (e1->getRankingFIFA() < e2->getRankingFIFA()) {
            goles1++; // Ajuste manual: +1 al favorito
            cout << " -> +1 gol para " << e1->getNombrePais() << " por mejor Ranking FIFA." << endl;
        } else {
            goles2++;
            cout << " -> +1 gol para " << e2->getNombrePais() << " por mejor Ranking FIFA." << endl;
        }
    }

    cout << "[RESULTADO FINAL] " << e1->getNombrePais() << " " << goles1 << " - " << goles2 << " " << e2->getNombrePais() << endl;

    return (goles1 > goles2) ? e1 : e2;
}
