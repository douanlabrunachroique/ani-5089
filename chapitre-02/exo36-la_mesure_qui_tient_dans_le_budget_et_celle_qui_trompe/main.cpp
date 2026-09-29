#include <iostream>
#include <string>

using namespace std;

int main() {
    long long budget;
    cin >> budget;

    int S;
    cin >> S;

    int trompe = 0;

    for (int i = 0; i < S; ++i) {
        string nom;
        long long debug;
        long long release;

        cin >> nom >> debug >> release;

        // Arrondi entier au plus proche.
        long long facteur = (debug + release / 2) / release;

        // La scène tient si Release respecte le budget.
        bool tient = release <= budget;

        if (tient) {
            cout << nom << " " << facteur << " TIENT\n";
        } else {
            cout << nom << " " << facteur << " DEPASSE\n";
        }

        // La scène trompe si Debug dépasse mais Release tient.
        if (debug > budget && release <= budget) {
            ++trompe;
        }
    }

    cout << "TROMPE " << trompe << '\n';

    return 0;
}
