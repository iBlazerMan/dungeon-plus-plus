/* @author: William Wang
   @purpose: NPC is an abstract subclass of entity and the parent class of all non-playable character/enemies 
            including human, dwarf, elf, orcs, elf, merchant, halfling, and dragon
*/

#ifndef NPC_H
#define NPC_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "pc.h"
#include "entity.h"

using namespace std;

class NPC: public Entity{
    protected:
    // stats of NPC
    int atk, def, hp, tile_ID;
    char sym;
    string faction;

    public:
    // ctor and dtor
    NPC(int atk, int def, int hp, char sym, string faction, int tile_ID);
    ~NPC();
    // getters
    int get_atk() const;
    int get_def() const;
    int get_hp() const;
    // override entity's get_sym method to return NPC's symbol
    char get_sym() const override;
    string get_faction() const;
    virtual bool mod_hp(int dmg);
};

// human, concrete derived class of NPC
class human: public NPC {
    public:
    human(int tile_ID);
    ~human();
};

// dwarf, concrete derived class of NPC
class dwarf: public NPC {
    public:
    dwarf(int tile_ID);
    ~dwarf();
};

// elf, concrete derived class of NPC
class elf: public NPC {
    public:
    elf(int tile_ID);
    ~elf();
};

// orcs, concrete derived class of NPC
class orcs: public NPC {
    public:
    orcs(int tile_ID);
    ~orcs();
};

// merchant, concrete derived class of NPC
class merchant: public NPC {
    public:
    merchant(int tile_ID);
    ~merchant();
};

// halfling, concrete derived class of NPC
class halfling: public NPC {
    public:
    halfling(int tile_ID);
    ~halfling();
};

// dragon, concrete derived class of NPC
class dragon: public NPC {
    // tile_ID of the treDragon that the dragon guards, defaulted to -1
    int treasure_tile_ID;
    public: 
    dragon(int tile_ID, int treasure_tile_ID = -1);
    ~dragon();
    // getter and setter for treasure_tile_ID
    int get_treasure_tild_ID() const;
    void set_treasure_tild_ID(int val);
};

#endif
