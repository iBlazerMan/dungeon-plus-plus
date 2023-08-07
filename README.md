# dungeon-plus-plus

```made in collaboration with Kevin Yang (github.com/NEVIEMYK3V1N/)```

Dungeon++ is a rogue-like video game implemented in C++ using many C++ classes
The objective is to reach the stairway of all 5 levels in order to win the game while collecting as much gold as possible for a high score.

## Controls:
### Selecting a faction/race:
s for Shade, d for Drow, v for Vampire, t for Troll, and g for Goblin
### Character Control:
direction (nw, no, ne, we, ea, sw, so, se): move the character to the adjacent tile in the direction given
u + direction: use the potion on the adjacent tile given (for example, using the potion on the northeast tile would be "u ne")
a + direction: attack the NPC on the tile given

## Playable Characters
Shade: No special ability
Drow: All potion effects are magnified by 1.5 times regardless of buff or debuff. Immune to elf's double attack
Vampire: No maximum HP cap, regains 5 HP for every successful attack except dwarf (loses 5 HP instead for being allergic)
Troll: Regains 5 HP at the start of every turn
Goblin: Gets a 5 Gold bonus upon killing an enemy
More to come!

## NPCs
NPC always attack the player if they are adjacent to one and move to a random direction 
Dragon(D): Does not move, guards a gold treasure that cannot be picked up before it is killed. Will attack 

## Potions
The potions' effects are not known before being picked up, and they can be any one of the following:
HP gain/loss, Attack buff/debuff, and Defense buff/debuff.
All attack and defense changes do not carry to another floor, but HP gained or lost do.

