#include "potionEffect.h"

PotionEffect::PotionEffect(int val, string type, PC* player) :
    // PC ctor must be called since PotionEffect is a subclass of PC, 
    // values of PC fields are never used in the decorator (only the PC* player's methods)
    PC{-1, -1, -1, -1, "", -1}, val{val}, type{type}, player{player} {};
PotionEffect::~PotionEffect() {
    // chain delete other decorators or the PC
    delete player;
}

int PotionEffect::get_atk() const {
    return player->get_atk();
}

int PotionEffect::get_def() const {
    return player->get_def();
}

int PotionEffect::get_hp() const {
    return player->get_hp();
}

bool PotionEffect::get_merch_stat() const {
    return player->get_merch_stat();
}

bool PotionEffect::get_miss() const {
    return player->get_miss();
}

string PotionEffect::get_faction() const {
    return player->get_faction();
}

int PotionEffect::get_tile_ID() const {
    return player->get_tile_ID();
}

int PotionEffect::get_gold() const {
    return player->get_gold();
}

char PotionEffect::get_sym() const {
    return player->get_sym();
}

void PotionEffect::mod_gold(int val) {
    player->mod_gold(val);
}

void PotionEffect::set_tile_ID(int val) {
    player->set_tile_ID(val);
}

void PotionEffect::set_miss(bool val) {
    player->set_miss(val);
}

void PotionEffect::set_merch_stat(bool val) {
    player->set_merch_stat(val);
}

bool PotionEffect::mod_hp(int val) {
    return player->mod_hp(val);
}


PotAtk::PotAtk(int val, PC* player) :
    PotionEffect {val, "atk", player} {};

int PotAtk::get_atk() const {
    int ret_val = val + player->get_atk();
    if (ret_val < 0) {
        ret_val = 0;
    }
    return ret_val;
}


PotDef::PotDef(int val, PC* player) :
    PotionEffect {val, "def", player} {};

int PotDef::get_def() const {
    int ret_val = val + player->get_def();
    if (ret_val < 0) {
        ret_val = 0;
    }
    return ret_val;
}
