/* @author: William Wang
   @purpose: potion is the subclass of entity and the parent class of 3 types of potion, 
            potionHP, potionAtk, potionDef. 
*/

#ifndef POTION_H
#define POTION_H
#include "item.h"

class potion: public item {
protected:
    // stat of potion, negative effect potions
    int val;
    string pot_type;
public:
    // ctor and dtor, bool eff is used to determine whether the potion is a buff or debuff
    potion(int val, bool eff, string pot_type, int tile_ID);
    ~potion();
    // check if the player is drow and enhance potion effects accordingly
    void is_drow(const PC* player);
    char get_sym() const override;
};

class potionHP: public potion {
public:
    // HP buff potion is defaulted to +/-10 HP
    potionHP(bool eff, int tile_ID, int val = 10);
    ~potionHP();
    // calls player's mod_hp() when used, not a decorator
    PC* consume_item (PC* player) override;
};

class potionAtk: public potion {
public:
    potionAtk(bool eff, int tile_ID, int val = 5);
    ~potionAtk();
    // attaches a potAtk decorator to the player and returns the pointer of the decorator
    PC* consume_item (PC* player) override;
};

class potionDef: public potion {
public:
    potionDef(bool eff, int tile_ID, int val = 5);
    ~potionDef();
    // similar to potionAtk
    PC* consume_item (PC* player) override;
};

#endif
