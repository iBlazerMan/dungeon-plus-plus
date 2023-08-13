#include "constants.h"

const char WALL_HORIZONTAL = '-';
const char WALL_VERTICAL = '|';
const char VOID_CELL = ' ';
const char FLOOR_TILE = '.';
const char DOORWAY = '+';
const char PASSAGE = '#';

const char STAIRWAY = '\\';

const char PLAYER = '@';

const char ENEMY_HUMAN_RENDER = 'H';
const char ENEMY_DWARF_RENDER = 'W';
const char ENEMY_ELF_RENDER = 'E';
const char ENEMY_ORC_RENDER = 'O';
const char ENEMY_MERCHANT_RENDER = 'M';
const char ENEMY_DRAGON_RENDER = 'D';
const char ENEMY_HALFLING_RENDER = 'L';

const char POTION_RENDER = 'P';
const char GOLD_RENDER = 'G';

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
