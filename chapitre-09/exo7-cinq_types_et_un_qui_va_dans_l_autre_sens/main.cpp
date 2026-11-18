#include <iostream>
#include <string>
#include <unordered_map>

int main() {
    int a = 0;
    if (!(std::cin >> a)) {
        return 0;
    }

    std::unordered_map<std::string, std::string> action_types;
    int entrees = 0;
    int sorties = 0;

    for (int i = 0; i < a; ++i) {
        std::string nom;
        std::string type;
        std::cin >> nom >> type;
        action_types[nom] = type;

        if (type == "HAPTIC") {
            ++sorties;
        } else if (type == "BOOL" || type == "FLOAT" || type == "VEC2" || type == "POSE") {
            ++entrees;
        }
    }

    int o = 0;
    if (!(std::cin >> o)) {
        return 0;
    }

    for (int i = 0; i < o; ++i) {
        std::string nom;
        std::string op;
        std::cin >> nom >> op;

        auto it = action_types.find(nom);
        if (it == action_types.end()) {
            // Ignored if action was not declared
            continue;
        }

        const std::string &type = it->second;
        bool is_output = (type == "HAPTIC");
        bool is_input = !is_output;

        if (op == "LIT" && is_output) {
            std::cout << nom << " LIT UNE SORTIE\n";
        } else if (op == "ECRIT" && is_input) {
            std::cout << nom << " ECRIT UNE ENTREE\n";
        }
    }

    std::cout << "ENTREES " << entrees << '\n';
    std::cout << "SORTIES " << sorties << '\n';

    return 0;
}
