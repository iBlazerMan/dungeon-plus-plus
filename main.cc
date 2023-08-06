#include "blockedCell.h"
#include "cell.h"
#include "chamberInterior.h"
#include "entity.h"
#include "entitySpawnable.h"
#include "floor.h"
#include "floorTile.h"
#include "game.h"
#include "item.h"
#include "npc.h"
#include "pc.h"
#include "playerWalkableCell.h"
#include "doorway.h"
#include "passage.h"
#include "potion.h"
#include "potionEffect.h"
#include "stairway.h"
#include "treasure.h"
#include "voidCell.h"
#include "wall.h"

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include <cmath>
#include <sstream>

// constants for all maps
const char WALL_HORIZONTAL = '-';
const char WALL_VERTICAL = '|';
const char VOID_CELL = ' ';
const char FLOOR_TILE = '.';
const char DOORWAY = '+';
const char PASSAGE = '#';

const char STAIRWAY = '\\';

const char PLAYER = '@';

// constants for rendering map
const char ENEMY_HUMAN_RENDER = 'H';
const char ENEMY_DWARF_RENDER = 'W';
const char ENEMY_ELF_RENDER = 'E';
const char ENEMY_ORC_RENDER = 'O';
const char ENEMY_MERCHANT_RENDER = 'M';
const char ENEMY_DRAGON_RENDER = 'D';
const char ENEMY_HALFLING_RENDER = 'L';

const char POTION_RENDER = 'P';
const char GOLD_RENDER = 'G';


// colors for rendering
const std::string BLUE_TEXT = "\033[34m";
const std::string YELLOW_TEXT = "\033[33m";
const std::string GREEN_TEXT = "\033[32m";
const std::string RED_TEXT = "\033[31m";
const std::string RESET_TEXT = "\033[0m";

// constants for reading exising map
// The translation of numbers to items is as follows: 
// 0 - RH, 1 - BA, 2 - BD, 3 - PH, 4 - WA, 5 - WD, 6 - normal gold pile, 7 - small hoard, 8 - merchant hoard, 9 - dragon hoard.
const char RH = '0';
const char BA = '1';
const char BD = '2';
const char PH = '3';
const char WA = '4';
const char WD = '5';
const char NGP = '6';
const char SH = '7';
const char MH = '8';
const char DH = '9';

const int NGP_VAL = 2;
const int SH_VAL = 1;
const int MH_VAL = 4;
const int DH_VAL = 6;

const int NUM_PLAYERS = 1;
const int NUM_FLOORS = 5;
const int DEFAULT_WIDTH = 79;
const int DEFAULT_HEIGHT = 25;
const int DEFAULT_CHAMBER_ON_FLOOR = 5;

const int ARG_NUM_FILENAME = 1;

const int RATE_OF_POTIONS = 6;
const int RH_RATE = 0;
const int BA_RATE = RH_RATE + 1;
const int BD_RATE = BA_RATE + 1;
const int PH_RATE = BD_RATE + 1;
const int WA_RATE = PH_RATE + 1;
const int WD_RATE = WA_RATE + 1;

const int RATE_OF_GOLD = 8;
const int NGP_RATE = 4;
const int DH_RATE = NGP_RATE + 1;
const int SH_RATE = DH_RATE + 2;

const int RATE_OF_ENEMY = 18;
const int HUMAN_RATE = 3;
const int DWARF_RATE = HUMAN_RATE + 3;
const int HALFLING_RATE = DWARF_RATE + 5;
const int ELF_RATE = HALFLING_RATE + 2;
const int ORC_RATE = ELF_RATE + 2;
const int MER_RATE = ORC_RATE + 2;

const int DEFAULT_NUM_STAIRWAY = 1;
const int DEFAULT_NUM_POTIONS = 10;
const int DEFAULT_NUM_PLAYER = 1;
const int DEFAULT_NUM_GOLD = 10;
const int DEFAULT_NUM_ENEMY = 20;

const int NUM_SURROUNDING_CELL = 8;

const int BUFF_ATK_POTION_VAL = 5;
const int BUFF_DEF_POTION_VAL = 5;
const int BUFF_H_POTION_VAL = 10;
const int NERF_ATK_POTION_VAL = -5;
const int NERF_DEF_POTION_VAL = -5;
const int NERF_H_POTION_VAL = -10;

const std::string SH_MSG = "small";
const std::string NGP_MSG = "normal";
const std::string MC_MSG = "merchant";
const std::string DH_MSG = "dragon";

