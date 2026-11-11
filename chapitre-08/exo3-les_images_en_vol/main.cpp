
#include <iostream>
#include <string>

int main() {
    int vol;
    int n;

    std::cin >> vol;
    std::cin >> n;

    int enVol = 0;
    int bloque = 0;

    for (int i = 1; i <= n; ++i) {
        std::string commande;
        std::cin >> commande;

        std::string resultat = "PASSE";

        if (commande == "SOUMET") {
            if (enVol >= vol) {
                resultat = "ATTEND";

                if (bloque == 0) {
                    bloque = i;
                }
            } else {
                ++enVol;
            }
        }
        else if (commande == "FINI") {
            if (enVol > 0) {
                --enVol;
            }
        }

        std::cout << i << " "
                  << commande << " "
                  << enVol << " "
                  << resultat << '\n';
    }

    std::cout << "BLOQUE " << bloque << '\n';

    return 0;
}
