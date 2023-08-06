/* @author: William Wang
   @purpose: stairway is a subclass of entity and it is used for the player to move to the next floor
*/

#ifndef STAIRWAY_H
#define STAIRWAY_H

#include "entity.h"

class Stairway : public Entity {
public:
    Stairway(int tile_ID);
    ~Stairway();
    char get_sym () const;
};

#endif
