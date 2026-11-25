// soumettre.cpp - Exercice 9 : La pose du rendu contre la pose fraiche
//
// Version juste  : on garde les vues au moment du rendu et on resoumet telles quelles.
// Version fautive: on redemande les vues juste avant de soumettre (pose fraiche).
//                  La version fautive est mise en commentaire ci-dessous.

#include <iostream>

// Simule une vue (matrice 4x4 simplifiee)
struct Vue {
    float mat[16];
};

// Simule "obtenir les vues courantes"
static float head_angle = 0.0f; // en degres

Vue get_vue_gauche() {
    Vue v = {};
    v.mat[0] = head_angle; // on stocke l'angle comme marqueur
    return v;
}

Vue get_vue_droite() {
    Vue v = {};
    v.mat[0] = head_angle;
    return v;
}

void simuler_rendu(const Vue& /*vg*/, const Vue& /*vd*/) {
    // dessin de la scene ici (non simule)
}

void soumettre_couche(const Vue& vg, const Vue& vd) {
    std::cout << "pose_vg=" << vg.mat[0] << " pose_vd=" << vd.mat[0] << "\n";
}

int main() {
    // --- VERSION JUSTE ---
    // On capture les vues avant le rendu, on les reutilise pour soumettre.
    Vue vg_rendu = get_vue_gauche();
    Vue vd_rendu = get_vue_droite();

    simuler_rendu(vg_rendu, vd_rendu);

    // La tete bouge pendant le rendu
    head_angle += 1.5f; // 1.5 degre par trame a 72 fps

    // On resoumet avec la pose du rendu (juste)
    soumettre_couche(vg_rendu, vd_rendu);

    // --- VERSION FAUTIVE (en commentaire) ---
    // La version ci-dessous redemande les vues APRES le rendu.
    // Le compositeur recoit la pose fraiche, pas la pose du rendu.
    // La reprojection calcule la correction entre les deux poses,
    // mais comme la couche est deja alignee sur la pose fraiche,
    // la correction est appliquee deux fois : la scene glisse.
    //
    // Vue vg_fraiche = get_vue_gauche();
    // Vue vd_fraiche = get_vue_droite();
    // soumettre_couche(vg_fraiche, vd_fraiche);

    return 0;
}
