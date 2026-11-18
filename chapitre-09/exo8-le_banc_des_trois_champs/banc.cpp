#include <iostream>
#include "actions.h"

int main() {
    // Deux actions liées à deux touches distinctes, et une troisième liée à rien.
    Action action1;
    action1.bound = true; // Liée à la première touche

    Action action2;
    action2.bound = true; // Liée à la seconde touche

    Action action3;
    action3.bound = false; // Liée à rien (non-liée / unbound)

    // Exécution sur six images (1 à 6)
    // La première action est maintenue de la deuxième à la quatrième image.
    for (int frame = 1; frame <= 6; ++frame) {
        bool key1 = (frame >= 2 && frame <= 4);
        bool key2 = false; // Non pressée

        action1.sync(key1);
        action2.sync(key2);
        action3.sync(false);

        // Affichage en colonnes, une ligne par image :
        // Image | Action 1 (current, changed, active) | Action 2 | Action 3
        std::cout << frame << ' '
                  << action1.state.current << ' ' << action1.state.changed << ' ' << action1.state.active << ' '
                  << action2.state.current << ' ' << action2.state.changed << ' ' << action2.state.active << ' '
                  << action3.state.current << ' ' << action3.state.changed << ' ' << action3.state.active << '\n';
    }

    return 0;
}
