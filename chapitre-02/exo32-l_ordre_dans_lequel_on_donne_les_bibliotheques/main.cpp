#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>

using namespace std;

int main() {
    int n;
    cin >> n;

    map<string, vector<string>> dependances;

    for (int i = 0; i < n; ++i) {
        string module;
        cin >> module;

        string besoin;
        string ligne;
        getline(cin, ligne);

        dependances[module];

        size_t pos = 0;
        while (pos < ligne.size()) {
            while (pos < ligne.size() && ligne[pos] == ' ') {
                ++pos;
            }

            if (pos >= ligne.size()) {
                break;
            }

            size_t debut = pos;
            while (pos < ligne.size() && ligne[pos] != ' ') {
                ++pos;
            }

            besoin = ligne.substr(debut, pos - debut);
            dependances[module].push_back(besoin);
        }
    }

    int m;
    cin >> m;

    set<string> necessaires;
    vector<string> projets(m);

    for (int i = 0; i < m; ++i) {
        cin >> projets[i];
    }

    // Recherche de toutes les dépendances transitives.
    vector<string> a_traiter = projets;

    while (!a_traiter.empty()) {
        string module = a_traiter.back();
        a_traiter.pop_back();

        if (necessaires.count(module)) {
            continue;
        }

        necessaires.insert(module);

        for (const string& besoin : dependances[module]) {
            a_traiter.push_back(besoin);
        }
    }

    // Compte de combien de modules dépendent de chaque module.
    map<string, int> compte;

    for (const string& module : necessaires) {
        compte[module] = 0;
    }

    for (const string& module : necessaires) {
        for (const string& besoin : dependances[module]) {
            if (necessaires.count(besoin)) {
                ++compte[besoin];
            }
        }
    }

    // Les modules dont personne ne dépend peuvent être placés en premier.
    set<string> disponibles;

    for (const auto& element : compte) {
        if (element.second == 0) {
            disponibles.insert(element.first);
        }
    }

    vector<string> ordre;

    while (!disponibles.empty()) {
        // set trie automatiquement par ordre alphabétique.
        auto it = disponibles.begin();
        string module = *it;
        disponibles.erase(it);

        ordre.push_back(module);

        // Retirer ce module des besoins de ses dépendants.
        for (const string& besoin : dependances[module]) {
            if (!necessaires.count(besoin)) {
                continue;
            }

            --compte[besoin];

            if (compte[besoin] == 0) {
                disponibles.insert(besoin);
            }
        }
    }

    if (ordre.size() != necessaires.size()) {
        cout << "CYCLE\n";
        return 0;
    }

    for (const string& module : ordre) {
        cout << module << '\n';
    }

    return 0;
}
