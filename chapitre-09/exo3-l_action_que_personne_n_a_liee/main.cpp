#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

struct Action {
    std::string nom;
    std::string usage;
};

int main() {
    int a;
    if (!(std::cin >> a)) {
        return 0;
    }

    std::vector<Action> actions(a);
    for (int i = 0; i < a; ++i) {
        std::cin >> actions[i].nom >> actions[i].usage;
    }

    int l;
    if (!(std::cin >> l)) {
        return 0;
    }

    std::unordered_set<std::string> provided;
    for (int i = 0; i < l; ++i) {
        std::string u;
        std::cin >> u;
        provided.insert(u);
    }

    int mortes = 0;
    for (const auto &action : actions) {
        bool is_active = (provided.find(action.usage) != provided.end());
        if (is_active) {
            std::cout << action.nom << " ACTIVE\n";
        } else {
            std::cout << action.nom << " MORTE\n";
            ++mortes;
        }
    }

    std::cout << "MORTES " << mortes << '\n';

    return 0;
}
