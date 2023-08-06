/* @author: Kevin Yang
   @purpose: This is a concrete subclass, representing the walls (horizontal and vertical) in floor's map
             The details of orientation of the walls is determined by the clients and the notation they
             construct the object with
*/

// Include guard
#ifndef WALL_H
#define WALL_H

#include "blockedCell.h"

class Wall : public BlockedCell {
    // Whether the wall has a chamber around associated to or not
    //      Provides shortcut to when the chambers are determined
    bool has_chamber;
    
 public:
    // Constructor: has_chamber field is initialized as if the Wall is isolated
    //      the client is responsible to update this field accordingly
    Wall(char notation, int index, bool has_chamber = false);

    char render_cell() override;

    // getters
    bool get_has_chamber();

    // setters
    void set_has_chamber(bool has_chamber);
};

#endif
