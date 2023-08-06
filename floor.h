/* @author: Kevin Yang
   @purpose: This is a concrete class representing the entire map of one floor, including 
             the different cells, entities and player
             This class possess ownership over all its cells, entities and player
*/

// Include guard
#ifndef FLOOR_H
#define FLOOR_H

#include <memory>
#include <memory>
#include <vector>
#include <string>
#include "cell.h"
#include "chamberInterior.h"

class Entity;
class PC;

class Floor {
  // Number of different entities on the floor
  int num_stairway;
  int num_potions;
  int num_gold;
  int num_enemy;

  // Unique ID of the floor equal to the index in Game's vector
  int floor_level;

  // Dimensions of the floor
  int width;
  int height;

  // The single player on the floor
  PC* pc_on_floor;
  // Many objects on the floor
  std::vector<Entity*> entities_on_floor;
  std::vector<Cell*> map;
  std::vector<ChamberInterior*> chambers_on_floor;

 public:

  // Constructor: Defaultly constructs all the vectors to empty vectors
  //              Constructs a basic floor objects with no objects attached,
  //              the client needs to attach objects
  Floor(PC* pc, int height, int width, int floor_level, int num_stairway = 0, int num_potions = 0, int num_gold = 0, int num_enemy = 0);

  // Destructor: frees all memory of the floor's Entity, Cell, ChamberInterior and PC 
  ~Floor();

  // Pushes the parameters to the back of the corresponding vectors of floor
  void emplace_cell(Cell* cell);
  void emplace_entity(Entity* entity);
  void emplace_chamber(ChamberInterior* ci);

  // Returns number of cells in the floor equal to size of entities_on_floor
  int get_num_cells();
  // Returns number of chambers in the floor equal to size of chambers_on_floor
  int get_num_chambers();

  // getters
  int get_num_stairway();
  int get_num_potions();
  int get_num_gold();
  int get_num_enemy();
  int get_floor_level();
  int get_width();
  int get_height();
  PC* get_pc_on_floor();

  // Returns the object at given index in the corresponding vector
  Entity* get_entity_at_index(int index);
  Cell* get_cell_at_index(int index);
  ChamberInterior* get_chamber_at_index(int index);

  // setters
  void set_num_stairway(int num_stairway);
  void set_num_potions(int num_potions);
  void set_num_gold(int num_gold);
  void set_num_enemy(int num_enemy);
  void set_floor_level(int floor_level);
  void set_width(int width);
  void set_height(int height);
  void set_pc_on_floor(PC* pc_on_floor);
};

#endif
