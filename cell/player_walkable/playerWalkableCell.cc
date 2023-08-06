#include "playerWalkableCell.h"

PlayerWalkableCell::PlayerWalkableCell(PC* player_on_cell, bool open_to_player) : 
    player_on_cell{player_on_cell}, open_to_player{open_to_player} {
    // Invariants of the class, indicating the type of cells
    this->player_walkable = true;   
}

// getter
bool PlayerWalkableCell::get_open_to_player() {
    return this->open_to_player;
}
PC* PlayerWalkableCell::get_player_on_cell() {
    return this->player_on_cell;
}

// setter
void PlayerWalkableCell::set_open_to_player(bool open_to_player) {
    this->open_to_player = open_to_player;
}

void PlayerWalkableCell::set_player_on_cell(PC* player_on_cell) {
    this->player_on_cell = player_on_cell;
}