// read_entity_map_file(game, file_name, map_width, map_height, num_floors, race):
//      takes in the name of the file consisting of (num_floors) number of maps, each with width (map_width) and height (map_height)
//      and initializes the game with that many floors, each corresponding to one floor layout specified in the txt file, with
//      each player on each floor initialized to the race (race)
//      The function returns true if ANY objects (entity / player) exist in ANY of the floor layout, and false otherwise
// Requires: file_name is a valid file
//           game is a valid game
//           map_width, map_height corresponds to the width and height of each individual floor layout in the text file
bool read_entity_map_file(Game* game, std::string file_name, int map_width, int map_height, int num_floors, std::string race) {
    std::ifstream f(file_name);
    std::string s;
    // index / ID of the current cell on each floor being processed
    int index = 0;
    // return value
    bool contain_entity = false;
    bool contain_player = false;

    for (int numf = 0; numf < num_floors; numf++) {
        // reset counters for floor
        index = 0;
        // used for binding dragons with dragon hoards
        std::vector<dragon*> unbounded_drags;

        // intialize the empty map with no cells and player
        Floor* floor = new Floor(nullptr, map_height, map_width, numf);

        // loop through height / lines of the floor layout
        for (int h = 0; h < map_height; h++) {
            std::getline(f, s);

            // loop through each individual cell on each line
            for (int w = 0; w < map_width; w++) {
                // cell character
                char c = s[w];
                // if the cell is a wall of any kinds
                if ((c == WALL_HORIZONTAL) || (c == WALL_VERTICAL)) {
                    // initialize wall
                    Wall *wall = new Wall(c, index);
                    // adds wall to floor
                    floor->emplace_cell(wall);
                    // update counter
                    index++;
                } 
                // if the cell is a void / empty space cell
                else if (c == VOID_CELL) {
                    // initialize cell
                    VoidCell *vc = new VoidCell(c, index);
                    // adds cell
                    floor->emplace_cell(vc);
                    // increase counter
                    index++;
                }
                // if the cell is a floortile cell
                else if (c == FLOOR_TILE) {
                    // initialize cell
                    FloorTile *ft = new FloorTile(c, index);
                    // add cell to floor
                    floor->emplace_cell(ft);
                    // update counter
                    index++;
                }
                // if the cell is a doorway cell
                else if (c == DOORWAY) {
                    // initialize cell
                    Doorway *dw = new Doorway(c, index);
                    // adds cell to floor
                    floor->emplace_cell(dw);
                    // update counter
                    index++;
                }
                // if the cell is a passage
                else if (c == PASSAGE) {
                    // initialize cell
                    Passage *psg = new Passage(c, index);
                    // adds cell to floor
                    floor->emplace_cell(psg);
                    // update counter
                    index++;
                }
            // handleing entities / non-default cells
                // handleing potions
                else if (c == RH) {
                    // initialize potion
                    potionHP *pot = new potionHP(true, index, BUFF_H_POTION_VAL);
                    // initialize cell
                    FloorTile *ft = new FloorTile(FLOOR_TILE, index);
                    // adds cell to floor
                    floor->emplace_cell(ft);
                    // binds pot to cell
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_entity_on_cell(pot);
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_open_to_entity(false);
                    // adds pot to floor
                    floor->emplace_entity(pot);
                    floor->set_num_potions(floor->get_num_potions() + 1);
                    // update counters
                    index++;
                    contain_entity = true;
                    pot = nullptr;
                    ft = nullptr;
                }

                else if (c == BA) {
                    // initialize potion
                    potionAtk *pot = new potionAtk(true, index, BUFF_ATK_POTION_VAL);
                    // initialize cell
                    FloorTile *ft = new FloorTile(FLOOR_TILE, index);
                    // adds cell to floor
                    floor->emplace_cell(ft);
                    // binds pot to cell
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_entity_on_cell(pot);
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_open_to_entity(false);
                    // adds pot to floor
                    floor->emplace_entity(pot);
                    floor->set_num_potions(floor->get_num_potions() + 1);
                    // update counters
                    index++;
                    contain_entity = true;
                    pot = nullptr;
                    ft = nullptr;
                }

                else if (c == BD) {
                    // initialize potion
                    potionDef *pot = new potionDef(true, index, BUFF_DEF_POTION_VAL);
                    // initialize cell
                    FloorTile *ft = new FloorTile(FLOOR_TILE, index);
                    // adds cell to floor
                    floor->emplace_cell(ft);
                    // binds pot to cell
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_entity_on_cell(pot);
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_open_to_entity(false);
                    // adds pot to floor
                    floor->emplace_entity(pot);
                    floor->set_num_potions(floor->get_num_potions() + 1);
                    // update counters
                    index++;
                    contain_entity = true;
                    pot = nullptr;
                    ft = nullptr;
                }

                else if (c == PH) {
                    // initialize potion
                    potionHP *pot = new potionHP(false, index, NERF_H_POTION_VAL);
                    // initialize cell
                    FloorTile *ft = new FloorTile(FLOOR_TILE, index);
                    // adds cell to floor
                    floor->emplace_cell(ft);
                    // binds pot to cell
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_entity_on_cell(pot);
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_open_to_entity(false);
                    // adds pot to floor
                    floor->emplace_entity(pot);
                    floor->set_num_potions(floor->get_num_potions() + 1);
                    // update counters
                    index++;
                    contain_entity = true;
                    pot = nullptr;
                    ft = nullptr;
                }

                else if (c == WA) {
                    // initialize potion
                    potionAtk *pot = new potionAtk(false, index, NERF_ATK_POTION_VAL);
                    // initialize cell
                    FloorTile *ft = new FloorTile(FLOOR_TILE, index);
                    // adds cell to floor
                    floor->emplace_cell(ft);
                    // binds pot to cell
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_entity_on_cell(pot);
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_open_to_entity(false);
                    // adds pot to floor
                    floor->emplace_entity(pot);
                    floor->set_num_potions(floor->get_num_potions() + 1);
                    // update counters
                    index++;
                    contain_entity = true;
                    pot = nullptr;
                    ft = nullptr;
                }

                else if (c == WD) {
                    // initialize potion
                    potionDef *pot = new potionDef(false, index, NERF_DEF_POTION_VAL);
                    // initialize cell
                    FloorTile *ft = new FloorTile(FLOOR_TILE, index);
                    // adds cell to floor
                    floor->emplace_cell(ft);
                    // binds pot to cell
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_entity_on_cell(pot);
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_open_to_entity(false);
                    // adds pot to floor
                    floor->emplace_entity(pot);
                    floor->set_num_potions(floor->get_num_potions() + 1);
                    // update counters
                    index++;
                    contain_entity = true;
                    pot = nullptr;
                    ft = nullptr;
                    
                }

                // handeling golds
                else if (c == NGP) {
                    // initialize gold
                    treGround *normal_pile_gold = new treGround(NGP_VAL, index, NGP_MSG);
                    // initialize cell
                    FloorTile *ft = new FloorTile(FLOOR_TILE, index);
                    // add cell to floor
                    floor->emplace_cell(ft);
                    // bind gold to cell
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_entity_on_cell(normal_pile_gold);
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_open_to_entity(false);
                    // add gold to floor
                    floor->emplace_entity(normal_pile_gold);
                    floor->set_num_gold(floor->get_num_gold() + 1);
                    // update counters
                    index++;
                    contain_entity = true;
                    normal_pile_gold = nullptr;
                    ft = nullptr;
                }

                else if (c == SH) {
                    // initialize gold
                    treGround *small_hoard = new treGround(SH_VAL, index, SH_MSG);
                    // initialize cell
                    FloorTile *ft = new FloorTile(FLOOR_TILE, index);
                    // add cell to floor
                    floor->emplace_cell(ft);
                    // bind gold to cell
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_entity_on_cell(small_hoard);
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_open_to_entity(false);
                    // add gold to floor
                    floor->emplace_entity(small_hoard);
                    floor->set_num_gold(floor->get_num_gold() + 1);
                    // update counters
                    index++;
                    contain_entity = true;
                    small_hoard = nullptr;
                    ft = nullptr;
                }
                
                else if (c == MH) {
                    // initialize gold
                    treGround *merchant_hoard = new treGround(MH_VAL, index, MC_MSG);
                    // initialize cell
                    FloorTile *ft = new FloorTile(FLOOR_TILE, index);
                    // add cell to floor
                    floor->emplace_cell(ft);
                    // bind gold to cell
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_entity_on_cell(merchant_hoard);
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_open_to_entity(false);
                    // add gold to floor
                    floor->emplace_entity(merchant_hoard);
                    floor->set_num_gold(floor->get_num_gold() + 1);
                    // update counters
                    index++;
                    contain_entity = true;
                    merchant_hoard = nullptr;
                    ft = nullptr;
                }
                
                else if (c == DH) {
                    // initialize gold
                    treDragon * td = new treDragon(DH_VAL, index);
                    // initialize cell
                    FloorTile *ft = new FloorTile(FLOOR_TILE, index);
                    // reset guard / dragon for dragon hoard
                    td->set_guard(nullptr);
                    // adds cell to floor
                    floor->emplace_cell(ft);
                    // binds gold to cell
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_entity_on_cell(td);
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_open_to_entity(false);
                    // add gold to floor
                    floor->emplace_entity(td);      
                    floor->set_num_gold(floor->get_num_gold() + 1);
                    // update counters
                    index++;
                    contain_entity = true;
                    td = nullptr;
                    ft = nullptr;
                }

                // handeling players
                else if (c == PLAYER) {
                    // determine faction/race of the player and initialize pc
                    PC* pc;
                    if (race == "s") {
                        pc = new shade(index);
                    } else if (race == "d") {
                        pc = new drow(index);
                    } else if (race == "v") {
                        pc = new vampire(index);
                    } else if (race == "g") {
                        pc = new goblin(index);
                    } else if (race == "t") {
                        pc = new troll(index);
                    }
                    // initialize floor
                    FloorTile *ft = new FloorTile(FLOOR_TILE, index);
                    // bind pc to cell
                    ft->set_player_on_cell(pc);
                    // adds cell to floor
                    floor->emplace_cell(ft);
                    // binds pc to floor
                    floor->set_pc_on_floor(pc);
                    // update counters
                    contain_player = true;
                    index++;
                    pc = nullptr;
                    ft = nullptr;
                }

                // handeling stairway
                else if (c == STAIRWAY) {
                    // initialize stairway
                    Stairway *stw = new Stairway(index);
                    // initialize cell
                    FloorTile *ft = new FloorTile(FLOOR_TILE, index);
                    // adds cell to floor
                    floor->emplace_cell(ft);
                    // binds stairway to cell
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_entity_on_cell(stw);
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_open_to_entity(false);
                    // add stairway to floor
                    floor->emplace_entity(stw);
                    floor->set_num_stairway(floor->get_num_stairway() + 1);
                    // update counters
                    index++;
                    contain_entity = true;
                    stw = nullptr;
                    ft = nullptr;
                }

                // handeling enemies
                else if (c == ENEMY_HUMAN_RENDER) {
                    // initialize enemy
                    human *hm = new human(index);
                    // initialize cell
                    FloorTile *ft = new FloorTile(FLOOR_TILE, index);
                    // add cell to floor
                    floor->emplace_cell(ft);
                    // bind enemy to cell
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_entity_on_cell(hm);
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_open_to_entity(false);
                    // adds enemy to floor
                    floor->emplace_entity(hm);
                    floor->set_num_enemy(floor->get_num_enemy() + 1);
                    // update counters
                    index++;
                    contain_entity = true;
                    hm = nullptr;
                    ft = nullptr;
                }

                else if (c == ENEMY_DWARF_RENDER) {
                    // initialize enemy
                    dwarf *dw = new dwarf(index);
                    // initialize cell
                    FloorTile *ft = new FloorTile(FLOOR_TILE, index);
                    // add cell to floor
                    floor->emplace_cell(ft);
                    // bind enemy to cell
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_entity_on_cell(dw);
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_open_to_entity(false);
                    // adds enemy to floor
                    floor->emplace_entity(dw);
                    floor->set_num_enemy(floor->get_num_enemy() + 1);
                    // update counters
                    index++;
                    contain_entity = true;
                    dw = nullptr;
                    ft = nullptr;
                }

                else if (c == ENEMY_ELF_RENDER) {
                    // initialize enemy
                    elf *ef = new elf(index);
                    // initialize cell
                    FloorTile *ft = new FloorTile(FLOOR_TILE, index);
                    // add cell to floor
                    floor->emplace_cell(ft);
                    // bind enemy to cell
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_entity_on_cell(ef);
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_open_to_entity(false);
                    // adds enemy to floor
                    floor->emplace_entity(ef);
                    floor->set_num_enemy(floor->get_num_enemy() + 1);
                    // update counters
                    index++;
                    contain_entity = true;
                    ef = nullptr;
                    ft = nullptr;
                }

                else if (c == ENEMY_ORC_RENDER) {
                    // initialize enemy
                    orcs *oc = new orcs(index);
                    // initialize cell
                    FloorTile *ft = new FloorTile(FLOOR_TILE, index);
                    // add cell to floor
                    floor->emplace_cell(ft);
                    // bind enemy to cell
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_entity_on_cell(oc);
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_open_to_entity(false);
                    // adds enemy to floor
                    floor->emplace_entity(oc);
                    floor->set_num_enemy(floor->get_num_enemy() + 1);
                    // update counters
                    index++;
                    contain_entity = true;
                    oc = nullptr;
                    ft = nullptr;
                }

                else if (c == ENEMY_MERCHANT_RENDER) {
                    // initialize enemy
                    merchant *mr = new merchant(index);
                    // initialize cell
                    FloorTile *ft = new FloorTile(FLOOR_TILE, index);
                    // add cell to floor
                    floor->emplace_cell(ft);
                    // bind enemy to cell
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_entity_on_cell(mr);
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_open_to_entity(false);
                    // adds enemy to floor
                    floor->emplace_entity(mr);
                    floor->set_num_enemy(floor->get_num_enemy() + 1);
                    // update counters
                    index++;
                    contain_entity = true;
                    mr = nullptr;
                    ft = nullptr;
                }

                else if (c == ENEMY_HALFLING_RENDER) {
                    // initialize enemy
                    halfling *hf = new halfling(index);
                    // initialize cell
                    FloorTile *ft = new FloorTile(FLOOR_TILE, index);
                    // add cell to floor
                    floor->emplace_cell(ft);
                    // bind enemy to cell
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_entity_on_cell(hf);
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_open_to_entity(false);
                    // adds enemy to floor
                    floor->emplace_entity(hf);
                    floor->set_num_enemy(floor->get_num_enemy() + 1);
                    // update counters
                    index++;
                    contain_entity = true;
                    hf = nullptr;
                    ft = nullptr;
                }
                
                else if (c == ENEMY_DRAGON_RENDER) {
                    // initialize enemy
                    dragon *dr = new dragon(index);
                    // initialize cell
                    FloorTile *ft = new FloorTile(FLOOR_TILE, index);
                    // adds cell to floor
                    floor->emplace_cell(ft);
                    // binds enemy to cell
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_entity_on_cell(dr);
                    dynamic_cast<FloorTile*>(floor->get_cell_at_index(index))->set_open_to_entity(false);
                    // adds enemy to floor
                    floor->emplace_entity(dr);
                    floor->set_num_enemy(floor->get_num_enemy() + 1);
                    // append drag for hoard process
                    unbounded_drags.emplace_back(dr);
                    // update counters
                    index++;
                    contain_entity = true;
                    dr = nullptr;
                    ft = nullptr;
                }
            }
        }

        // process read in dragons to bind with dragon hoard
        for (int i = 0; i < (int)unbounded_drags.size(); i++) {
            // get position of the current dragon
            int index = unbounded_drags[i]->get_tile_ID();

            // map boundary checks
            bool top = true;
            bool left = true;
            bool right = true;
            bool bottom = true;
            // the top of map
            if (index < floor->get_width()) {
                top = false;
            }
            // the left of map
            if (index % floor->get_width() == 0) {
                left = false;
            }
            // the right of map
            if (index & (floor->get_width() == floor->get_width() - 1)) {
                right = false;
            }
            // the bottom of map
            if (index + floor->get_width() >= floor->get_num_cells()) {
                bottom = false;
            }
            
            // checking the surrounding cells
            for (int h = -1; h <= 1; h++) {
                for (int w = -1; w <= 1; w++) {
                    // check the border cells correctly
                    if (!top && h == -1) {
                        continue;
                    }
                    if (!left && w == -1) {
                        continue;
                    }
                    if (!right && w == 1) {
                        continue;
                    }
                    if (!bottom && h == 1) {
                        continue;
                    }
                    // ignore the cell the dragon is on
                    if (h == 0 && w == 0) {
                        continue;
                    }

                    // hoard placeholder
                    treDragon* target_dh = nullptr;

                    // gets information about the current checking cell
                    int target_index = index + h * floor->get_width() + w;
                    Cell* target_cell = floor->get_cell_at_index(target_index);
                    EntitySpawnable* target_es = dynamic_cast<EntitySpawnable*>(target_cell);

                    // if the current checking cell is EntitySpawnable
                    if (target_es) {
                        // update hoard pointer
                        Entity* target_entity_on_cell = target_es->get_entity_on_cell();
                        target_dh = dynamic_cast<treDragon*>(target_entity_on_cell);
                    }
                    // if there is a hoard at the current checking cell
                    if (target_dh && (target_dh->get_guard() == nullptr)) {\
                        // bind board to dragon
                        target_dh->set_guard(unbounded_drags[i]);
                        // bind dragon with hoard id
                        unbounded_drags[i]->set_treasure_tild_ID(target_index);
                        // continue to other dragons
                        break;
                    }
                }
            }
        }
        
        // binds updated floor to game
        game->emplace_floor(floor);

        // reset counters
        floor = nullptr;
    }
    return (contain_player || contain_entity);
}

