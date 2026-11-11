
#include <iostream>
#include <string>

int main() {
    int n;
    std::cin >> n;

    bool acquise = false;
    bool rendue = false;
    int fautes = 0;

    for (int i = 1; i <= n; ++i) {
        std::string appel;
        std::cin >> appel;

        std::string resultat = "OK";

        if (appel == "ACQUIERT") {
            if (acquise) {
                resultat = "DEJA ACQUISE";
                ++fautes;
            } else {
                acquise = true;
            }
        }
        else if (appel == "DESSINE") {
            if (!acquise) {
                resultat = "PAS ACQUISE";
                ++fautes;
            }
        }
        else if (appel == "REND") {
            if (!acquise) {
                resultat = "RIEN ACQUIS";
                ++fautes;
            } else {
                acquise = false;
                rendue = true;
            }
        }
        else if (appel == "SOUMET") {
            if (!rendue) {
                resultat = "PAS RENDUE";
                ++fautes;
            } else {
                rendue = false;
            }
        }

        std::cout << i << " " << appel << " "
                  << resultat << '\n';
    }

    std::cout << "FAUTES " << fautes << '\n';

    return 0;
}
