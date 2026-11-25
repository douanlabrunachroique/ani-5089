// boucle.cpp - Exercice 10 : La boucle qui ne reprend jamais
//
// Boucle complete du chapitre : pompe d'evenements, attente, debut,
// synchronisation des actions, rendu conditionnel, fin de trame.
//
// Version fautive : la fin de trame est DANS le bloc if(shouldRender).
// Quand shouldRender est faux (casque pose), la fin de trame n'est pas
// appelee. La boucle attend la prochaine trame indefiniment : elle est bloquee.

#include <iostream>
#include <string>

int main() {
    // Simulation : 20 trames
    // shouldRender est faux aux trames 6 a 10 (pause : casque pose)
    int total = 20;

    for (int t = 1; t <= total; t++) {
        bool shouldRender = !(t >= 6 && t <= 10);

        // --- VERSION CORRIGEE ---
        // La fin de trame est HORS du test de rendu
        int rend = shouldRender ? 1 : 0;
        // fin toujours appelee
        int fin = 1;

        // --- VERSION FAUTIVE (en commentaire) ---
        // if (shouldRender) {
        //     // rendu ici
        //     fin = 1; // fin dans le if -> pas appelee si !shouldRender
        // }
        // int fin = /* jamais appele si !shouldRender */ 0;

        std::cout << "trame : " << t
                  << " rend : " << rend
                  << " debut : 1"
                  << " fin : " << fin << "\n";
    }
    return 0;
}
