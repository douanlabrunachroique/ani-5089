#pragma once

#ifndef ACTIONS_H
#define ACTIONS_H

// État d'une action avec les trois champs fondamentaux du chapitre
struct ActionState {
    bool current = false; ///< Vrai si l'action est activement actionnée à cette image
    bool changed = false; ///< Vrai si l'état courant a basculé depuis l'image précédente
    bool active = false;  ///< Vrai si une source matérielle est liée et disponible
};

// Modélisation d'une action pouvant être liée ou non à une touche/source matérielle
struct Action {
    bool bound = false;
    ActionState state;
    bool prev_current = false;

    void sync(bool key_pressed) {
        state.active = bound;
        bool raw = (state.active && key_pressed);
        state.current = raw;
        state.changed = (state.current != prev_current);
        prev_current = state.current;
    }
};

#endif // ACTIONS_H
