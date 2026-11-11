#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class ChaineEchange
{
private:
    struct Image
    {
        int identifiant;
    };

    std::string nom;
    std::vector<Image> images;

    int prochaineImage = 0;
    int imageEmpruntee = -1;

    bool valide = false;
    bool imagesEnregistrees = false;

    enum class Etat
    {
        DISPONIBLE,
        EMPRUNTEE,
        RENDUE
    };

    Etat etat = Etat::DISPONIBLE;

    inline static int prochainIdentifiant = 1;

public:

    ChaineEchange(
        const std::string& nomChaine,
        int largeur,
        int hauteur,
        int nombreImages
    )
    {
        nom = nomChaine;

        if (largeur <= 0 || hauteur <= 0 || nombreImages <= 0)
            return;

        for (int i = 0; i < nombreImages; i++)
        {
            Image image;
            image.identifiant = prochainIdentifiant++;
            images.push_back(image);
        }

        valide = true;
    }

    bool estValide() const
    {
        return valide;
    }

    bool enregistrerImages()
    {
        if (!valide)
            return false;

        imagesEnregistrees = true;
        return true;
    }

    int emprunterImage()
    {
        if (!valide || !imagesEnregistrees)
            return -1;

        if (etat != Etat::DISPONIBLE)
            return -1;

        imageEmpruntee = prochaineImage;
        etat = Etat::EMPRUNTEE;

        return imageEmpruntee;
    }

    bool effectuerRendu()
    {
        if (etat != Etat::EMPRUNTEE)
            return false;

        etat = Etat::RENDU;
        return true;
    }

    bool libererImage()
    {
        if (etat != Etat::RENDU)
            return false;

        etat = Etat::DISPONIBLE;
        return true;
    }

    bool soumettreImage()
    {
        if (!valide || etat != Etat::DISPONIBLE ||
            imageEmpruntee < 0)
            return false;

        prochaineImage =
            (prochaineImage + 1) %
            static_cast<int>(images.size());

        imageEmpruntee = -1;

        return true;
    }

    void detruire()
    {
        imagesEnregistrees = false;
        images.clear();

        valide = false;
        prochaineImage = 0;
        imageEmpruntee = -1;
        etat = Etat::DISPONIBLE;
    }
};


int main()
{
    const int LARGEUR = 1280;
    const int HAUTEUR = 720;

    const int NOUVELLE_LARGEUR = 1024;
    const int NOUVELLE_HAUTEUR = 600;

    const int NOMBRE_IMAGES = 3;

    std::ofstream trace("trace.txt");
    std::ofstream resize("resize.txt");

    if (!trace || !resize)
    {
        std::cerr << "Erreur d'ouverture des fichiers.\n";
        return 1;
    }

    // Création de deux chaînes indépendantes.
    ChaineEchange gauche(
        "Gauche", LARGEUR, HAUTEUR, NOMBRE_IMAGES
    );

    ChaineEchange droit(
        "Droit", LARGEUR, HAUTEUR, NOMBRE_IMAGES
    );

    if (!gauche.estValide() || !droit.estValide())
    {
        std::cerr << "Erreur de creation des chaines.\n";
        return 1;
    }

    gauche.enregistrerImages();
    droit.enregistrerImages();

    // Simulation de 30 images.
    for (int image = 1; image <= 30; image++)
    {
        // TEMPS 1 : emprunter une image pour chaque œil.
        int indexGauche = gauche.emprunterImage();
        int indexDroit = droit.emprunterImage();

        if (indexGauche < 0 || indexDroit < 0)
        {
            std::cerr << "Erreur d'emprunt.\n";
            return 1;
        }

        // TEMPS 2 : effectuer le rendu.
        if (!gauche.effectuerRendu() ||
            !droit.effectuerRendu())
        {
            std::cerr << "Erreur de rendu.\n";
            return 1;
        }

        // TEMPS 3 : libérer les images.
        if (!gauche.libererImage() ||
            !droit.libererImage())
        {
            std::cerr << "Erreur de liberation.\n";
            return 1;
        }

        // TEMPS 4 : soumettre les images.
        if (!gauche.soumettreImage() ||
            !droit.soumettreImage())
        {
            std::cerr << "Erreur de soumission.\n";
            return 1;
        }

        // Enregistrer les indices prêtés.
        trace << "image : " << image
              << ", gauche : " << indexGauche
              << ", droit : " << indexDroit
              << "\n";

        // Redimensionnement à la 15e image.
        if (image == 15)
        {
            // 1. Destruction des anciennes chaînes.
            gauche.detruire();
            resize << "Detruire la chaine gauche.\n";

            droit.detruire();
            resize << "Detruire la chaine droite.\n";

            // 2. Recréation des chaînes.
            gauche = ChaineEchange(
                "Gauche",
                NOUVELLE_LARGEUR,
                NOUVELLE_HAUTEUR,
                NOMBRE_IMAGES
            );

            resize << "Recreer la chaine gauche avec les nouvelles dimensions.\n";

            droit = ChaineEchange(
                "Droit",
                NOUVELLE_LARGEUR,
                NOUVELLE_HAUTEUR,
                NOMBRE_IMAGES
            );

            resize << "Recreer la chaine droite avec les nouvelles dimensions.\n";

            // 3. Enregistrement des nouvelles images.
            gauche.enregistrerImages();
            resize << "Enregistrer les nouvelles images de la chaine gauche.\n";

            droit.enregistrerImages();
            resize << "Enregistrer les nouvelles images de la chaine droite.\n";
        }
    }

    trace.close();
    resize.close();

    std::cout << "Simulation terminee avec succes.\n";
    std::cout << "30 images traitees.\n";

    return 0;
}
