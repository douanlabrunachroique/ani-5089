#include <iostream>
#include <string>

int main() {
    int n = 0;
    if (!(std::cin >> n)) {
        return 0;
    }

    int fautes = 0;

    for (int i = 0; i < n; ++i) {
        std::string nom;
        std::string intention;
        std::string pose;
        std::cin >> nom >> intention >> pose;

        if (intention == "TENIR" && pose == "GRIP") {
            std::cout << nom << " OK\n";
        } else if (intention == "POINTER" && pose == "AIM") {
            std::cout << nom << " OK\n";
        } else if (intention == "TENIR" && pose == "AIM") {
            std::cout << nom << " FLOTTE\n";
            ++fautes;
        } else if (intention == "POINTER" && pose == "GRIP") {
            std::cout << nom << " PART DE TRAVERS\n";
            ++fautes;
        }
    }

    std::cout << "FAUTES " << fautes << '\n';

    return 0;
}
