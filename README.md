# dungeon-plus-plus

``` made in collaboration with Kevin Yang (github.com/NEVIEMYK3V1N/) ```

Dungeon++ is a rogue-like game implemented in C++ using many C++ and OOP design principles such as derived classes, class hierarchy, the "Big Five", and design patterns such as the decorator pattern. It has the ability to randomly generate a set of 

The objective is to reach the stairway of all 5 levels in order to win the game while not dying to the dangers along the way and collecting as much gold as possible for a high score. 

***Please ensure that either empty.txt or a valid map file is under the same directory when running the executable, the game would not run otherwise.***

When using a map file, provide the file name as a command line argument with the executable. Ex: if the file is called map.txt, place the file in the same directory and run ./Dungeon++.exe map.txt

## Controls:
### Selecting a faction/race:
s for Shade, d for Drow, v for Vampire, t for Troll, and g for Goblin
### Character Control:
* direction (nw, no, ne, we, ea, sw, so, se): move the character to the adjacent tile in the direction given
* u + direction: use the potion on the adjacent tile given (for example, using the potion on the northeast tile would be "u ne")
* a + direction: attack the NPC on the tile given
### Functionalities:
* f: enable/disable NPC movement
* q: quit the game

## Map Symbols:
* | and -: vertical and horizontal walls, no player or NPC is allowed to move on it
* +: doorway, only the player is allowed to enter
* #: passage, only the player is allowed to enter
* .: floortile, both player and NPC are allowed to move on it
* \: stairway, the player advances to the next floor once reached. If it is the stairway of the 5th floor, the player wins the game

## Playable Characters
- Shade: No special ability
- Drow: All potion effects are magnified by 1.5 times regardless of buff or debuff. Immune to elf's double attack
- Vampire: No maximum HP cap, regains 5 HP for every successful attack
- Troll: Regains 5 HP at the start of every turn
- Goblin: Gets a 5 Gold bonus upon killing an enemy <br> <br>
More to come!

## NPCs
NPC always attack the player if they are adjacent to one and move to a random adjacent tile otherwise. 
All NPCs have a 50% chance of missing their attack on the player. NPCs do not leave the chamber that they were spawned in.

* Dwarf (W): Causes Vampire to lose 5 HP instead of gaining when attacked
* Orcs (O): Deals 50% more damage against goblins
* Halfling: Has a 50% chance to cause the player to miss its next attack (player does not miss otherwise)
* Human(H): Drops a pile of gold when killed
* Merchant(M): remains neutral to the player but becomes hostile once attacked. Drops a pile of gold when killed.
* Dragon(D): Does not move, guards a gold treasure that cannot be picked up before it is killed. Will attack the player if it is adjacent to the treasure <br>
Dwarf, Orcs and Halfing give the player 1-2 gold randomly upon their demise. <br>
More to come!

## Potions
The potions' effects are not known before being picked up, and they can be any one of the following: <br>
HP gain/loss, Attack buff/debuff, and Defense buff/debuff <br>
All attack and defense changes do not carry to another floor, but HP gained or lost do <br>

