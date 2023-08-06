#include "floorTile.h"

FloorTile::FloorTile (char notation, int index, ChamberInterior* root_chamber)
    : EntitySpawnable{root_chamber} {
        this->notation = notation;
        this->index = index;
    }

// If there is any player or enemy on the cell, the one with higher priority overwrites the others
//      Priority order: player (high) <- Entity <- object-notation (low)
char FloorTile::render_cell() {
    if (this->player_on_cell) {
        return this->player_on_cell->get_sym();
    }
    if (this->entity_on_cell) {
        return this->entity_on_cell->get_sym();
    } else {
        return this->notation;
    }   
}

