#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Appareil {
    string serie;
    string etat;
    string modele;
};

int main() {
    int D;
    cin >> D;

    vector<Appareil> appareils;

    for (int i = 0; i < D; ++i) {
        Appareil appareil;
        cin >> appareil.serie >> appareil.etat >> appareil.modele;
        appareils.push_back(appareil);
    }

    string cible;
    cin >> cible;

    // Une cible précise est demandée.
    if (cible != "-") {
        for (const Appareil& appareil : appareils) {
            if (appareil.serie == cible) {
                if (appareil.etat != "device") {
                    cout << "ERREUR " << appareil.serie
                         << " est " << appareil.etat << '\n';
                    return 0;
                }

                cout << appareil.serie << '\n';
                return 0;
            }
        }

        cout << "ERREUR cible introuvable\n";
        return 0;
    }

    // Aucune cible : on garde uniquement les appareils prêts.
    vector<string> disponibles;

    for (const Appareil& appareil : appareils) {
        if (appareil.etat == "device") {
            disponibles.push_back(appareil.serie);
        }
    }

    if (disponibles.empty()) {
        cout << "ERREUR aucun appareil\n";
        return 0;
    }

    if (disponibles.size() == 1) {
        cout << disponibles[0] << '\n';
        return 0;
    }

    sort(disponibles.begin(), disponibles.end());

    cout << "ERREUR plusieurs appareils\n";

    for (const string& serie : disponibles) {
        cout << serie << '\n';
    }

    return 0;
}
