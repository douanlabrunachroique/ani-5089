#include <iostream>
#include "NkWindow.h"   // adapter a l'en-tete de la bibliotheque fenetre du cours

int main() {
    // 1. Creer la fenetre
    Window fenetre;
    fenetre.Create("Fenetre nue", 800, 600);

    // 2. Verifier que la fenetre est valide AVANT de boucler
    if (!fenetre.IsValid()) {
        std::cerr << "Erreur : fenetre invalide\n";
        return 1;
    }

    // 3. Boucle principale : relever les messages a chaque tour
    while (fenetre.IsOpen()) {
        fenetre.PollEvents();
    }

    return 0;
}
