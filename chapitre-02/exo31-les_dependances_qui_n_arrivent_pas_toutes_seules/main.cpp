
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>

using namespace std;

int main() {
    int N;
    cin >> N;
    cin.ignore();

    map<string, vector<string>> dependances;

    for (int i = 0; i < N; ++i) {
        string ligne;
        getline(cin, ligne);

        stringstream ss(ligne);
        string module;

        if (!(ss >> module)) {
            continue;
        }

        string besoin;
        while (ss >> besoin) {
            dependances[module].push_back(besoin);
        }
    }

    int M;
    cin >> M;
    cin.ignore();

    string ligne;
    getline(cin, ligne);

    stringstream ss(ligne);

    set<string> resultats;
    vector<string> a_traiter;

    string module;
    while (ss >> module) {
        if (resultats.insert(module).second) {
            a_traiter.push_back(module);
        }
    }

    size_t position = 0;

    while (position < a_traiter.size()) {
        string courant = a_traiter[position];
        ++position;

        auto it = dependances.find(courant);

        if (it != dependances.end()) {
            for (const string& besoin : it->second) {
                if (resultats.insert(besoin).second) {
                    a_traiter.push_back(besoin);
                }
            }
        }
    }

    for (const string& nom : resultats) {
        cout << nom << '\n';
    }

    return 0;
}

