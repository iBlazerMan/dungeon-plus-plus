/* @author: Kevin Yang
   @purpose: This is an abstract class, representing all types of cells where players can occupy (walk on)
             but is unavailable to Entity nor player spawning
*/

// Include guard
#ifndef PLAYERWALKABLE_H
#define PLAYERWALKABLE_H

#include "cell.h"
#include "pc.h"

class PlayerWalkableCell : public Cell {
 protected:
  // If another player can occupy this object 
  //   Current Limit: 1 player per object
  bool open_to_player;
  // The player currently occupying this object'
  //   if none is occupying: player_on_cell is nullptr, open_to_player is true
  //   otherwise: player_on_cell is a valid pointer, open_to_player is false
  PC* player_on_cell;

 public:
  // Constructor: constructs a default template for its subclasses
  PlayerWalkableCell(PC* player_on_cell = nullptr, bool open_to_player = true);

  // getter
  bool get_open_to_player();
  PC* get_player_on_cell();
  
  // setter
  void set_open_to_player(bool open_to_player);
  void set_player_on_cell(PC* player_on_cell);
};

#endif
