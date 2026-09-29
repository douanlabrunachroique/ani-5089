#include <iostream>
#include <string>

using namespace std;

bool commencePar(const string& texte, const string& prefixe) {
    return texte.rfind(prefixe, 0) == 0;
}

bool finitPar(const string& texte, const string& suffixe) {
    if (texte.length() < suffixe.length()) {
        return false;
    }

    return texte.compare(
        texte.length() - suffixe.length(),
        suffixe.length(),
        suffixe
    ) == 0;
}

int main() {
    string architecture;
    cin >> architecture;

    int F;
    cin >> F;

    long long tailleTotale = 0;
    bool signe = false;
    bool abiOui = false;
    int inutile = 0;

    string prefixeABI = "lib/" + architecture + "/";

    for (int i = 0; i < F; ++i) {
        string chemin;
        long long taille;

        cin >> chemin >> taille;

        // Tous les fichiers comptent dans la taille totale.
        tailleTotale += taille;

        // Vérification de la signature.
        if (commencePar(chemin, "META-INF/") &&
            (finitPar(chemin, ".RSA") ||
             finitPar(chemin, ".DSA") ||
             finitPar(chemin, ".EC"))) {
            signe = true;
        }

        // Vérification de l'architecture.
        if (commencePar(chemin, prefixeABI)) {
            abiOui = true;
        }

        // Fichier sous lib/ mais appartenant à une autre architecture.
        if (commencePar(chemin, "lib/") &&
            !commencePar(chemin, prefixeABI)) {
            ++inutile;
        }
    }

    cout << tailleTotale << '\n';

    if (signe) {
        cout << "SIGNE\n";
    } else {
        cout << "NON SIGNE\n";
    }

    if (abiOui) {
        cout << "ABI OUI\n";
    } else {
        cout << "ABI NON\n";
    }

    cout << "INUTILE " << inutile << '\n';

    return 0;
}
