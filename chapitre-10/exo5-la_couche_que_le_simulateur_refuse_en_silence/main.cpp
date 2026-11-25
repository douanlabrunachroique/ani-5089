#include <iostream>
#include <string>

int main() {
    int n;
    std::cin >> n;
    int refusees = 0, averties = 0;
    for (int i = 0; i < n; i++) {
        std::string nom;
        int commence, rend, gauche, droite;
        std::cin >> nom >> commence >> rend >> gauche >> droite;

        // Règle 1 : trame pas commencee -> REFUSEE
        if (!commence) {
            std::cout << nom << " REFUSEE\n";
            refusees++;
            continue;
        }
        // Règle 2 : ne devait pas dessiner, aucune chaîne -> OK (casque posé)
        if (!rend && !gauche && !droite) {
            std::cout << nom << " OK\n";
            continue;
        }
        // Règle 3 : ne devait pas dessiner mais au moins une chaîne présente -> COUCHE SANS RENDU
        if (!rend && (gauche || droite)) {
            std::cout << nom << " COUCHE SANS RENDU\n";
            averties++;
            continue;
        }
        // rend == 1 à partir d'ici
        // Règle 4 : devait dessiner, les deux chaînes présentes -> OK
        if (gauche && droite) {
            std::cout << nom << " OK\n";
            continue;
        }
        // Règle 5 : devait dessiner, aucune chaîne -> SOUMISSION VIDE
        if (!gauche && !droite) {
            std::cout << nom << " SOUMISSION VIDE\n";
            averties++;
            continue;
        }
        // Règle 6 : une seule chaîne manque
        if (!gauche) {
            std::cout << nom << " OEIL NOIR G\n";
        } else {
            std::cout << nom << " OEIL NOIR D\n";
        }
        averties++;
    }
    std::cout << "REFUSEES " << refusees << "\n";
    std::cout << "AVERTIES " << averties << "\n";
    return 0;
}
