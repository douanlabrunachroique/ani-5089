// Accumulateur de mouvement de souris : ajoute a chaque evenement brut,
// et se vide a chaque image.

struct Delta {
    int x;
    int y;
};

class AccumulateurSouris {
public:
    // Rappel appele a chaque evenement brut de souris : on AJOUTE (on n'ecrase pas)
    void SurEvenementBrut(int dx, int dy) {
        totalX += dx;
        totalY += dy;
    }

    // Appele UNE fois par image : rend le total accumule puis REMET A ZERO,
    // meme si rien n'a bouge pendant cette image.
    Delta Consommer() {
        Delta resultat{totalX, totalY};
        totalX = 0;
        totalY = 0;
        return resultat;
    }

private:
    int totalX = 0;
    int totalY = 0;
};
