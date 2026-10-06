#include <iostream>

int main() {
    int n;
    std::cin >> n;

    int lisibles = 0;
    for (int i = 0; i < n; i++) {
        long long largeur, hauteur, echelle, champ;
        std::cin >> largeur >> hauteur >> echelle >> champ;

        // dimensions reelles, en division entiere
        long long largeurReelle = largeur * echelle / 100;
        long long hauteurReelle = hauteur * echelle / 100;

        // pixels par degre, arrondi a l'entier le plus proche (largeur REELLE)
        long long pixelsParDegre = (largeurReelle + champ / 2) / champ;

        std::cout << largeurReelle << " " << hauteurReelle << " " << pixelsParDegre << "\n";

        if (pixelsParDegre >= 15) {
            lisibles++;
        }
    }

    std::cout << "LISIBLE " << lisibles << "\n";
    return 0;
}
