#include "item.h"

item::item(bool gold, bool pot, bool NPC, int tile_ID) :
    Entity{gold, pot, NPC, tile_ID} {};
item::~item() {};
