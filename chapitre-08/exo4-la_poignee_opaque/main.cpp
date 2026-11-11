
#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

int main() {
    int images;
    int n;

    std::cin >> images;
    std::cin >> n;

    std::vector<std::uint64_t> poignees(images > 0 ? images : 0);
    std::vector<bool> occupe(images > 0 ? images : 0, false);

    int posees = 0;

    for (int i = 0; i < n; ++i) {
        std::string commande;
        int index;

        std::cin >> commande >> index;

        if (commande == "POSE") {
            std::uint64_t valeur;
            std::cin >> valeur;

            if (index < 0 || index >= images) {
                std::cout << "HORS ANNEAU\n";
            } else {
                if (!occupe[index]) {
                    occupe[index] = true;
                    ++posees;
                }

                poignees[index] = valeur;
            }
        }
        else if (commande == "LIT") {
            if (index < 0 || index >= images || !occupe[index]) {
                std::cout << "VIDE\n";
            } else {
                std::cout << poignees[index] << '\n';
            }
        }
    }

    std::cout << "POSEES " << posees << '\n';

    return 0;
}
