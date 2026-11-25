#include <iostream>
#include <string>

int main() {
    // Première ligne : rendu deformation reprojection seuil
    int rendu, deformation, reprojection, seuil;
    std::cin >> rendu >> deformation >> reprojection >> seuil;

    int n;
    std::cin >> n;
    int gagnes = 0, perdus = 0;
    for (int i = 0; i < n; i++) {
        std::string nom;
        int pixels;
        std::cin >> nom >> pixels;

        // Calcul dans la scène : 3 étapes, troncature entière à chaque étape
        int e1 = (pixels * rendu) / 1000;
        int e2 = (e1 * deformation) / 1000;
        int e3 = (e2 * reprojection) / 1000;
        // En couche quad : garde pixels d'origine (pleine résolution)
        int quad = pixels;

        std::string scene_v = (e3 >= seuil) ? "LISIBLE" : "FLOU";
        std::string quad_v  = (quad >= seuil) ? "LISIBLE" : "FLOU";

        std::cout << nom << " " << e3 << " " << quad << " " << scene_v << " " << quad_v << "\n";

        if (scene_v == "FLOU" && quad_v == "LISIBLE") gagnes++;
        if (scene_v == "LISIBLE" && quad_v == "FLOU") perdus++;
    }
    std::cout << "GAGNES " << gagnes << "\n";
    std::cout << "PERDUS " << perdus << "\n";
    return 0;
}
