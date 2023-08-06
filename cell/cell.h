/* @author: Kevin Yang
   @purpose: This is an abstract class holding all the types of cells the map can have
             and provides common non-virtual methods and virtual methods for overriding 
*/

// include guard
#ifndef CELL_H
#define CELL_H

// forward declaration to use Floor*
class Floor;

class Cell {
  // The floor the cell is on
  Floor* root_floor;
 protected:
  // The unique ID of the cell represented by their index in floor's vector
  int index;
  // The symbol of the cell when outputted, varies for different types
  char notation;
  // These are invariants for different subclasses
  bool player_walkable;
  bool entity_spawnable;

 public:
  // Returns the char that should be outputted when rendering the cell
  virtual char render_cell() = 0;

  // getters
  Floor* get_root_floor();
  int get_index();
  bool get_player_walkable();
  bool get_entity_spawnable();

  // setters
  void set_root_floor(Floor* root_floor);
  void set_index(int index);
  void set_notation(char notation);
};

#endif
