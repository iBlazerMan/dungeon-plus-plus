#include "stairway.h"

Stairway::Stairway(int tile_ID) :
    Entity{false, false, false, tile_ID} {};
Stairway::~Stairway() {};

char Stairway::get_sym() const {
    return '\\';
}
