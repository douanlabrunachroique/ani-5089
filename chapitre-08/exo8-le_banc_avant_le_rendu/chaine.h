#ifndef CHAINE_H
#define CHAINE_H

class Chaine {
public:
    static const int MAX_IMAGES = 3;

private:
    int taille;
    int suivant;
    int imageEmpruntee;
    bool empruntEnCours;
    bool valide;

public:
    explicit Chaine(int nombreImages)
        : taille(nombreImages),
          suivant(0),
          imageEmpruntee(-1),
          empruntEnCours(false),
          valide(nombreImages > 0 && nombreImages <= MAX_IMAGES) {
    }

    bool estValide() const {
        return valide;
    }

    bool emprunter(int& index) {
        if (!valide || empruntEnCours) {
            return false;
        }

        imageEmpruntee = suivant;
        empruntEnCours = true;
        index = imageEmpruntee;

        return true;
    }

    bool rendre(int& index) {
        if (!valide || !empruntEnCours) {
            return false;
        }

        index = imageEmpruntee;
        empruntEnCours = false;
        imageEmpruntee = -1;

        suivant = (suivant + 1) % taille;

        return true;
    }
};

#endif
