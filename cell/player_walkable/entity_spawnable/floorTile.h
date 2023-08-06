/* @author: Kevin Yang
   @purpose: This is a concrete subclass, representing the floortiles on the floor map
*/

// Include guard
#ifndef FLOORTILE_H
#define FLOORTILE_H

#include "entitySpawnable.h"
#include "pc.h"
#include "entity.h"

class FloorTile : public EntitySpawnable {
 public:
    // Constructor: The client is responsible to attach the object to the correct chamber
    FloorTile (char notation, int index, ChamberInterior* root_chamber = nullptr);

    char render_cell() override;
};

#endif
