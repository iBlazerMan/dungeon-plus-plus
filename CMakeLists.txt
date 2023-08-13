cmake_minimum_required (VERSION 3.26.3)
project (Dungeon++)
add_executable(Dungeon++
	cell/cell.cc
	cell/blocked_cell/blockedCell.cc
	cell/blocked_cell/voidCell.cc
	cell/blocked_cell/wall.cc
	cell/player_walkable/doorway.cc
	cell/player_walkable/passage.cc
	cell/player_walkable/playerWalkableCell.cc
	cell/player_walkable/entity_spawnable/entitySpawnable.cc
	cell/player_walkable/entity_spawnable/floorTile.cc
	entity/entity.cc
	entity/npc.cc
	entity/stairway.cc
	entity/item/item.cc
	entity/item/potion.cc
	entity/item/treasure.cc
	playable_character/pc.cc
	playable_character/potionEffect.cc
	chamberInterior.cc
	constants.cc
	floor.cc
	game.cc
	main.cc
)

target_include_directories(Dungeon++
	PRIVATE
	cell
	cell/blocked_cell
	cell/player_walkable
	cell/player_walkable/entity_spawnable
	entity
	entity/item
	playable_character
)

	