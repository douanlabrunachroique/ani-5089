#include <iostream>
#include <string>
#include <cstdlib>

int main() {
    int images, n;
    std::cin >> images >> n;

    int suivantG = 0;
    int suivantD = 0;

    int emprunteeG = -1;
    int emprunteeD = -1;

    int rendusG = 0;
    int rendusD = 0;

    int desync = 0;

    for (int tour = 1; tour <= n; ++tour) {
        char oeil;
        std::string commande;
        std::cin >> oeil >> commande;

        int& suivant = (oeil == 'G') ? suivantG : suivantD;
        int& empruntee = (oeil == 'G') ? emprunteeG : emprunteeD;
        int& rendus = (oeil == 'G') ? rendusG : rendusD;

        if (commande == "EMPRUNTE") {
            if (empruntee != -1) {
                std::cout << tour << " " << oeil << " "
                          << commande << " REFUSE\n";
            } else {
                empruntee = suivant;
                std::cout << tour << " " << oeil << " "
                          << commande << " " << empruntee << '\n';
            }
        } else if (commande == "REND") {
            if (empruntee == -1) {
                std::cout << tour << " " << oeil << " "
                          << commande << " REFUSE\n";
            } else {
                std::cout << tour << " " << oeil << " "
                          << commande << " " << empruntee << '\n';

                empruntee = -1;
                suivant = (suivant + 1) % images;
                ++rendus;
            }
        }

        int difference = std::abs(rendusG - rendusD);

        if (difference > 1 && desync == 0) {
            desync = tour;
        }
    }

    int decalage = std::abs(rendusG - rendusD);

    std::cout << "DECALAGE " << decalage << '\n';
    std::cout << "DESYNC " << desync << '\n';

    return 0;
}
