#include <iostream>

int main() {
    int n;
    if (!(std::cin >> n)) {
        return 0;
    }

    int prev_courant = 0;
    int fronts = 0;
    int niveaux = 0;

    for (int frame = 1; frame <= n; ++frame) {
        int presse = 0;
        int lie = 0;
        std::cin >> presse >> lie;

        int actif = lie;
        int courant = (actif == 1) ? presse : 0;
        int change = (courant != prev_courant) ? 1 : 0;

        if (courant == 1 && change == 1) {
            ++fronts;
        }
        if (courant == 1) {
            ++niveaux;
        }

        std::cout << frame << ' ' << courant << ' ' << change << ' ' << actif << '\n';

        prev_courant = courant;
    }

    std::cout << "FRONTS " << fronts << '\n';
    std::cout << "NIVEAUX " << niveaux << '\n';

    return 0;
}
