#include "potion.h"

potion::potion(int val, bool eff, string pot_type, int tile_ID) :
    item{false, true, false, tile_ID}, val{val}, pot_type{pot_type} {
        if (!eff) {
            val = -100;
        }
    };
potion::~potion() {};

void potion::is_drow(const PC* player) {
    if (player->get_faction() == "drow") {
        val *= 1.5;
    }
}

char potion::get_sym() const {
    return 'P';
}

potionHP::potionHP(bool eff, int tile_ID, int val) :
    potion{val, eff, "HP", tile_ID} {};
potionHP::~potionHP() {};

PC* potionHP::consume_item(PC* player) {
    is_drow(player);
    player->mod_hp(val);
    return nullptr;
}

potionAtk::potionAtk(bool eff, int tile_ID, int val) :
    potion{val, eff, "atk", tile_ID} {};
potionAtk::~potionAtk() {};

PC* potionAtk::consume_item(PC* player) {
    is_drow(player);
    return new PotAtk(val, player);
}

potionDef::potionDef(bool eff, int tile_ID, int val) :
    potion{val, eff, "def", tile_ID} {};
potionDef::~potionDef() {};

PC* potionDef::consume_item(PC* player) {
    is_drow(player);
    return new PotDef(val, player);
}
