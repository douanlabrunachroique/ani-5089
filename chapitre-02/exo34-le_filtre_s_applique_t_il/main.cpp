#include <iostream>
#include <string>
#include <map>
#include <sstream>

using namespace std;

int main() {
    int V;
    cin >> V;

    map<string, string> machine;

    for (int i = 0; i < V; ++i) {
        string ligne;
        cin >> ligne;

        size_t position = ligne.find('=');

        string cle = ligne.substr(0, position);
        string valeur = ligne.substr(position + 1);

        machine[cle] = valeur;
    }

    int F;
    cin >> F;
    cin.ignore();

    for (int i = 0; i < F; ++i) {
        string condition;
        getline(cin, condition);

        string terme;
        stringstream ss(condition);

        bool applique = true;

        while (ss >> terme) {
            if (terme == "&&") {
                continue;
            }

            bool inverse = false;

            if (!terme.empty() && terme[0] == '!') {
                inverse = true;
                terme = terme.substr(1);
            }

            size_t position = terme.find('=');

            string cle = terme.substr(0, position);
            string valeur = terme.substr(position + 1);

            bool vrai = false;

            auto it = machine.find(cle);

            if (it != machine.end()) {
                vrai = (it->second == valeur);
            }

            if (inverse) {
                vrai = !vrai;
            }

            if (!vrai) {
                applique = false;
            }
        }

        if (applique) {
            cout << "OUI\n";
        } else {
            cout << "NON\n";
        }
    }

    return 0;
}
