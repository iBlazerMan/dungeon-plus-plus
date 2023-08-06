/* @author: Kevin Yang
   @purpose: This cell represents the interior of a chamber, including all the EntitySpawnable cells
             on the chamber but excluding any non-EntitySpawnable cell (ie. Wall)
             This class provides a shortcut for generating objects within a given chamber
*/

// include guard
#ifndef CHAMBERINTERIOR_H
#define CHAMBERINTERIOR_H

#include "entitySpawnable.h"
#include <vector>

class Floor;

class ChamberInterior {
    // Unique ID for chamber corresponding to their index in floor's vector
    int chamber_id;
    // Number of non-overlapping objects in the chamber, including Entities and player
    int num_entities;
    // If the chamber contains a player within
    bool has_player;
    // All EntitySpawnable cells within the chamber
    std::vector<EntitySpawnable*> interior_tiles;
    // The floor the chamber belongs to
    Floor* root_floor;

 public:
    // Constructor
    ChamberInterior(int chamber_id, Floor* root_floor, int num_entities = 0, bool has_player = false);

    // Pushes the es to the back of the interior_tiles
    void emplace_entityspawnable(EntitySpawnable* es);

    // getters
    int get_chamber_id();
    int get_num_entities();
    bool get_has_player();
    Floor* get_root_floor();
    // Returns the total number of EntitySpawnables in the vector equal to its size
    int get_num_cells();
    // Returns a pointer to the EntitySpawnable at interior_tiles[index]
    EntitySpawnable* get_tile_at(int index = 0);

    // setters
    void set_chamber_id(int chamber_id);
    void set_num_entities(int num_entities);
    void set_has_player(bool has_player);
    void set_root_floor(Floor* root_floor);
};

#endif
