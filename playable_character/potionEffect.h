/* @author: William Wang
   @purpose: PotionEffect is the abstract decorator class and the parent class of every concrete decorator 
   subclass including PotAtk and PotDef
*/

#ifndef POTIONEFFECT_H
#define POTIONEFFECT_H
#include "pc.h"

class PotionEffect: public PC {
protected:
    // stats of potion
    int val;
    string type;
    // has a PC ptr
    PC* player; 

public:
    PotionEffect(int val, string type, PC* player);
    virtual ~PotionEffect();
    // decorator pattern
    virtual int get_atk() const override;
    virtual int get_def() const override;
    int get_hp() const override;
    bool get_merch_stat() const override;
    bool get_miss() const override;
    string get_faction() const override;
    int get_tile_ID() const override;
    int get_gold() const override;
    char get_sym() const override;
    void mod_gold(int val) override;
    void set_tile_ID(int val) override;
    void set_miss(bool val) override;
    void set_merch_stat(bool val) override;
    bool mod_hp(int val) override;
};

// PotAtk, concrete decorator component
class PotAtk: public PotionEffect {
public:
    PotAtk(int val, PC* player);
    // overrides get_atk and modifies the return value accordingly
    int get_atk() const override;
};

// PotDef, concrete decorator component
class PotDef: public PotionEffect {
public:
    PotDef(int val, PC* player);
    // overrides get_def and modifies the return value accordingly
    int get_def() const override;
};

#endif
