#include "treasure.h"

Treasure::Treasure(int val, int tile_ID, string size, bool is_dragon) :
    // is_gold set to true
    item{true, false, false, tile_ID}, val{val}, size{size}, is_dragon{is_dragon} {};
Treasure::~Treasure() {};

bool Treasure::is_treDragon() const {
    return is_dragon;
}

PC* Treasure::consume_item(PC* player) {
    player->mod_gold(val);
    return nullptr;
}

char Treasure::get_sym() const {
    return 'G';
}

treGround::treGround(int val, int tile_ID, string size) :
    Treasure{val, tile_ID, size, false} {};
treGround::~treGround() {};


treDragon::treDragon(int val, int tile_ID) :
    Treasure{val, tile_ID, "dragon_hoard", true} {};
treDragon::~treDragon() {};

dragon* treDragon::get_guard() const {
    return guard;
}

void treDragon::set_guard(dragon* guard) {
    this->guard = guard;
}
