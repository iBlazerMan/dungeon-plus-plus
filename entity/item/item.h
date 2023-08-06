/* @author: William Wang
   @purpose: item a subclass of entity and the parent class of potion and treasure
*/

#ifndef ITEM_H
#define ITEM_H
#include "entity.h"

class item : public Entity {
public:
    // ctor and dtor
    item(bool gold, bool pot, bool NPC, int tile_ID);
    virtual ~item();
    // pure virtual consume_item method to attach a ctor to player or 
    // simply call player's mod_hp() or mod_gold()
    virtual PC* consume_item(PC* player) = 0;
};
#endif
