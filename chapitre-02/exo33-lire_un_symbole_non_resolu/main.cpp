#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

struct Prefixe {
    string prefixe;
    string module;
};

int main() {
    int P;
    cin >> P;
    cin.ignore();

    vector<Prefixe> prefixeModules;

    for (int i = 0; i < P; ++i) {
        string prefixe;
        string module;

        cin >> prefixe >> module;

        prefixeModules.push_back({prefixe, module});
    }

    int L;
    cin >> L;
    cin.ignore();

    set<string> modules;
    int inconnus = 0;

    const string marqueur = "undefined reference to '";

    for (int i = 0; i < L; ++i) {
        string ligne;
        getline(cin, ligne);

        size_t debut = ligne.find(marqueur);

        if (debut == string::npos) {
            continue;
        }

        debut += marqueur.length();

        size_t fin = ligne.find('\'', debut);

        if (fin == string::npos) {
            continue;
        }

        string symbole = ligne.substr(debut, fin - debut);

        string meilleurModule;
        size_t longueurMax = 0;

        for (const Prefixe& element : prefixeModules) {
            if (symbole.rfind(element.prefixe, 0) == 0) {
                if (element.prefixe.length() > longueurMax) {
                    longueurMax = element.prefixe.length();
                    meilleurModule = element.module;
                }
            }
        }

        if (longueurMax > 0) {
            modules.insert(meilleurModule);
        } else {
            ++inconnus;
        }
    }

    for (const string& module : modules) {
        cout << module << '\n';
    }

    if (inconnus > 0) {
        cout << "INCONNU " << inconnus << '\n';
    }

    return 0;
}
