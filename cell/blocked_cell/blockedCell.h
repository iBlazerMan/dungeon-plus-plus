/* @author: Kevin Yang
   @purpose: This is an abstract class of Cell, representing all the concrete types of cells that
             the player character can not walk on top
*/

// include guard
#ifndef BLOCKEDCELL_H
#define BLOCKEDCELL_H

#include "cell.h"

class BlockedCell : public Cell {
 public:
    BlockedCell();
};

#endif
