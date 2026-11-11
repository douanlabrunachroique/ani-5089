
#include <iostream>
#include <string>

int main() {
    int largeurFenetre;
    int hauteurFenetre;
    int n;

    std::cin >> largeurFenetre >> hauteurFenetre;
    std::cin >> n;

    int bloquantes = 0;

    for (int i = 0; i < n; ++i) {
        std::string nom;
        int cible;
        int taille;
        int largeurCible;
        int hauteurCible;

        std::cin >> nom >> cible >> taille
                 >> largeurCible >> hauteurCible;

        int largeurReelle = largeurFenetre;
        int hauteurReelle = hauteurFenetre;

        std::string verdict;

        if (cible == 0) {
            verdict = "PAS RELIEE";
        }
        else if (taille == 1) {
            largeurReelle = largeurCible;
            hauteurReelle = hauteurCible;
            verdict = "OK";
        }
        else {
            if (largeurFenetre != largeurCible ||
                hauteurFenetre != hauteurCible) {
                verdict = "BLOQUE";
                ++bloquantes;
            }
            else {
                verdict = "SANS EFFET";
            }
        }

        std::cout << nom << " "
                  << largeurReelle << " "
                  << hauteurReelle << " "
                  << verdict << '\n';
    }

    std::cout << "BLOQUANTES " << bloquantes << '\n';

    return 0;
}
