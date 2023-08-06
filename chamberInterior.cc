#include "chamberInterior.h"

ChamberInterior::ChamberInterior(int chamber_id, Floor* root_floor, int num_entities, bool has_player)
    : chamber_id{chamber_id}, root_floor{root_floor}, num_entities{num_entities}, has_player{has_player} {
    this->interior_tiles = {};
}

void ChamberInterior::emplace_entityspawnable(EntitySpawnable* es) {
    this->interior_tiles.emplace_back(es);
}

// getters
int ChamberInterior::get_chamber_id() {
    return this->chamber_id;
}

int ChamberInterior::get_num_entities() {
    return this->num_entities;
}

bool ChamberInterior::get_has_player() {
    return this->has_player;
}

EntitySpawnable* ChamberInterior::get_tile_at(int index) {
    // Checks if the index is out of bounds
    if (index >= this->get_num_cells()) {
        return nullptr;
    }
    return this->interior_tiles[index];
}

Floor* ChamberInterior::get_root_floor() {
    return this->root_floor;
}

int ChamberInterior::get_num_cells() {
    return (this->interior_tiles).size();
}

// setters
void ChamberInterior::set_chamber_id(int chamber_id) {
    this->chamber_id = chamber_id;
}

void ChamberInterior::set_num_entities(int num_entities) {
    this->num_entities;
}

void ChamberInterior::set_has_player(bool has_player) {
    this->has_player = has_player;
}

void ChamberInterior::set_root_floor(Floor* root_floor) {
    this->root_floor = root_floor;
}
