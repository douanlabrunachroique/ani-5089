#include <iostream>
#include <string>

int main() {
    int p, f;
    std::cin >> p >> f;

    int compteur = 0;   // tours consecutifs sans releve
    int premier = 0;    // premier tour ou la fenetre est declaree morte (0 = jamais)

    for (int tour = 1; tour <= f; tour++) {
        std::string action;
        std::cin >> action;

        if (action == "releve") {
            compteur = 0;
        } else if (action == "travaille") {
            compteur++;
        }

        // morte des que le compteur ATTEINT p (>=), et le reste tant qu'on ne releve pas
        bool morte = (compteur >= p);
        if (morte && premier == 0) {
            premier = tour;
        }

        std::cout << compteur << " " << (morte ? "MORTE" : "VIVANTE") << "\n";
    }

    std::cout << "PREMIER " << premier << "\n";
    return 0;
}
