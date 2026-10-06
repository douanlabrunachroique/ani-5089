#include <iostream>
#include <string>
#include <utility>
#include <vector>

int main() {
    int n;
    std::cin >> n;

    // registre : rappels dans l'ordre de pose (id, type)
    std::vector<std::pair<long long, std::string>> registre;

    for (int i = 0; i < n; i++) {
        std::string commande;
        std::cin >> commande;

        if (commande == "poser") {
            long long id;
            std::string type;
            std::cin >> id >> type;
            // un identifiant deja pose est retire d'abord, puis ajoute a la fin
            for (size_t k = 0; k < registre.size(); k++) {
                if (registre[k].first == id) {
                    registre.erase(registre.begin() + k);
                    break;
                }
            }
            registre.push_back({id, type});
        } else if (commande == "retirer") {
            long long id;
            std::cin >> id;
            for (size_t k = 0; k < registre.size(); k++) {
                if (registre[k].first == id) {
                    registre.erase(registre.begin() + k);
                    break;
                }
            }
        } else if (commande == "envoyer") {
            std::string type;
            std::cin >> type;
            bool premier = true;
            for (const auto& r : registre) {
                if (r.second == type) {
                    if (!premier) std::cout << " ";
                    std::cout << r.first;
                    premier = false;
                }
            }
            if (premier) std::cout << "AUCUN";
            std::cout << "\n";
        }
    }
    return 0;
}
