/* @author: Kevin Yang
   @Purpose: This is an abstract class, representing all cell types where an entity and player can be spawn and/or moved to
*/

// Include guard
#ifndef ENTITYSPAWNABLE_H
#define ENTITYSPAWNABLE_H

#include "playerWalkableCell.h"
#include <vector>

class ChamberInterior;
class Entity;

class EntitySpawnable : public PlayerWalkableCell {
 protected:
   // If another entity can occupy this object 
   //   Current Limit: 1 Entity per object
   bool open_to_entity;
   // The chamber it belongs to
   ChamberInterior* root_chamber;
   // The Entity currently occupying this object'
   //   if none is occupying: entity_on_cell is nullptr, open_to_entity is true
   //   otherwise: entity_on_cell is a valid pointer, open_to_entity is false
   Entity* entity_on_cell;

 public:
  // Constructor: Constructs a default template for the subclasses
  EntitySpawnable(ChamberInterior* root_chamber = nullptr, Entity* entity_on_cell = nullptr, bool open_to_entity = true);

  // getters
  bool get_open_to_entity();
  ChamberInterior* get_root_chamber();
  Entity* get_entity_on_cell();  

  // setters
  void set_open_to_entity(bool open_to_entity);
  void set_root_chamber(ChamberInterior* root_chamber);
  void set_entity_on_cell(Entity* entity);
};

#endif
