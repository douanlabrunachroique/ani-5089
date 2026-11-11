
#include <iostream>
#include <string>

int main() {
    int images;
    int n;

    std::cin >> images;
    std::cin >> n;

    int suivant = 0;
    int empruntee = -1;
    int prets = 0;

    for (int i = 1; i <= n; ++i) {
        std::string commande;
        std::cin >> commande;

        if (commande == "EMPRUNTE") {
            if (empruntee == -1) {
                empruntee = suivant;
                ++prets;

                std::cout << i << " EMPRUNTE "
                          << empruntee << '\n';
            } else {
                std::cout << i << " EMPRUNTE REFUSE\n";
            }
        }
        else if (commande == "REND") {
            if (empruntee != -1) {
                std::cout << i << " REND "
                          << empruntee << '\n';

                empruntee = -1;
                suivant = (suivant + 1) % images;
            } else {
                std::cout << i << " REND REFUSE\n";
            }
        }
    }

    std::cout << "PRETS " << prets << '\n';

    return 0;
}
