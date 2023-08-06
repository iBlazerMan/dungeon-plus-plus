#include "doorway.h"

Doorway::Doorway(char notation, int index) : PlayerWalkableCell{} {
    this->entity_spawnable = false;
    this->notation = notation;
    this->index = index;
}

// If the Doorway has a player, then render the player notation, else render the doorway notation
char Doorway::render_cell() {
    if (this->player_on_cell) {
        return this->player_on_cell->get_sym();
    } else {
        return this->notation;
    }   
}
