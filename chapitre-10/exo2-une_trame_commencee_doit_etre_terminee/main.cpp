#include <iostream>
#include <string>

int main() {
    int n;
    std::cin >> n;
    // States: 0=REPOS, 1=ATTENDUE, 2=COMMENCEE
    int state = 0;
    int fautes = 0;
    int bloque = 0;
    for (int i = 1; i <= n; i++) {
        std::string geste;
        std::cin >> geste;
        std::string fault = "";
        if (geste == "ATTEND") {
            if (state == 0) {
                state = 1;
            } else if (state == 1) {
                fault = "DEJA ATTENDUE";
            } else { // state == 2
                fault = "TRAME EN COURS";
                if (bloque == 0) bloque = i;
            }
        } else if (geste == "COMMENCE") {
            if (state == 1) {
                state = 2;
            } else if (state == 0) {
                fault = "PAS ATTENDUE";
            } else { // state == 2
                fault = "DEJA COMMENCEE";
            }
        } else { // FINIT
            if (state == 2) {
                state = 0;
            } else {
                fault = "PAS COMMENCEE";
            }
        }
        if (fault.empty()) {
            std::cout << i << " " << geste << " OK\n";
        } else {
            std::cout << i << " " << geste << " " << fault << "\n";
            fautes++;
        }
    }
    std::cout << "FAUTES " << fautes << "\n";
    std::cout << "BLOQUE " << bloque << "\n";
    return 0;
}
