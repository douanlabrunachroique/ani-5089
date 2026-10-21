#include <utility>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <filesystem>

#include "NKPlatform/NkPlatformDetect.h"
#include "NKWindow/NKMain.h"
#include "NKImage/Core/NkImage.h"

using namespace nkentseu;

static void ConfigureAppData(NkAppData &d) {
	d.appName = "Formats";
}


namespace fs = std::filesystem;

int main()
{
    NkImage photo;

    if (!photo.Load("photo.jpg"))
    {
        std::cerr << "Erreur : impossible de charger photo.jpg\n";
        return 1;
    }

    struct Format
    {
        std::string nom;
        std::string fichier;
    };

    const Format formats[] = {
        {"PNG", "photo.png"},
        {"JPEG", "photo_sortie.jpg"},
        {"BMP", "photo.bmp"},
        {"TGA", "photo.tga"},
        {"QOI", "photo.qoi"}
    };

    // Enregistrer la photographie dans les cinq formats.
    if (!photo.SavePNG("photo.png"))
    {
        std::cerr << "Erreur lors de l'ecriture PNG\n";
    }

    if (!photo.SaveJPEG("photo_sortie.jpg"))
    {
        std::cerr << "Erreur lors de l'ecriture JPEG\n";
    }

    if (!photo.SaveBMP("photo.bmp"))
    {
        std::cerr << "Erreur lors de l'ecriture BMP\n";
    }

    if (!photo.SaveTGA("photo.tga"))
    {
        std::cerr << "Erreur lors de l'ecriture TGA\n";
    }

    if (!photo.SaveQOI("photo.qoi"))
    {
        std::cerr << "Erreur lors de l'ecriture QOI\n";
    }

    std::ofstream sortie("formats.txt");

    if (!sortie)
    {
        std::cerr << "Erreur : impossible de creer formats.txt\n";
        return 1;
    }

    // Relire chaque fichier et mesurer le resultat obtenu.
    for (const Format& format : formats)
    {
        if (!fs::exists(format.fichier))
        {
            sortie << format.nom << " : 0 octets, illisible\n";
            continue;
        }

        const auto taille = fs::file_size(format.fichier);

        NkImage imageRelue;

        if (!imageRelue.Load(format.fichier.c_str()))
        {
            sortie << format.nom << " : "
                   << taille << " octets, illisible\n";

            continue;
        }

        const int largeur = imageRelue.Width();
        const int hauteur = imageRelue.Height();

        std::cout << format.nom << " : "
                  << taille << " octets, "
                  << largeur << " x " << hauteur << '\n';

        sortie << format.nom << " : "
               << taille << " octets, "
               << largeur << " x " << hauteur << '\n';

        if (largeur != photo.Width() || hauteur != photo.Height())
        {
            std::cerr << "Attention : dimensions differentes pour "
                      << format.nom << '\n';
        }
    }

    return 0;
}
