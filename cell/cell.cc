#include "cell.h"

// getters
Floor* Cell::get_root_floor() {
  return this->root_floor;
}

int Cell::get_index() {
  return this->index;
}

bool Cell::get_player_walkable() {
  return this->player_walkable;
}

bool Cell::get_entity_spawnable() {
  return this->entity_spawnable;
}

// setters
void Cell::set_root_floor(Floor* root_floor) {
  this->root_floor = root_floor;
}

void Cell::set_index(int index) {
  this->index = index;
}

void Cell::set_notation(char notation) {
  this->notation = notation;
}
