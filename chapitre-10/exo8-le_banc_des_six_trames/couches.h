#pragma once
#include <cstdint>

// Structure de couche de projection : l'espace et une vue par oeil
struct CoucheProjection {
    bool espace_stage; // true = STAGE, false = LOCAL
    // Vue gauche
    float vg[16];
    // Vue droite
    float vd[16];
};
