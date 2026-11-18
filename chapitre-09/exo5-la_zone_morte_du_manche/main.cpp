#include <iostream>
#include <cstdlib>

int main() {
    long long seuil = 0;
    long long maximum = 0;
    if (!(std::cin >> seuil >> maximum)) {
        return 0;
    }

    int n = 0;
    if (!(std::cin >> n)) {
        return 0;
    }

    int morts = 0;
    const long long denom = (1000LL - seuil) * (1000LL - seuil);

    for (int i = 0; i < n; ++i) {
        long long val = 0;
        std::cin >> val;

        long long abs_val = std::abs(val);

        if (abs_val < seuil) {
            ++morts;
            std::cout << 0 << '\n';
        } else {
            long long reste = abs_val - seuil;
            long long vitesse = 0;
            if (denom != 0) {
                vitesse = (maximum * reste * reste) / denom;
            }

            if (val < 0) {
                vitesse = -vitesse;
            }

            std::cout << vitesse << '\n';
        }
    }

    std::cout << "MORTS " << morts << '\n';

    return 0;
}
