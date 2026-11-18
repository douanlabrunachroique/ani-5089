#include <iostream>

int main() {
    int n;
    if (!(std::cin >> n)) {
        return 0;
    }

    int prev_state = 0;
    int balles_front = 0;
    int balles_niveau = 0;
    int tenu_niveau = 0;
    int tenu_front = 0;

    for (int i = 0; i < n; ++i) {
        int state = 0;
        std::cin >> state;

        bool is_edge = (state == 1 && prev_state == 0);
        bool is_level = (state == 1);

        if (is_edge) {
            ++balles_front;
            ++tenu_front;
        }

        if (is_level) {
            ++balles_niveau;
            ++tenu_niveau;
        }

        prev_state = state;
    }

    std::cout << "BALLES FRONT " << balles_front << '\n';
    std::cout << "BALLES NIVEAU " << balles_niveau << '\n';
    std::cout << "TENU NIVEAU " << tenu_niveau << '\n';
    std::cout << "TENU FRONT " << tenu_front << '\n';

    return 0;
}
