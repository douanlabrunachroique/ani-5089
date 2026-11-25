
#include <iostream>

int main() {
    int images, n;
    std::cin >> images >> n;
    int idx = 0;
    int rendues = 0;
    for (int i = 1; i <= n; i++) {
        int draw;
        std::cin >> draw;
        if (draw == 1) {
            std::cout << i << " OUI 1 " << idx << "\n";
            idx = (idx + 1) % images;
            rendues++;
        } else {
            std::cout << i << " NON 0 -\n";
        }
    }
    std::cout << "RENDUES " << rendues << "\n";
    std::cout << "FINS " << n << "\n";
    return 0;
}