// is_char_enemy (char c): returns true if c is any of the enemy symbols, false otherwise
bool is_char_enemy (char c) {
    return (c == ENEMY_HUMAN_RENDER || 
            c == ENEMY_DWARF_RENDER ||
            c == ENEMY_ELF_RENDER ||
            c == ENEMY_ORC_RENDER || 
            c == ENEMY_MERCHANT_RENDER || 
            c == ENEMY_DRAGON_RENDER ||
            c == ENEMY_HALFLING_RENDER);
}

// void render_map(floor): outputs the map and player information in counsel with correct colering and formatting
// Requires: floor is a valid floor
void render_map(Floor* floor) {
    int width = floor->get_width();
    int height = floor->get_height();
    char c = 'X';
    // loop through each cell on the floor
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            Cell* cell = floor->get_cell_at_index(w + (h * width));
            c = cell->render_cell();
            if (c == PLAYER || c == STAIRWAY) {
                std::cout << BLUE_TEXT;
            } else if (c == GOLD_RENDER) {
                std::cout << YELLOW_TEXT;
            } else if (c == POTION_RENDER) {
                std::cout << GREEN_TEXT;
            } else if (is_char_enemy(c)) {
                std::cout << RED_TEXT;
            }
            std::cout << c;
            std::cout << RESET_TEXT;
        }
        std::cout << std::endl;
    }
    // print out player information
    PC* player = floor->get_pc_on_floor();
    if (player) {
        std::cout << GREEN_TEXT << "Race: " << player->get_faction() << endl;
        std::cout << YELLOW_TEXT << "Gold: " << player->get_gold() << RESET_TEXT << endl;
        std::cout << RED_TEXT << "HP: " << player->get_hp() << endl;
        std::cout << "Atk: " << player->get_atk() << RESET_TEXT << endl;
        std::cout << BLUE_TEXT << "Def: " << player->get_def() << RESET_TEXT << endl;
        std::cout << "Action: ";
    }
}

