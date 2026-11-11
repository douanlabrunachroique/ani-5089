
#include <iostream>
#include <string>
#include <sstream>

int main() {
    int n;
    std::cin >> n;

    int survivants = 0;

    std::string ligne;
    std::getline(std::cin, ligne);

    for (int i = 0; i < n; ++i) {
        std::getline(std::cin, ligne);

        std::istringstream flux(ligne);

        std::string nom;
        flux >> nom;

        bool detruit = false;
        bool recree = false;
        bool reenregistre = false;

        int positionDetruit = -1;
        int positionRecree = -1;
        int position = 0;

        std::string commande;

        while (flux >> commande) {
            if (commande == "DETRUIT") {
                detruit = true;
                if (positionDetruit == -1) {
                    positionDetruit = position;
                }
            }
            else if (commande == "RECREE") {
                recree = true;
                if (positionRecree == -1) {
                    positionRecree = position;
                }
            }
            else if (commande == "REENREGISTRE") {
                reenregistre = true;
            }

            ++position;
        }

        std::string verdict;

        if (detruit && recree && positionRecree < positionDetruit) {
            verdict = "MAUVAIS ORDRE";
        }
        else if (!detruit || !recree) {
            verdict = "CHAINE PERIMEE";
        }
        else if (!reenregistre) {
            verdict = "POIGNEES PERDUES";
        }
        else {
            verdict = "SURVIT";
            ++survivants;
        }

        std::cout << nom << " " << verdict << '\n';
    }

    std::cout << "SURVIVANTS " << survivants << '\n';

    return 0;
}
