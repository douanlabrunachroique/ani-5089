#include <iostream>
#include <string>

int main() {
    int hauteur_yeux;
    std::cin >> hauteur_yeux;
    int n;
    std::cin >> n;
    int decalees = 0;
    for (int i = 0; i < n; i++) {
        std::string nom, espace_pose, espace_couche;
        std::cin >> nom >> espace_pose >> espace_couche;
        // STAGE a son origine au plancher, LOCAL a la hauteur des yeux
        // Si pose en STAGE declaree en LOCAL : compositor croit origine = yeux -> remonte de hauteur_yeux -> LEVITATION
        // Si pose en LOCAL declaree en STAGE : descend -> ENTERRE
        int decalage = 0;
        std::string verdict;
        if (espace_pose == espace_couche) {
            decalage = 0;
            // verdict OK meme si hauteur nulle
            verdict = "OK";
        } else if (espace_pose == "STAGE" && espace_couche == "LOCAL") {
            // poses en STAGE, couche declare LOCAL : compositor remonte de hauteur_yeux
            decalage = hauteur_yeux;
            verdict = "LEVITATION";
        } else {
            // poses en LOCAL, couche declare STAGE : descend
            decalage = -hauteur_yeux;
            verdict = "ENTERRE";
        }
        std::cout << nom << " " << decalage << " " << verdict << "\n";
        if (verdict != "OK") decalees++;
    }
    std::cout << "DECALEES " << decalees << "\n";
    return 0;
}