// calculate_dmg (atk, def): Calculate the damage using attacker's atk value and defender's def value 
int calculate_dmg(int atk, int def) {
    double numerator = 100;
    double def_src = 100 + def;
    int dmg = ceil((numerator / def_src) * atk);
    return dmg;
}

// process_dragon(drag, floor, action) determines the dragon's attack range and perform the 
// attack on the player if in range
void process_dragon(dragon* drag, Floor* floor, ostringstream& action) {
    int row = floor->get_width();
    PC* curr_player = floor->get_pc_on_floor();
    int player_tile_ID = curr_player->get_tile_ID();
    int dragon_ID = drag->get_tile_ID();
    int dragonHoard_ID = drag->get_treasure_tild_ID();
    vector<int> attack_range;
    // put every cell_ID that a dragon can reach in a vector
    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            attack_range.push_back(dragon_ID + i * row + j);
            attack_range.push_back(dragonHoard_ID + i * row + j);
        }
    }

    for (int i = 0; i < (int)attack_range.size(); ++i) {
        if (attack_range[i] == player_tile_ID) {
            srand(time(0));
                int hit = rand() % 2;
                if (hit == 0) {
                    action << drag->get_sym() << " attacks the player but missed!\n";
                } else {
                    int atk = drag->get_atk();
                int def = curr_player->get_def();
                int dmg = calculate_dmg(atk, def);
                curr_player->mod_hp(-dmg);
                action << drag->get_sym() << " attacks the player and deals " << dmg << " damage!\n";
            }   
        return;
        }
    }
}

// process_NPC_action(npc, floor, move_enable, action) determines the action available
//      to NPC and perform the action accordingly
void process_NPC_action(NPC* npc, Floor* floor, bool move_enable, ostringstream& action) {
    int row = floor->get_width();
    int ID = npc->get_tile_ID();
    int ID_max = floor->get_num_cells() - 1;
    vector<Cell*> adj_tiles;

    // find every adjacent cell that a player can be on
    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            int ID_curr = ID + i * row + j;
            if (ID_curr < 0 || ID_curr > ID_max || ID_curr == ID) {
                continue;
            }
            Cell* cell_curr = floor->get_cell_at_index(ID_curr);
            if (cell_curr->get_player_walkable()) {
                adj_tiles.push_back(cell_curr);
            }
        }
    }

    // find if any adjacent cell has a player present and attack if there are
    int atk_left = 1;
    for (int i = 0; i < (int)adj_tiles.size(); ++i) {
        PlayerWalkableCell* casted = dynamic_cast<PlayerWalkableCell*>(adj_tiles[i]);
        PC* player = casted->get_player_on_cell();
        if (player != nullptr) {
            // if merchant and not aggro
            if (npc->get_sym() == 'M' && player->get_merch_stat() == true) { break;} 
            int atk = npc->get_atk();
            int def = player->get_def();
            int dmg = calculate_dmg(atk, def);
            // elf ability
            if (npc->get_sym() == 'E' && player->get_faction() != "drow") {
                atk_left ++;
            }
            while (atk_left > 0) {
                // 50% chance of hitting the player
                srand(time(0));
                int hit = rand() % 2;
                if (hit == 0) {
                    action << npc->get_faction() << " attacks the player but missed!\n";
                } else {
                    // orcs ability
                    if (npc->get_sym() == 'O' && player->get_faction() == "goblin") {
                        dmg *= 1.5;
                    }
                    // halfling ability
                    if (npc->get_sym() == 'L') {
                        srand(time(0));
                        int affect = rand() % 2;
                        if (affect == 1) {
                            player->set_miss(true);
                        }
                    }
                    player->mod_hp(-dmg);
                    action << npc->get_faction() << " attacks the player and deals " << dmg << " damage!\n";
                }
                --atk_left;
            }
            return;
        }  
    }

    // move NPC if no player adjacent
    if (move_enable) {
        vector<EntitySpawnable*> available_tile;
        for (int i = 0; i < (int)adj_tiles.size(); ++i) {
            if (adj_tiles[i]->get_entity_spawnable()) {
                EntitySpawnable* casted = dynamic_cast<EntitySpawnable*>(adj_tiles[i]);
                // check if tile is empty
                if (casted && casted->get_open_to_entity() && (casted->get_player_on_cell() == nullptr)) {
                    available_tile.emplace_back(casted);
                }
            }
        }
        int options = available_tile.size();
        // if no move is available for NPC
        if (options == 0) {
            return;
        }
        srand(time(0));
        int chosen = rand() % options;
        int new_ID = available_tile[chosen]->get_index();
        EntitySpawnable* curr_tile = dynamic_cast<EntitySpawnable*>(floor->get_cell_at_index(npc->get_tile_ID()));
        available_tile[chosen]->set_entity_on_cell(npc);
        available_tile[chosen]->set_open_to_entity(false);
        curr_tile->set_entity_on_cell(nullptr);
        curr_tile->set_open_to_entity(true);
        npc->set_tile_ID(new_ID);
    }    
}


// is_top_left_unchecked_wall(floor, cell): returns true if the passed in cell is the top left corner of a chamber
//      that has not been processed, and false otherwise
//      The format of a top left wall of a uncheck chamber follows:
//          |-
//          -.
//          where . is a floortile that has not been processed
// Require: floor is a valid floor
//          cell is a valid cell on that floor
bool is_top_left_unchecked_wall(Floor* floor, Cell* cell) {
    // the cell must be a vertical wall to be a top left corner
    if (cell->render_cell() == WALL_VERTICAL) {
        int index = cell->get_index();
        // border checks, the top left corner can NOT be on the right most colume
        if (index % floor->get_width() == floor->get_width() - 1) {
            return false;
        }
        // nor the left most colume
        if (index % floor->get_width() == 0) {
            return false;
        }
        // nor the top of the map
        if (index < floor->get_width()) {
            return false;
        }
        // not the bottom of map
        if (index + floor->get_width() >= floor->get_num_cells()) {
            return false;
        }

        // get the cell index for the surrounding cells making up the identifier
        int right_cell_index = index + 1;
        int bottom_cell_index = index + floor->get_width();
        int br_cell_index = index + floor->get_width() + 1;

        int num_cells = floor->get_num_cells();

        // boundary checks
        if (right_cell_index < num_cells && bottom_cell_index < num_cells && br_cell_index < num_cells) {
            // checks if the cell types are correct, and that no cells has been processed already
            return (floor->get_cell_at_index(right_cell_index)->render_cell() == WALL_HORIZONTAL &&
                    floor->get_cell_at_index(bottom_cell_index)->render_cell() == WALL_VERTICAL &&
                    dynamic_cast<EntitySpawnable*> (floor->get_cell_at_index(br_cell_index)) &&
                    !dynamic_cast<Wall*> (floor->get_cell_at_index(right_cell_index))->get_has_chamber() &&
                    !dynamic_cast<Wall*> (floor->get_cell_at_index(bottom_cell_index))->get_has_chamber() &&
                    !dynamic_cast<EntitySpawnable*> (floor->get_cell_at_index(br_cell_index))->get_root_chamber());
        }
    }
    return false;
}

