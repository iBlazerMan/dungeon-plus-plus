/* @author: Kevin Yang
   @purpose: This is a concrete subclass, represeting the passage on the floor's mape
*/

// Include guard
#ifndef PASSAGE_H
#define PASSAGE_H

#include "playerWalkableCell.h"

class Passage : public PlayerWalkableCell {
 public:
  // Constructor
  Passage(char notation, int index);
  
  char render_cell() override;   
};

#endif
