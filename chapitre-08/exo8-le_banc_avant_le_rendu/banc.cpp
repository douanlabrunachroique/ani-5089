#include <iostream>
#include "chaine.h"

int main() {
    Chaine chaine(3);

    int index = -1;

    // Six échanges sur un anneau de trois images.
    for (int tour = 1; tour <= 6; ++tour) {
        if (chaine.emprunter(index)) {
            std::cout << tour << " EMPRUNTE " << index << '\n';
        }

        if (chaine.rendre(index)) {
            std::cout << tour << " REND " << index << '\n';
        }
    }

    // Test 1 : double emprunt.
    Chaine doubleEmprunt(3);
    doubleEmprunt.emprunter(index);

    if (!doubleEmprunt.emprunter(index)) {
        std::cout << "REFUS DOUBLE EMPRUNT\n";
    }

    // Test 2 : rendu sans emprunt.
    Chaine renduSansEmprunt(3);

    if (!renduSansEmprunt.rendre(index)) {
        std::cout << "REFUS RENDU SANS EMPRUNT\n";
    }

    // Test 3 : création d'une chaîne trop grande.
    Chaine tropGrande(Chaine::MAX_IMAGES + 1);

    if (!tropGrande.estValide()) {
        std::cout << "REFUS CHAINE TROP GRANDE\n";
    }

    return 0;
}