// find_all_cell_in_chamber( floor, top_left, chamber): finds all interior (EntitySpawnable) tiles from the floor around top_left
//      that are inside a given chamber marked by the given (top_left) cell, add binds them with the chamber
// Require: floor is a valid floor
//          top_left is the valid cell in chamber on the floor
//          chamber is a valid chamber on the floor
void find_all_cell_in_chamber(Floor* floor, Cell* top_left, ChamberInterior* chamber) {
    int ori_index = top_left->get_index();
    int f_width = floor->get_width();

    // boundary checks
    bool top = true;
    bool left = true;
    bool right = true;
    bool bottom = true;

    // the top of map
    if (ori_index < floor->get_width()) {
        top = false;
    }
    // the left of map
    if (ori_index % floor->get_width() == 0) {
        left = false;
    }
    // the right of map
    if (ori_index & (floor->get_width() == floor->get_width() - 1)) {
        right = false;
    }
    // the bottom of map
    if (ori_index + floor->get_width() >= floor->get_num_cells()) {
        bottom = false;
    }

     // checking the surrounding cells
    for (int h = -1; h <= 1; h++) {
        for (int w = -1; w <= 1; w++) {
            if (h == 0 && w == 0) {
                continue;
            }
            //skip diagonal
            if ((h == -1 && w == -1) ||
                (h == -1 && w == 1) ||
                (h == 1 && w == -1) ||
                (h == 1 && w == 1)) {
                continue;
            }
            if (!top && h == -1) {
                continue;
            }
            if (!left && w == -1) {
                continue;
            }
            if (!right && w == 1) {
                continue;
            }
            if (!bottom && h == 1) {
                continue;
            }

            // sets up current checking cell
            int curr_index = ori_index + h * f_width + w;
            Cell* curr_cell = floor->get_cell_at_index(curr_index);
            // if the current checking cell is EntitySpawnable
            EntitySpawnable* casted_curr_cell = dynamic_cast<EntitySpawnable*> (curr_cell);

            if (casted_curr_cell && !(casted_curr_cell->get_root_chamber())) {
                // binds cell to chamber
                casted_curr_cell->set_root_chamber(chamber);
                // adds cell to chamber
                chamber->emplace_entityspawnable(casted_curr_cell);
                // if the current checking cell has a player occupying
                if (dynamic_cast<PC*> (casted_curr_cell->get_player_on_cell())) {
                    // update the chamber to contain player
                    chamber->set_has_player(true);
                }

                // recursive call: find all cells around the current checking cell that belongs to the same chamber
                find_all_cell_in_chamber(floor, curr_cell, chamber);
            } else {
                Wall* casted_curr_wall = dynamic_cast<Wall*> (curr_cell);
                // if the current cell is a wall
                if (casted_curr_wall) {
                    // without a chamber associated
                    if (!casted_curr_wall->get_has_chamber()) {
                        // associate the wall with chamber
                        casted_curr_wall->set_has_chamber(true);
                    }
                }
            }
        }
    }
    return;
}

// determine_chambers_on_flr(floor, num_chambers = 5): find all (num_chambers) chambers on the current floor
//      and associate then with their corresponding interior cells
// Require: floor is a valid floor
//          num_chambers correspond to the correct number of chambers in the floor
void determine_chambers_on_flr(Floor* floor, int num_chambers = 5) {
    // initialize all chambers, and adds then to floor
    for (int i = 0; i < num_chambers; i++) {
        ChamberInterior *ci = new ChamberInterior(i, floor);
        floor->emplace_chamber(ci);
        ci = nullptr;
    }

    // loop through chambers
    int curr_chamber = 0;
    // loop through all cells in floor
    for(int h = 0; h < floor->get_height(); h++) {
        for(int w = 0; w < floor->get_width(); w++) {
            // set up current checking cell
            Cell* curr_cell = floor->get_cell_at_index(h * floor->get_width() + w);
            // if the current checking cell marks the top left of a chamber that has not been processed
            if (is_top_left_unchecked_wall(floor, curr_cell)) {
                // set up the top left wall
                Wall* tl_wall = dynamic_cast<Wall*>(curr_cell);
                // if the corner has been processed
                if (tl_wall->get_has_chamber()) {
                    continue;
                }
                // associate wall with chamber
                tl_wall->set_has_chamber(true);
                // get the top left EntitySpawnable cell of the chamber
                EntitySpawnable* tl_spawnable = dynamic_cast<EntitySpawnable*> (floor->get_cell_at_index((h + 1) * floor->get_width() + w + 1));
                // bind cell with chamber
                tl_spawnable->set_root_chamber(floor->get_chamber_at_index(curr_chamber));
                // adds cell to chamber
                floor->get_chamber_at_index(curr_chamber)->emplace_entityspawnable(tl_spawnable);

                // adds all cells corresponding to the chamber
                find_all_cell_in_chamber(floor, tl_spawnable, floor->get_chamber_at_index(curr_chamber));
                curr_chamber++;
            }
        }
    }
}

// get_cell_from_chamber(chamber): returns of the cell index in floor that is randomly selected from a EntitySpawnable cell in chamber
//      that is not being occupied by any Entity
// Require: chamber is a valid chamber 
int get_cell_from_chamber(ChamberInterior* chamber) {
    int index = rand() % chamber->get_num_cells();
    // if the cell is not occupied
    if (((chamber->get_tile_at(index))->get_entity_on_cell()) == nullptr) {
        return (chamber->get_tile_at(index))->get_index();
    }
    else {
        return get_cell_from_chamber(chamber);
    }
}

// attach_entity_to_cell(curr_floor_playing, cell_index, entity): attaches entity to the cell at cell_index in floor
//      and updating the corresponding parameters 
// Require: curr_floor_playing is a valid floor
//          cell_index is a valid cell index corresponding to a valid cell in floor
//          entity is a valid entity
void attach_entity_to_cell(Floor* curr_floor_playing, int cell_index, Entity* entity) {
    dynamic_cast<EntitySpawnable*>(curr_floor_playing->get_cell_at_index(cell_index))->set_open_to_entity(false);
    dynamic_cast<EntitySpawnable*>(curr_floor_playing->get_cell_at_index(cell_index))->set_entity_on_cell(entity);
    entity->set_tile_ID(cell_index);
}

// rand_a_surrounding_cell(floor, index): returns a cell pointer to a randomly selected cell from the surrounding 8 cells 
//      of the cell at the given index, available for entity generation
// Require: floor is a valid floor
//          index corresponse to a valid cell index in the floor
Cell* rand_a_surrounding_cell(Floor* floor, int index) {
    // boundary checks
    bool top = true;
    bool left = true;
    bool right = true;
    bool bottom = true;

    // the top of map
    if (index < floor->get_width()) {
        top = false;
    }
    // the left of map
    if (index % floor->get_width() == 0) {
        left = false;
    }
    // the right of map
    if (index & (floor->get_width() == floor->get_width() - 1)) {
        right = false;
    }
    // the bottom of map
    if (index + floor->get_width() >= floor->get_num_cells()) {
        bottom = false;
    }

    while (true) {
        // randomly select a row and colume modifier
        int h_rand = (rand() % 3) - 1;
        int w_rand = (rand() % 3) - 1;
        // checks the boundarys if the cell is valid
        if (!top && h_rand == -1) {
            continue;
        }
        if (!left && w_rand == -1) {
            continue;
        }
        if (!right && w_rand == 1) {
            continue;
        }
        if (!bottom && h_rand == 1) {
            continue;
        }
        if (h_rand == 0 && w_rand == 0) {
            continue;
        }
        // calculate the target cell index
        int ret_index = index + h_rand * floor->get_width() + w_rand;
        // get target cell ptr
        Cell* ret_cell = floor->get_cell_at_index(ret_index);
        
        EntitySpawnable* ret_es = dynamic_cast<EntitySpawnable*> (ret_cell);
        // if the target cell is EntitySpawnable and not occupied
        if (ret_es && (ret_es->get_entity_on_cell() == nullptr) && (ret_es->get_player_on_cell() == nullptr)) {
            return ret_cell;
        }
        else {
            continue;
        }
    }
}


