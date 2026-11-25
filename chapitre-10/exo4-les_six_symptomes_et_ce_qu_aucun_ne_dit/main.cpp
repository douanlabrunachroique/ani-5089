#include <iostream>
#include <string>
#include <map>

int main() {
    // symptome -> cause
    std::map<std::string, std::string> table = {
        {"BLOQUE_AU_WAIT",        "FIN DE TRAME"},
        {"PAS_DE_REPRISE",        "FIN SANS RENDU"},
        {"OEIL_NOIR",             "CHAINE MANQUANTE"},
        {"TREMBLEMENT",           "MAUVAIS INSTANT"},
        {"CORRECTION_DE_TRAVERS", "POSE FRAICHE"},
        {"SCENE_DECALEE",         "MAUVAIS ESPACE"}
    };

    int n;
    std::cin >> n;
    int diagnostiques = 0, inconnus = 0;
    for (int i = 0; i < n; i++) {
        std::string symptome;
        std::cin >> symptome;
        auto it = table.find(symptome);
        if (it != table.end()) {
            std::cout << symptome << " " << it->second << "\n";
            diagnostiques++;
        } else {
            std::cout << symptome << " INCONNU\n";
            inconnus++;
        }
    }
    std::cout << "DIAGNOSTIQUES " << diagnostiques << "\n";
    std::cout << "INCONNUS " << inconnus << "\n";
    return 0;
}
