#include "voidCell.h"

VoidCell::VoidCell(char notation, int index) : BlockedCell{} {
    this->notation = notation;
    this->index = index;
} 

char VoidCell::render_cell() {
    return this->notation;
}