// generate_objects(floor, pc, num_stairway, num_potions, num_gold, num_enemy, num_player):
//      randomly generates the given number of each objects onto the floor
// Require: floor is a valid floor
//          pc is a valid pc
void generate_objects(Floor* floor, PC* pc, int num_stairway = DEFAULT_NUM_STAIRWAY, int num_potions = DEFAULT_NUM_POTIONS, 
                      int num_gold = DEFAULT_NUM_GOLD, int num_enemy = DEFAULT_NUM_ENEMY, int num_player = DEFAULT_NUM_PLAYER) {
    // get chamber informations and relative counters                    
    int num_chambers = floor->get_num_chambers();
    int chamber_index = 0;
    int cell_index = 0;

    // attach player to floor
    floor->set_pc_on_floor(pc);

    // generate player:
    for (int i = 0; i < num_player; i++) {
        // randomly select a chamber
        chamber_index = rand() % num_chambers;
        // randomly selects a cell from the chamber
        cell_index = get_cell_from_chamber(floor->get_chamber_at_index(chamber_index));
        PlayerWalkableCell* pwc = dynamic_cast<PlayerWalkableCell*>(floor->get_cell_at_index(cell_index));
        if (pwc) {
            // bind pc to cell
            pc->set_tile_ID(cell_index);
            // bind cell to player
            pwc->set_player_on_cell(pc);
        }
        // associate player to chamber
        floor->get_chamber_at_index(chamber_index)->set_has_player(true);
        // updates floor player counter
        floor->get_chamber_at_index(chamber_index)->set_num_entities(floor->get_chamber_at_index(chamber_index)->get_num_entities() + 1);
    }

    // generate stairway
    for (int i = 0; i < num_stairway; i++) {
        // randomly generate a chamber without the player in it
        while(true) {
            chamber_index = rand() % num_chambers;
            if (floor->get_chamber_at_index(chamber_index)->get_num_entities() >= floor->get_num_cells()) {
                continue;
            }
            if (floor->get_chamber_at_index(chamber_index)->get_has_player()) {
                continue;
            }
            break;
        }
        // randomly generate a cell in the chamber
        cell_index = get_cell_from_chamber(floor->get_chamber_at_index(chamber_index));
        // initialize stairway on give cell
        Stairway* stw = new Stairway(cell_index);
        // attach stairway to cell
        attach_entity_to_cell(floor, cell_index, stw);

        // adds stairway to floor
        floor->emplace_entity(stw);
        floor->set_num_stairway(floor->get_num_stairway() + 1);
        floor->get_chamber_at_index(chamber_index)->set_num_entities(floor->get_chamber_at_index(chamber_index)->get_num_entities() + 1);
    }

    // generate potion
    for (int i = 0; i < num_potions; i++) {
        // randomly select a chamber that is not full
        while(true) {
            chamber_index = rand() % num_chambers;
            if (floor->get_chamber_at_index(chamber_index)->get_num_entities() >= floor->get_num_cells()) {
                continue;
            }
            break;
        }
        // randomly select a cell in that chamber
        cell_index = get_cell_from_chamber(floor->get_chamber_at_index(chamber_index));

        // randomly select a potion type
        int pot_type = rand() % RATE_OF_POTIONS;
        potion *pot = nullptr;
        if (pot_type <= RH_RATE) {
            pot = new potionHP(true, cell_index, BUFF_H_POTION_VAL);
        } else if (pot_type > RH_RATE && pot_type <= BA_RATE) {
            pot = new potionAtk(true, cell_index, BUFF_ATK_POTION_VAL);
        } else if (pot_type > BA_RATE && pot_type <= BD_RATE) {
            pot = new potionDef(true, cell_index, BUFF_DEF_POTION_VAL);
        } else if (pot_type > BD_RATE && pot_type <= PH_RATE) {
            pot = new potionHP(false, cell_index, NERF_H_POTION_VAL);
        } else if (pot_type > PH_RATE && pot_type <= WA_RATE) {
            pot = new potionAtk(false, cell_index, NERF_ATK_POTION_VAL);
        } else if (pot_type > WA_RATE && pot_type <= WD_RATE) {
            pot = new potionDef(false, cell_index, NERF_DEF_POTION_VAL);
        }
        // attach potion to cell
        attach_entity_to_cell(floor, cell_index, pot);

        // adds potion to floor
        floor->emplace_entity(pot);
        floor->set_num_potions(floor->get_num_potions() + 1);
        floor->get_chamber_at_index(chamber_index)->set_num_entities(floor->get_chamber_at_index(chamber_index)->get_num_entities() + 1);
    }

    // generate gold
    for (int i = 0; i < num_gold; i++) {
        // randomly select a chamber that is not full
        while(true) {
            chamber_index = rand() % num_chambers;
            if (floor->get_chamber_at_index(chamber_index)->get_num_entities() >= floor->get_num_cells()) {
                continue;
            }
            break;
        }
        // randomly select a cell in the chamber
        cell_index = get_cell_from_chamber(floor->get_chamber_at_index(chamber_index));

        // randomly select the type of gold with predetermained odds
        int gold_type = rand() % RATE_OF_GOLD;

        // if a dragon hoard needs to be generated
        if (gold_type > NGP_RATE && gold_type <= DH_RATE) {
            // initialize hoard on cell
            treDragon* drag_gold = new treDragon(DH_VAL, cell_index);
            // randomly select a surrounding cell to generate dragoon
            Cell* drag_cell = rand_a_surrounding_cell(floor, cell_index);
            // initialize dragon
            dragon *drag = new dragon(drag_cell->get_index(), cell_index);
            // attach dragon to hoard
            drag_gold->set_guard(drag);

            // adds dragon and hoard to cell
            attach_entity_to_cell(floor, cell_index, drag_gold);
            attach_entity_to_cell(floor, drag_cell->get_index(), drag);

            // adds dragon and hoard to floor
            floor->emplace_entity(drag_gold);
            floor->emplace_entity(drag);
            floor->set_num_gold(floor->get_num_gold() + 1);
            floor->get_chamber_at_index(chamber_index)->set_num_entities(floor->get_chamber_at_index(chamber_index)->get_num_entities() + 2);
        } else {
            // placeholder
            treGround* gold = nullptr;
            // initialize other individual types of gold
            if (gold_type > DH_RATE && gold_type <= SH_RATE) {
                gold = new treGround(SH_VAL, cell_index, SH_MSG);
            } else if (gold_type <= NGP_RATE) {
                gold = new treGround(NGP_VAL, cell_index, NGP_MSG);
            }
            // attach gold to cell
            attach_entity_to_cell(floor, cell_index, gold);
            // adds gold to floor
            floor->emplace_entity(gold);
            floor->set_num_gold(floor->get_num_gold() + 1);
            floor->get_chamber_at_index(chamber_index)->set_num_entities(floor->get_chamber_at_index(chamber_index)->get_num_entities() + 1);
        }
        
    }

    // generate enemy
    for (int i = 0; i < num_enemy; i++) {
        // randomly select a chamber that is not full
        while(true) {
            chamber_index = rand() % num_chambers;
            if (floor->get_chamber_at_index(chamber_index)->get_num_entities() >= floor->get_num_cells()) {
                continue;
            }
            break;
        }
        // randomly select a cell in the chamber
        cell_index = get_cell_from_chamber(floor->get_chamber_at_index(chamber_index));
        // randomly select an enemy type with predetermined odds
        int enemy_type = rand() % RATE_OF_ENEMY;
        // place holder
        NPC *npc = nullptr;
        // initialize the different types of enemy
        if (enemy_type <= HUMAN_RATE) {
            npc = new human(cell_index);
        } else if (enemy_type > HUMAN_RATE && enemy_type <= DWARF_RATE) {
            npc = new dwarf(cell_index);
        } else if (enemy_type > DWARF_RATE && enemy_type <= HALFLING_RATE) {
            npc = new halfling(cell_index);
        } else if (enemy_type > HALFLING_RATE && enemy_type <= ELF_RATE) {
            npc = new elf(cell_index);
        } else if (enemy_type > ELF_RATE && enemy_type <= ORC_RATE) {
            npc = new orcs(cell_index);
        } else if (enemy_type > ORC_RATE && enemy_type <= MER_RATE) {
            npc = new merchant(cell_index);
        }

        // attach enemy to cell
        attach_entity_to_cell(floor, cell_index, npc);

        // adds enemy to floor
        floor->emplace_entity(npc);
        floor->set_num_enemy(floor->get_num_enemy() + 1);
        floor->get_chamber_at_index(chamber_index)->set_num_entities(floor->get_chamber_at_index(chamber_index)->get_num_entities() + 1);
    }
}

