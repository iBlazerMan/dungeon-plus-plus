#include "wall.h"

Wall::Wall(char notation, int index, bool has_chamber) 
    : BlockedCell{}, has_chamber{has_chamber} {
    this->notation = notation;
    this->index = index;
}

char Wall::render_cell() {
    return this->notation;
}

// getters
bool Wall::get_has_chamber() {
    return this->has_chamber;
}

// setters
void Wall::set_has_chamber(bool has_chamber) {
    this->has_chamber = has_chamber;
}
