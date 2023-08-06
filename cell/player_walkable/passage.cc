#include "passage.h"

Passage::Passage(char notation, int index) : PlayerWalkableCell{} {
    // Invariant of this class indicating the type of cells
    this->entity_spawnable = false;

    this->notation = notation;
    this->index = index; 
}

// If a player is occupying the cell, the player render overwrites the object's
char Passage::render_cell() {
    if (this->player_on_cell) {
        return this->player_on_cell->get_sym();
    } else {
        return this->notation;
    }   
}
