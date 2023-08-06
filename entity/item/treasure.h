/* @author: William Wang
   @purpose: treasure is the subclass of item and the parent class of 2 kinds of treasures:
            regular ground treasure/hoard, and the dragon hoard. Every gold the spawns 
            from NPC death or natural generation is a treGround, and the dragon hoard guarded 
            by a dragon is treDragon
*/

#ifndef TREASURE_H
#define TREASURE_H

#include "item.h"

class Treasure: public item {
protected:
    // stats of treasure
    int val;
    string size;
    // check if treasure is treGround or treDragon for dynamic casting
    bool is_dragon;
public:
    // ctor and dtor
    Treasure(int val, int tile_ID, string size, bool is_dragon);
    ~Treasure();
    bool is_treDragon() const;
    // call player's mod_gold and use the treasure's value as argument
    PC* consume_item (PC* player) override;
    char get_sym() const override;
};

class treGround: public Treasure {
public:
    treGround(int val, int tile_ID, string size);
    ~treGround();
};

class treDragon: public Treasure {
    // pointer to a dragon entity, used by I/O in main to call dragon's methods
    // player cannot pick up treasure if guard ptr is not null
    dragon* guard;
public:
    treDragon(int val, int tile_ID);
    ~treDragon();
    // getter and setter for guard
    dragon* get_guard() const;
    void set_guard(dragon* guard);
};



#endif
