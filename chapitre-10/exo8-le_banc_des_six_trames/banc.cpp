#include <iostream>
#include "couches.h"

// Anneau de 4 images
static const int RING_SIZE = 4;

int main() {
    // 6 trames, tête tourne d'un degré par trame
    // Trames 3 et 4 (index 2 et 3) : pas de rendu
    int ring_idx = 0;
    int total_frames = 6;

    for (int t = 1; t <= total_frames; t++) {
        bool should_render = (t != 3 && t != 4);

        int on_rend = should_render ? 1 : 0;
        // nb couches soumises : 1 si on dessine, 0 sinon (trames 3 et 4 soumettent zéro couche)
        int nb_couches = should_render ? 1 : 0;
        // index d'image au moment de cette trame
        int img_idx = ring_idx;

        // Fin de trame toujours appelée
        std::cout << "trame : " << t
                  << " rend : " << on_rend
                  << " debut : 1"
                  << " fin : 1\n";

        (void)nb_couches;
        (void)img_idx;

        if (should_render) {
            ring_idx = (ring_idx + 1) % RING_SIZE;
        }
    }
    return 0;
}
