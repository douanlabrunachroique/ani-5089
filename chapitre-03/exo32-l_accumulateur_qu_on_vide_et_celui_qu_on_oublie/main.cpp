#include <iostream>
#include <string>

int main() {
    int n;
    std::cin >> n;

    long long dx = 0, dy = 0;   // accumulateur : ajoute, remis a zero a chaque image
    long long bx = 0, by = 0;   // moteur defectueux : ecrase, jamais remis a zero

    for (int i = 0; i < n; i++) {
        std::string commande;
        std::cin >> commande;

        if (commande == "bouge") {
            long long mx, my;
            std::cin >> mx >> my;
            dx += mx;
            dy += my;
            bx = mx;
            by = my;
        } else if (commande == "image") {
            std::cout << dx << " " << dy << " " << bx << " " << by << "\n";
            dx = 0;
            dy = 0;
        }
    }
    return 0;
}
