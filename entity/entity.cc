#include "entity.h"

using namespace std;


Entity::Entity(bool gold, bool pot, bool NPC, int tile_ID) :
    gold{gold}, pot{pot}, NPC{NPC}, tile_ID{tile_ID} {};
Entity::~Entity() {};

bool Entity::is_gold() const {
    return gold;
}

bool Entity::is_pot() const {
    return pot;
}

bool Entity::is_NPC() const {
    return NPC;
}

int Entity::get_tile_ID() const {
    return tile_ID;
}

void Entity::set_tile_ID(int val) {
    tile_ID = val;
}
