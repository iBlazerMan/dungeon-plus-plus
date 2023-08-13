#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

// constants for all maps
extern const char WALL_HORIZONTAL;
extern const char WALL_VERTICAL;
extern const char VOID_CELL;
extern const char FLOOR_TILE;
extern const char DOORWAY;
extern const char PASSAGE;

extern const char STAIRWAY;

extern const char PLAYER;

// constants for rendering map
extern const char ENEMY_HUMAN_RENDER;
extern const char ENEMY_DWARF_RENDER;
extern const char ENEMY_ELF_RENDER;
extern const char ENEMY_ORC_RENDER;
extern const char ENEMY_MERCHANT_RENDER;
extern const char ENEMY_DRAGON_RENDER;
extern const char ENEMY_HALFLING_RENDER;

extern const char POTION_RENDER;
extern const char GOLD_RENDER;

// colors for rendering
extern const std::string BLUE_TEXT;
extern const std::string YELLOW_TEXT;
extern const std::string GREEN_TEXT;
extern const std::string RED_TEXT;
extern const std::string RESET_TEXT;

// constants for reading exising map
extern const char RH;
extern const char BA;
extern const char BD;
extern const char PH;
extern const char WA;
extern const char WD;
extern const char NGP;
extern const char SH;
extern const char MH;
extern const char DH;

extern const int NGP_VAL;
extern const int SH_VAL;
extern const int MH_VAL;
extern const int DH_VAL;

extern const int NUM_PLAYERS;
extern const int NUM_FLOORS;
extern const int DEFAULT_WIDTH;
extern const int DEFAULT_HEIGHT;
extern const int DEFAULT_CHAMBER_ON_FLOOR;

extern const int ARG_NUM_FILENAME;

extern const int RATE_OF_POTIONS;
extern const int RH_RATE;
extern const int BA_RATE;
extern const int BD_RATE;
extern const int PH_RATE;
extern const int WA_RATE;
extern const int WD_RATE;

extern const int RATE_OF_GOLD;
extern const int NGP_RATE;
extern const int DH_RATE;
extern const int SH_RATE;

extern const int RATE_OF_ENEMY;
extern const int HUMAN_RATE;
extern const int DWARF_RATE;
extern const int HALFLING_RATE;
extern const int ELF_RATE;
extern const int ORC_RATE;
extern const int MER_RATE;

extern const int DEFAULT_NUM_STAIRWAY;
extern const int DEFAULT_NUM_POTIONS;
extern const int DEFAULT_NUM_PLAYER;
extern const int DEFAULT_NUM_GOLD;
extern const int DEFAULT_NUM_ENEMY;

extern const int NUM_SURROUNDING_CELL;

extern const int BUFF_ATK_POTION_VAL;
extern const int BUFF_DEF_POTION_VAL;
extern const int BUFF_H_POTION_VAL;
extern const int NERF_ATK_POTION_VAL;
extern const int NERF_DEF_POTION_VAL;
extern const int NERF_H_POTION_VAL;

extern const std::string SH_MSG;
extern const std::string NGP_MSG;
extern const std::string MC_MSG;
extern const std::string DH_MSG;

#endif
