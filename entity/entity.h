/* @author: William Wang
   @purpose: NPC is an abstract superclass and it is the parent class of Stairway, item and treasure.
            It is also the ancestor class of item and treasure's subclasses, such as 
            every entitySpawnable class has an entity pointer, and the specific subclass can be dynamically casted
            accordingly
*/

#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <string>
#include "pc.h"
#include "potionEffect.h"

using namespace std;

class dragon;

class Entity {
protected:
    // shared stats of entities
    int tile_ID;
    // three booleans to determine the type of entity, used for dynamic casting
    bool gold, pot, NPC;
public:
    // ctor and dtor
    Entity(bool gold, bool pot, bool NPC, int tile_ID);
    virtual ~Entity();
    bool is_gold() const;
    bool is_pot() const;
    bool is_NPC() const;
    int get_tile_ID() const;
    void set_tile_ID(int val);
    // pure virtual get_sym() function used to print map
    virtual char get_sym() const = 0;
};

#endif