// determine_all_chambers(game, num_chambers) :
//      processes and fills all chambers on all floors of the game with their corresponding inner cells
// Require: game is a valid game
//          each floor of the game has exactly (num_chambers) number of chambers
void determine_all_chambers(Game *game, int num_chambers) {
    int num_floors = game->get_num_floors();
    for (int i = 0; i < num_floors; i++) {
        determine_chambers_on_flr(game->get_floor_at(i), num_chambers);
    }
}

// get_new_cell (curr_tile, new_tile, cmd) interprets the command given and determines the corresponding tile
bool get_new_cell(int curr_tile, int& new_tile, string cmd) {
    const int row = 79;
    if (cmd == "nw") {
        new_tile = curr_tile - row - 1;                
    } else if (cmd == "no") {
        new_tile = curr_tile - row;
    } else if (cmd == "ne") {
        new_tile = curr_tile - row + 1;
    } else if (cmd == "we") {
        new_tile = curr_tile - 1;
    } else if (cmd == "ea") {
        new_tile = curr_tile + 1;
    } else if (cmd == "sw") {
        new_tile = curr_tile + row - 1;
    } else if (cmd == "so") {
        new_tile = curr_tile + row;
    } else if (cmd == "se") {
        new_tile = curr_tile + row + 1;
    } else {
        return false;
    }
    return true;
}

