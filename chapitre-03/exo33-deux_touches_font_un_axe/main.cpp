#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

int main() {
    int c;
    std::cin >> c;

    std::vector<long long> echelle(c), seuil(c);
    for (int i = 0; i < c; i++) {
        std::string nom;
        std::cin >> nom >> echelle[i] >> seuil[i];
    }

    int t;
    std::cin >> t;
    for (int tour = 0; tour < t; tour++) {
        long long somme = 0;
        for (int i = 0; i < c; i++) {
            long long brut;
            std::cin >> brut;
            long long contribution = brut * echelle[i] / 1000;
            if (std::llabs(contribution) < seuil[i]) {
                continue;
            }
            somme += contribution;
        }
        std::cout << somme << "\n";
    }
    return 0;
}
