#include "blockedCell.h"

BlockedCell::BlockedCell() {
    // these values are constant / invariant of the class indicating the cell type
    this->player_walkable = false;
    this->entity_spawnable = false;
}
