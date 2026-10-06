#include <iostream>
#include <sstream>
#include <string>

int main() {
    std::string ligne;
    std::getline(std::cin, ligne);
    int n = std::stoi(ligne);

    for (int i = 0; i < n; i++) {
        std::getline(std::cin, ligne);
        std::istringstream flux(ligne);

        // chaque touche compte au plus une fois par ligne
        bool w = false, z = false, a = false, q = false, s = false, d = false;
        std::string touche;
        while (flux >> touche) {
            if (touche == "W") w = true;
            else if (touche == "Z") z = true;
            else if (touche == "A") a = true;
            else if (touche == "Q") q = true;
            else if (touche == "S") s = true;
            else if (touche == "D") d = true;
            // toute autre touche (dont "rien") est ignoree
        }

        int avance = (w || z ? 1 : 0) - (s ? 1 : 0);
        int cote = (d ? 1 : 0) - (a || q ? 1 : 0);
        std::cout << avance << " " << cote << "\n";
    }
    return 0;
}
