/* @author: Kevin Yang
   @purpose: This is a concrete subclass, representing the empty space cells in floor's map
*/

// Include guard
#ifndef VOIDCELL_H
#define VOIDCELL_H

#include "blockedCell.h"

class VoidCell : public BlockedCell {
 public:
    // Constructor
    VoidCell(char notation, int index);

    char render_cell() override;    
};

#endif