int main(int argc, char *argv[]) {
    std::string filename{"empty.txt"};
    // if a file argument is provided
    if (argc > 1) {
        filename = argv[1];
    } else {
        filename = "empty.txt";
    }

    std::string faction_select;
    cout << "Welcome to CC3K! Please enter the faction that you'd like to play." << endl;
    // select a race to play
    while (true) {
        cin >> faction_select;
        if (faction_select == "s" || faction_select == "d" || faction_select == "v" 
            || faction_select == "g" || faction_select == "t") { break; }
        if (faction_select == "q") {
            std::cout << "Goodbye and play again!" << endl;
            return 0;
        }
        cout << "your command is not valid, please enter a valid faction" << endl;
    }
    cin.ignore();
    
    int num_floors = NUM_FLOORS;
    int num_players = NUM_PLAYERS;
    int map_height = DEFAULT_HEIGHT;
    int map_width = DEFAULT_WIDTH;
    int num_chambers = DEFAULT_CHAMBER_ON_FLOOR;
    int num_stairway = DEFAULT_NUM_STAIRWAY;
    int num_potions = DEFAULT_NUM_POTIONS;
    int num_gold = DEFAULT_NUM_GOLD;
    int num_enemy = DEFAULT_NUM_ENEMY;

    Game* game = new Game(num_floors);
    bool contain_things = read_entity_map_file(game, filename, map_width, map_height, num_floors, faction_select);
    
    if (!contain_things) {
        determine_all_chambers(game, num_chambers);
        for (int i = 0; i < num_floors; i++) {
            Floor* curr_flr = game->get_floor_at(i);
            if (num_chambers == DEFAULT_CHAMBER_ON_FLOOR) {
                PC* pc;
                if (faction_select == "s") {
                    pc = new shade(-1);
                } else if (faction_select == "d") {
                    pc = new drow(-1);
                } else if (faction_select == "v") {
                    pc = new vampire(-1);
                } else if (faction_select == "g") {
                    pc = new goblin(-1);
                } else if (faction_select == "t") {
                    pc = new troll(-1);
                }
                generate_objects(curr_flr, pc, num_stairway, num_potions, num_gold, num_enemy, num_players);
            }
        }
    }

    int floor_id = 0;
    bool NPC_move_enabled = true;
    const string invalid = "That is not a valid move. Please enter another move:";
    Floor* flr = game->get_floor_at(floor_id);
    std::ostringstream round_action;
    PC* curr_player = flr->get_pc_on_floor();

    while (true) {
        if (curr_player->get_hp() <= 0) {
            render_map(flr);
            std::cout << "Whoops, it seems like you lost" << endl;
            std::cout << "Your final score is:" << curr_player->get_gold() << endl;
            delete game;
            return 0;
        }
        // troll's ability
        if (curr_player->get_faction() == "troll") {
            curr_player->mod_hp(5);
        }
        // print the board and reset round action
        render_map(flr);
        cout << round_action.str();
        round_action.str("");
        while (true) {
            string cmd, cmd_supp, cmd_line;
            const int max_tile = 1974; // 25 * 79 - 1
            getline(cin, cmd_line);
            istringstream iss (cmd_line);
            iss >> cmd;
            int new_tile;
            int curr_tile = flr->get_pc_on_floor()->get_tile_ID();
            // guard undefined input
            if (cmd != "no" && cmd != "so" && cmd != "ea" && cmd != "we" && cmd != "ne" && cmd != "nw"
                && cmd != "se" && cmd != "sw" && cmd != "a" && cmd != "u" && cmd != "f" && cmd != "r"
                && cmd != "q") {
                    std::cout << invalid << std::endl;
                    continue;
                }
            // quit game
            if (cmd == "q") {
                std::cout << "Goodbye and play again!" << endl;
                delete game;
                return 0;
            }
            // enable and disable NPC movement
            if (cmd == "f") {
                NPC_move_enabled = !NPC_move_enabled;
                if (NPC_move_enabled) {
                    std::cout << "NPC movement enabled" << endl;
                } else {
                    std::cout << "NPC movement disabled" << endl;
                }
            }

            // if movement commands
            if (cmd == "no" || cmd == "so" || cmd == "ea" || cmd == "we" || cmd == "ne" || cmd == "nw"
                || cmd == "se" || cmd == "sw") {
                    get_new_cell(curr_tile, new_tile, cmd);
                    Cell* move_to_cell = flr->get_cell_at_index(new_tile);
                // check to make sure it's a tile that a player can be on
                if (!move_to_cell->get_player_walkable()) {
                    std::cout << invalid << std::endl;
                    continue;
                }
                // if the tile can have an entity
                if (move_to_cell->get_entity_spawnable()) {
                    EntitySpawnable* move_cell_casted = dynamic_cast<EntitySpawnable*>(move_to_cell);
                    Entity* entity = move_cell_casted->get_entity_on_cell();
                    if (entity != nullptr) {
                        // if the entity on the tile is an NPC or potion
                        if (entity->is_NPC() || entity->is_pot()) {
                            std::cout << invalid << std::endl;
                            continue;
                        }
                        // if the entity on the tile is a gold hoard
                        if (entity->is_gold()) {
                            Treasure* treasure = dynamic_cast<Treasure*>(entity);
                            if (treasure->is_treDragon()) {
                                treDragon* treasure_dragon = dynamic_cast<treDragon*>(treasure);
                                if (treasure_dragon->get_guard() == nullptr) {
                                    treasure_dragon->consume_item(curr_player);
                                    move_cell_casted->set_entity_on_cell(nullptr);
                                    move_cell_casted->set_open_to_entity(true);
                                    //round_action << "Player moves " << cmd << " and picks up some gold\n";
                                }
                            } else {
                                treasure->consume_item(curr_player);
                                move_cell_casted->set_entity_on_cell(nullptr);
                                move_cell_casted->set_open_to_entity(true);
                               // round_action << "Player moves " << cmd << " and picks up some gold\n";
                            }
                        }
                        // if the entity is a stair case
                        if (!entity->is_gold()) {
                            // if top floor
                            if (floor_id == 4) {
                                cout << "congratulations, you won!" << endl;
                                cout << "Your final score is:" << curr_player->get_gold() << endl;
                                delete game;
                                return 0;
                            }
                            // set to higher floor
                            int curr_hp = curr_player->get_hp();
                            int curr_gold = curr_player->get_gold();
                            bool curr_merch_status = curr_player->get_merch_stat();
                            floor_id++;
                            flr = game->get_floor_at(floor_id);
                            curr_player = flr->get_pc_on_floor();
                            // set HP
                            curr_player->mod_hp(-(curr_player->get_hp() - curr_hp));
                            // set merchant status
                            curr_player->set_merch_stat(curr_merch_status);
                            // set gold
                            curr_player->mod_gold(curr_gold);
                            round_action << "Player advances to another floor!\n"; 
                            break;
                        }
                    }

                }
                PlayerWalkableCell* move_to_casted = dynamic_cast<PlayerWalkableCell*>(move_to_cell);
                PlayerWalkableCell* curr_cell_casted = dynamic_cast<PlayerWalkableCell*>(flr->get_cell_at_index(curr_tile));
                move_to_casted->set_player_on_cell(curr_player);
                curr_cell_casted->set_player_on_cell(nullptr);
                curr_player->set_tile_ID(new_tile);
                round_action << "Player moves " << cmd << "\n";
                break;             
            }

            // if attack or use potion
            if (cmd == "a" || cmd == "u") {
                // interpret direction
                iss >> cmd_supp;
                if (!get_new_cell(curr_tile, new_tile, cmd_supp)) {
                    std::cout << invalid << std::endl;
                    continue;
                }
            }

            // check if out of bound
            if (new_tile < 0 || new_tile > max_tile) {
                std::cout << invalid << std::endl;
                continue;
            }

            // attack function
            if (cmd == "a") {
                Cell* enemy_cell = flr->get_cell_at_index(new_tile);
                // check to make sure it's a tile that an entity can be on
                if (!enemy_cell->get_entity_spawnable()) {
                    std::cout << invalid << std::endl;
                    continue;
                }
                EntitySpawnable* enemy_cell_casted = dynamic_cast<EntitySpawnable*>(enemy_cell);
                Entity* entity = enemy_cell_casted->get_entity_on_cell();
                // if no entities exist
                if (entity == nullptr) {
                    std::cout << invalid << std::endl;
                    continue;
                }
                // if entity is not NPC
                if (!entity->is_NPC()) {
                    std::cout << invalid << std::endl;
                    continue;
                }
                NPC* enemy = dynamic_cast<NPC*> (entity);
                // check if player misses
                if (curr_player->get_miss()) {
                    curr_player->set_miss(false);
                    int hit = rand() % 2;
                    if (hit == 0) {
                        round_action << "Player attacks the " << enemy->get_faction() << " but missed!\n";
                        break;
                    }
                }
                // set merchant aggro once attacked
                if (enemy->get_faction() == "merchant") {
                    curr_player->set_merch_stat(false);
                }

                // dwarf and vampire ability
                if (curr_player->get_faction() == "vampire") {
                    if (enemy->get_faction() == "dwarf") {
                        curr_player->mod_hp(-5);
                    } else {
                        curr_player->mod_hp(5);
                    }
                }

                int atk = curr_player->get_atk();
                int def = enemy->get_def();
                int dmg = calculate_dmg(atk, def);
                // if the enemy is killed
                if (!enemy->mod_hp(-dmg)) {
                    // make dragon hoard available
                    if (enemy->get_faction() == "dragon") {
                        dragon* enemy_casted = dynamic_cast<dragon*>(enemy);

                        std::cout << enemy_casted->get_tile_ID() << enemy_casted->get_treasure_tild_ID() << endl; // TESTER DELET!!!

                        Cell* hoard_tile = flr->get_cell_at_index(enemy_casted->get_treasure_tild_ID());
                        EntitySpawnable* hoard_tile_casted = dynamic_cast<EntitySpawnable*>(hoard_tile);
                        treDragon* dragon_hoard = dynamic_cast<treDragon*>(hoard_tile_casted->get_entity_on_cell());
                        dragon_hoard->set_guard(nullptr);
                        enemy_casted->set_treasure_tild_ID(-1);
                        enemy_cell_casted->set_entity_on_cell(nullptr);
                        enemy_cell_casted->set_open_to_entity(true);
                    } else if (enemy->get_faction() == "merchant") {
                        // spawn merchant hoard when merchant is killed
                        treGround* merch_hoard = new treGround(4, enemy->get_tile_ID(), "merchant");
                        flr->emplace_entity(merch_hoard);
                        enemy_cell_casted->set_entity_on_cell(merch_hoard);
                    } else if (enemy->get_faction() == "human") {
                        // spawn human drop
                        treGround* human_hoard = new treGround(4, enemy->get_tile_ID(), "human");
                        flr->emplace_entity(human_hoard);
                        enemy_cell_casted->set_entity_on_cell(human_hoard);
                    } else {
                        // for other NPCs killed
                        srand(time(0));
                        int drop = rand() % 2;
                        if (drop == 0) {
                            curr_player->mod_gold(1);
                        } else {
                            curr_player->mod_gold(2);
                        }
                        enemy_cell_casted->set_entity_on_cell(nullptr);
                        enemy_cell_casted->set_open_to_entity(true);
                    }
                    enemy->set_tile_ID(-1);
                    round_action << "Player attacks the " << enemy->get_faction() << " and killed it!\n";
                    // goblin ability
                    if (curr_player->get_faction() == "goblin") {
                        curr_player->mod_gold(5);
                    }
                } else {
                    round_action << "Player attacks the " << enemy->get_faction() << "("<< enemy->get_hp() << " HP)"
                    " and dealt " << dmg << " damage!\n";
                }
                break;
            }

            if (cmd == "u") {
                Cell* potion_cell = flr->get_cell_at_index(new_tile);
                // check to make sure it's a tile that an entity can be on
                if (!potion_cell->get_entity_spawnable()) {
                    std::cout << invalid << std::endl;
                    continue;
                }
                EntitySpawnable* pot_cell_casted = dynamic_cast<EntitySpawnable*>(potion_cell);
                Entity* entity = pot_cell_casted->get_entity_on_cell();
                // if no entities exist
                if (entity == nullptr) {
                    std::cout << invalid << std::endl;
                    continue;
                }
                // if entity is not potion
                if (!entity->is_pot()) {
                    std::cout << invalid << std::endl;
                    continue;
                }
                potion* pot = dynamic_cast<potion*> (entity);
                PC* deco = pot->consume_item(curr_player);
                if (deco != nullptr) {
                    // attach decorator
                    curr_player = deco;
                    flr->set_pc_on_floor(deco);
                }
                pot_cell_casted->set_entity_on_cell(nullptr);
                pot_cell_casted->set_open_to_entity(true);
                pot->set_tile_ID(-1);
                round_action << "Player consumes an unknown potion\n";
                break;
            }       
        }

        // process NPC moves
        int total_entity = flr->get_num_enemy() + flr->get_num_gold() + flr->get_num_potions() + 1;
        for (int j = 0; j < total_entity; ++j) {
            Entity* ent_on_tile = flr->get_entity_at_index(j);
            if (ent_on_tile != nullptr) {
                if (ent_on_tile->is_NPC()) {
                    NPC* NPC_on_tile = dynamic_cast<NPC*>(ent_on_tile);
                    if (NPC_on_tile->get_hp() > 0) {
                        if (NPC_on_tile->get_faction() == "dragon") {
                            dragon* drag = dynamic_cast<dragon*>(NPC_on_tile);
                            process_dragon(drag, flr, round_action);
                        } else {
                            process_NPC_action(NPC_on_tile, flr, NPC_move_enabled, round_action);
                        }   
                    }
                }
            }
        }
    }
}
