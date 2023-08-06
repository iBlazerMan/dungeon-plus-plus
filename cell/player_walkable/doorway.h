/* @author: Kevin Yang
   @purpose: This is a contrete subclass of PlayerWalkable, representing all the doorway cells in the map
*/

// Include guard
#ifndef DOORWAY_H
#define DOORWAY_H

#include "playerWalkableCell.h"

class Doorway : public PlayerWalkableCell {
 public:
  // Constructor: Index represents the unique ID of the Cell (Doorway)
  Doorway(char notation, int index);

  // Overrides from Cell
  char render_cell() override;  
};

#endif
