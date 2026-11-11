#include <iostream>
#include <cstdint>
#include <thread>
#include <chrono>

class Renderer {
public:
    void SetFinalColorTarget(std::uint64_t handle) {
        cible = handle;
    }

    void SetRenderSizeOverride(unsigned int largeur,
                               unsigned int hauteur) {
        largeurCible = largeur;
        hauteurCible = hauteur;
    }

    bool Dessiner(unsigned int largeurFenetre,
                  unsigned int hauteurFenetre) const {
        return cible != 0 &&
               largeurCible > 0 &&
               hauteurCible > 0 &&
               largeurCible <= largeurFenetre &&
               hauteurCible <= hauteurFenetre;
    }

private:
    std::uint64_t cible = 0;
    unsigned int largeurCible = 0;
    unsigned int hauteurCible = 0;
};

int main() {
    constexpr unsigned int LARGEUR_FENETRE = 1280;
    constexpr unsigned int HAUTEUR_FENETRE = 720;

    constexpr unsigned int LARGEUR_CIBLE = 640;
    constexpr unsigned int HAUTEUR_CIBLE = 360;

    constexpr std::uint64_t POIGNEE_CIBLE = 1;

    Renderer* rendu = new Renderer();

    // Configuration de la cible hors écran.
    rendu->SetFinalColorTarget(POIGNEE_CIBLE);
    rendu->SetRenderSizeOverride(
        LARGEUR_CIBLE,
        HAUTEUR_CIBLE
    );

    if (!rendu->Dessiner(
        LARGEUR_FENETRE,
        HAUTEUR_FENETRE
    )) {
        std::cerr << "Erreur de configuration.\n";
        delete rendu;
        return 1;
    }

    // Simulation de dix images après correction.
    for (int image = 1; image <= 10; ++image) {
        std::cout << "image : " << image
                  << ", etat : dessinee\n";

        std::this_thread::sleep_for(
            std::chrono::milliseconds(10)
        );
    }

    delete rendu;

    return 0;
}
