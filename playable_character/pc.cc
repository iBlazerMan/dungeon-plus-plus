#include "pc.h"

using namespace std;

PC::PC(int atk, int def, int hp, int hp_max, string faction, int tile_ID) :
    // symbol for player is always '@'
    // can_miss defaulted to false (can't miss), merchant_status to true (merchant neutral to player)
    atk{atk}, def{def}, hp{hp}, hp_max{hp_max}, gold{0}, sym{'@'}, 
    faction{faction}, tile_ID{tile_ID}, can_miss{false}, merchant_status{true} {};
PC::~PC() {};

int PC::get_atk() const {
    return atk;
}

int PC::get_def() const {
    return def;
}

int PC::get_hp() const {
    return hp;
}

bool PC::get_merch_stat() const {
    return merchant_status;
}

bool PC::get_miss() const {
    return can_miss;
}

string PC::get_faction() const {
    return faction;
}

int PC::get_tile_ID() const {
    return tile_ID;
}

int PC::get_gold() const {
    return gold;
}

char PC::get_sym() const {
    return sym;
}

void PC::mod_gold(int val) {
    gold += val;
}

void PC::set_tile_ID(int val) {
    tile_ID = val;
}

void PC::set_miss(bool val) {
    can_miss = val;
}

void PC::set_merch_stat(bool val) {
    merchant_status = val;
}

bool PC::mod_hp(int val) {
    hp += val;
    // vampire ability
    if ((faction != "vampire") && (hp > hp_max)) {
        hp = hp_max;
    }
    if (hp > 0) {
        return true;
    } 
    hp = 0;
    return false;
}

shade::shade(int tile_ID) :
    PC {25, 25, 125, 125, "shade", tile_ID} {};
shade::~shade() {};


drow::drow(int tile_ID) :
    PC {25, 15, 150, 150, "drow", tile_ID} {};
drow::~drow() {};


vampire::vampire(int tile_ID) :
    PC {25, 25, 50, -1, "vampire", tile_ID} {};
vampire::~vampire() {};

troll::troll(int tile_ID) :
    PC {25, 15, 120, 120, "troll", tile_ID} {};
troll::~troll() {};


goblin::goblin(int tile_ID) :
    PC {15,20, 110, 110, "goblin", tile_ID} {};
goblin::~goblin() {};


