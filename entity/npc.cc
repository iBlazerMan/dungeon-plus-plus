#include "npc.h"

using namespace std;

NPC::NPC(int atk, int def, int hp, char sym, string faction, int tile_ID) :
    Entity {false, false, true, tile_ID}, 
    atk{atk}, def{def}, hp{hp}, sym{sym}, faction{faction}, tile_ID{tile_ID} {};
NPC::~NPC() {};

int NPC::get_atk() const {
    return atk;
}

int NPC::get_def() const {
    return def;
}

int NPC::get_hp() const {
    return hp;
}

char NPC::get_sym() const {
    return sym;
}

string NPC::get_faction() const {
    return faction;
}

bool NPC::mod_hp(int dmg) {
    hp += dmg;
    if (hp > 0) {
        return true;
    }
    return false;
}


human::human(int tile_ID) :
    NPC {20, 20, 140, 'H', "human", tile_ID} {};
human::~human() {};


dwarf::dwarf(int tile_ID) : 
    NPC {20, 30, 100, 'W', "dwarf", tile_ID} {};
dwarf::~dwarf() {};


elf::elf(int tile_ID) : 
    NPC {30, 10, 140, 'E', "elf", tile_ID} {};
elf::~elf() {};


orcs::orcs(int tile_ID) :
    NPC {30, 25, 180, 'O', "orcs", tile_ID} {};
orcs::~orcs() {};

merchant::merchant(int tile_ID) : 
    NPC {70, 5, 30, 'M', "merchant", tile_ID} {};
merchant::~merchant() {};

halfling::halfling(int tile_ID) :
    NPC {15, 20, 100, 'L', "halfling", tile_ID} {};
halfling::~halfling() {};


dragon::dragon(int tile_ID, int treasure_tile_ID) :
    NPC {20, 20, 150,'D', "dragon", tile_ID}, treasure_tile_ID{treasure_tile_ID} {};
dragon::~dragon() {};

int dragon::get_treasure_tild_ID() const {
    return treasure_tile_ID;
}

void dragon::set_treasure_tild_ID(int val) {
    treasure_tile_ID = val;
}
