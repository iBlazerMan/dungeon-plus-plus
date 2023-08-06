/* @author: William Wang
   @purpose: PC is an abstract class and the parent class of every playable character subclass including
            shade, drow, vampire, troll, goblin, and is also the parent class of the decorator PotionEffect
*/

#ifndef PC_H
#define PC_H

#include <iostream>
#include <string>

using namespace std;

class PC {
protected:
    // stats of playable character
    int atk, def, hp, hp_max, gold, tile_ID;
    char sym;
    string faction;
    // can miss: 50% set to true once attacked by halfling, 
    // guarantee to miss the next attack
    // merchant_status: set to false once a merchant is attacked, trigger merchant's aggression
    bool can_miss, merchant_status;

public:
    // ctor and dtor
    PC(int atk, int def, int hp, int hp_max, string faction, int tile_ID);
    virtual ~PC();
    // getters and setters
    virtual int get_atk() const;
    virtual int get_def() const;
    virtual int get_hp() const;
    virtual bool get_merch_stat() const;
    virtual bool get_miss() const;
    virtual string get_faction() const;
    virtual int get_tile_ID() const;
    virtual int get_gold() const;
    virtual char get_sym() const;
    virtual void mod_gold(int val);
    virtual void set_tile_ID(int val);
    virtual void set_miss(bool val);
    virtual void set_merch_stat(bool val);
    virtual bool mod_hp(int val);
};

// shade, concrete derived class of PC
class shade: public PC {
public:
    shade(int tile_ID);
    ~shade();
};

// drow, concrete derived class of PC
class drow: public PC {
public:
    drow(int tile_ID);
    ~drow();
};

// vampire, concrete derived class of PC
class vampire: public PC {
public:
    vampire(int tile_ID);
    ~vampire();
};

// troll, concrete derived class of PC
class troll: public PC {
public:
    troll(int tile_ID);
    ~troll();
};

// goblin, concrete derived class of PC
class goblin: public PC {
public:
    goblin(int tile_ID);
    ~goblin();
};

#endif
