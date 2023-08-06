#include "game.h"

Game::Game(int num_floors) : num_floors{num_floors} {
}

// deletes subsequent floors
Game::~Game() {
    for(int i = 0; i < (int)(this->all_floors).size(); i++) {
        delete this->all_floors[i];
    }
}

void Game::emplace_floor(Floor* floor) {
    this->all_floors.emplace_back(floor);
}

// getters
int Game::get_num_floors() {
    return this->num_floors;
}

Floor* Game::get_floor_at(int index) {
    // error checking - out of bound index
    if (index >= (int)this->all_floors.size()) {
        return nullptr;
    }
    return (this->all_floors[index]);
}

// setters
void Game::set_num_floors(int num_floors) {
    this->num_floors = num_floors;
}
