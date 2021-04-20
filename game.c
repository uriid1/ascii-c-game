///******************************//#
///# Author: by uriid1		#//#
///# license: GNU GPL		#//#
///# telegram: uriid1		#//#
///# Mail: appdurov@gmail.com	#//#
//##****************************####

#include <stdio.h>
#include <string.h>
#include <ncurses.h>

// Const
#define nil -1

// Key Kode
#define vk_space  32
#define vk_enter  10
int key_pressed;

// Const Color
const short c_wall   = 1;
const short c_apple  = 2;
const short c_door   = 3;
const short c_space  = 4;
const short c_life   = 5;
const short c_player = 6;
const short c_bullet = 6;
const short c_enemy  = 7;
const short c_box    = 8;

// Game Global var
bool EXIT = false;
short level     = 1;
short score     = 0;
short lifes	= 3;
int bullet_shoot = false;

// index map object
#define i_wall   1
#define i_apple  2
#define i_door   3
#define i_space  4
#define i_life	 5
#define i_exit   6
#define i_enemy  7
#define i_box    8

///////////////////////  MENU
// MENU
bool menu = true;
// logo
char menu_logo[] = "\t     e Y8b                       888         Y8b Y8b Y888P \n\t    d8b Y8b    888 88e  888 88e  888  ,e e,   Y8b Y8b Y8P   ,8Y88b 888*,8, \n\t   d888b Y8b   888 888b 888 888b 888 d88 88b   Y8b Y8b Y    8  888 888  88  \n\t  d888888888b  888 888P 888 888P 888 888        Y8b Y8b     ee 888 888       \n\t d8888888b Y8b 888 88.  888 88.  888  .YeeP.     Y8P Y      88 888 888       \n\t               888      888 \n\t               888      888    \n\t";

/////////////////////// LEVEL MAPS
// Map
short arr_size_x;
#define s_wall  "###"
#define s_apple " @ "
#define s_empty "   "
#define s_door  "-^-"
#define s_life  "(+)"
#define s_enemy "<^>"
#define s_box   "|=|"

// Lvl 1
#define lvl_one_x 27
#define lvl_one_y 20
short level_one_size = lvl_one_x;
short lvl_one[lvl_one_y][lvl_one_x] = {
	// Level one
	{ 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 3, 1 },
	{ 4, 1, 0, 2, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
	{ 4, 1, 1, 1, 1, 1, 1, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6, 6, 6, 1 }
	//
};

// Lvl 2
#define lvl_two_x 27
#define lvl_two_y 20
short level_two_size = lvl_two_x;
short lvl_two[lvl_two_y][lvl_two_x] = {
	// Level two
	{ 4, 1, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 4, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 8, 8, 0, 0, 0, 0, 3, 0, 0, 6 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 2, 2, 2, 8, 0, 0, 0, 0, 3, 0, 0, 6 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 2, 2, 2, 8, 0, 0, 0, 0, 1, 1, 1, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 2, 2, 2, 8, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 2, 5, 2, 8, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 2, 2, 2, 8, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 2, 2, 2, 8, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 2, 2, 2, 8, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	//
};

// Lvl 3
#define lvl_three_x 27
#define lvl_three_y 20
short level_three_size = lvl_two_x;
short lvl_three[lvl_three_y][lvl_three_x] = {
	// Level three
	{ 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6, 1, 1, 1, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 1, 7, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 1, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 1, 1, 0, 0, 0, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 4, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1 ,7, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	//
};


// Lvl 4
#define lvl_fo_x 27
#define lvl_fo_y 20
short level_fo_size = lvl_fo_x;
short lvl_fo[lvl_fo_y][lvl_fo_x] = {
	// Level fo
	{ 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 1, 1, 1, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 8, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 8, 2, 2, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 8, 2, 7, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 8, 2, 2, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 8, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 2, 2, 2, 8, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 2, 7, 2, 8, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 2, 2, 2, 8, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 1, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 1, 1, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	//
};

// Lvl 5
#define lvl_five_x 27
#define lvl_five_y 20
short level_five_size = lvl_five_x;
short lvl_five[lvl_five_y][lvl_five_x] = {
	// Level five
	{ 4, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 4, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 7, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 1, 6, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 1, 6, 0, 3, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 1, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 0, 1 },
	{ 4, 1, 0, 2, 1, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 5, 8, 2, 1 },
	{ 4, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 2 ,0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	//
};


// Lvl 6
#define lvl_six_x 27
#define lvl_six_y 20
short level_six_size = lvl_six_x;
short lvl_six[lvl_six_y][lvl_six_x] = {
	// Level six
	{ 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6, 1, 1, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
	{ 4, 1, 0, 0, 2, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 1, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1 },
	{ 4, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 6 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 7, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 7, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 2, 0, 1, 1, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 1, 0, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 2, 1 },
	{ 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
	{ 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6, 1, 1, 1 }
	//
};


// lvl win
#define lvl_win_x 27
#define lvl_win_y 20
short level_win_size = lvl_win_x;
short lvl_win[lvl_win_y][lvl_win_x] = {
	// Level win
	{ 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 4, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
	{ 4, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
	{ 4, 1, 2, 1, 2, 2, 1, 2, 2, 1, 1, 2, 2, 1, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
	{ 4, 1, 2, 1, 2, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
	{ 4, 1, 2, 1, 2, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
	{ 4, 1, 2, 1, 2, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
	{ 4, 1, 2, 1, 1, 1, 1, 2, 2, 1, 1, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
	{ 4, 1, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
	{ 4, 1, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
	{ 4, 1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
	{ 4, 1, 2, 2, 1, 2, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2, 2, 2, 2, 1 },
	{ 4, 1, 2, 1, 2, 2, 2, 2, 1, 2, 1, 2, 1, 2, 2, 2, 1, 1, 2, 1, 2, 1, 2, 2, 2, 2, 1 },
	{ 4, 1, 2, 2, 2, 2, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 2, 1, 2, 2, 2, 2, 1 },
	{ 4, 1, 2, 2, 2, 2, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 },
	{ 4, 1, 2, 2, 2, 2, 2, 2, 1, 1, 2, 1, 1, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2, 2, 2, 2, 1 },
	{ 4, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
	{ 4, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 ,2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
	{ 4, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
	{ 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	//
};

///////////////////////  COLORSHEME
// Set color
void SetColor() {
	start_color();
	init_pair(c_wall,   COLOR_BLUE,     COLOR_BLACK);
	init_pair(c_apple,  COLOR_WHITE,    COLOR_BLACK);
	init_pair(c_door,   COLOR_RED,      COLOR_BLACK);	
	init_pair(c_space,  COLOR_BLACK,    COLOR_BLACK);
	init_pair(c_life,   COLOR_GREEN,    COLOR_BLACK);
	init_pair(c_player, COLOR_MAGENTA,  COLOR_BLACK);
	init_pair(c_bullet, COLOR_GREEN,    COLOR_BLACK);
	init_pair(c_enemy,  COLOR_BLACK,    COLOR_RED);
	init_pair(c_box,    COLOR_YELLOW,   COLOR_BLACK);
}

// Draw colored instance
void draw_instance(int color, char name[]) {
	attron(COLOR_PAIR(color));
	printw(name);
	attroff(COLOR_PAIR(color));
}

///////////////////////  OBJECT 
// Class
struct class_obj {
	char symbol[20];
	int x;
	int y;
	int direction;
};

// Create objects
struct class_obj player = {};
struct class_obj bullet = {};
struct class_obj enemy[5]={};

// Enemy movement
void enemy_move(short current_lvl[][arr_size_x], int index) {
	switch(index) {
		// hsp
		case 0:
		case 1:
		case 2:
			if (current_lvl[enemy[index].y][enemy[index].x] == i_wall || 
				current_lvl[enemy[index].y][enemy[index].x] == i_door || 
				current_lvl[enemy[index].y][enemy[index].x] == i_box)
			{
				enemy[index].direction *= -1;
			}
			enemy[index].y = enemy[index].y + enemy[index].direction;
		break;

		// vsp
		case 3:
		case 4:
		case 5:
			if (current_lvl[enemy[index].y][enemy[index].x] == i_wall || 
				current_lvl[enemy[index].y][enemy[index].x] == i_door || 
				current_lvl[enemy[index].y][enemy[index].x] == i_box)
			{
				enemy[index].direction *= -1;
			}
			enemy[index].x = enemy[index].x + enemy[index].direction;
		break;
	}
}

// Enemy clear
void clear_enemy() {
	for (int i = 0; i < 5; i++) {
		enemy[i].y = 0;
		enemy[i].x = 0;
		enemy[i].direction = 0;
	}
}


// set obj Parametrs
void obj_init(struct class_obj *obj, int x, int y, int dir, char *objname) {
	obj->x = x;
	obj->y = y;
	obj->direction = dir;
	strcpy(obj->symbol, objname);
}

/////////////////////// PLAYER
// Playes method move
int dir_x;
int dir_y;
int dir_shoot;
void player_move(int key) {
	// Key check
	int key_left  = ( key == KEY_LEFT  ) ? 1 : 0;
	int key_right = ( key == KEY_RIGHT ) ? 1 : 0;
	int key_down  = ( key == KEY_DOWN  ) ? 1 : 0;
	int key_up    = ( key == KEY_UP    ) ? 1 : 0;

	// key dir
	dir_x = key_right - key_left;
	dir_y = key_down  - key_up;

	// Animation and direction shoot
	if (dir_x == 0 && dir_y == 0) {
		strcpy(player.symbol, "|0|");
	} else {
		if ( dir_x ==  1 ) { dir_shoot =  1; strcpy(player.symbol, "|0>"  );}
		if ( dir_x == -1 ) { dir_shoot = -1; strcpy(player.symbol, "<0|"  );}
		if ( dir_y == -1 ) { dir_shoot = -2; strcpy(player.symbol, "/0\\" );}
		if ( dir_y ==  1 ) { dir_shoot =  2; strcpy(player.symbol, "\\0/" );}
	}

	player.x = player.x + dir_x;
	player.y = player.y + dir_y;
}

// Collsiion
void player_collision(short current_lvl[][arr_size_x]) {
	switch(current_lvl[player.y][player.x]) {
		case i_wall: 	// wall
		case i_box:  	// box
		case i_door: 	// door
		case i_space:	// space
			player.x = player.x - dir_x;
			player.y = player.y - dir_y;
		break;

		// Apple collision
		case i_apple:
			current_lvl[player.y][player.x] = 0;
			score = score - 1;
		break;

		// key
		case i_life:
			current_lvl[player.y][player.x] = 0;
			lifes = lifes + 1;
		break;
	}

	// Enemy collision
	for (int i = 0; i < 5; i++) {
		if (player.y == enemy[i].y && player.x == enemy[i].x) {
			lifes = lifes - 1; 
		}
	}
}

/////////////////////// BULLET
// Bullet
void bulet_collision(short current_lvl[][arr_size_x]) {
	switch(current_lvl[bullet.y][bullet.x]) {
		case i_wall:
		case i_door:
		case i_space:
			bullet_shoot = false;
		break;
	}

	// Kill Box
	if (current_lvl[bullet.y][bullet.x] == i_box) {
		current_lvl[bullet.y][bullet.x] = 0;
		bullet_shoot = false;
	}

	// Kill Enemy
	if (bullet_shoot == true) {
		for (int i = 0; i < 5; i++) {
			if (bullet.y == enemy[i].y && bullet.x == enemy[i].x) {
				enemy[i].y = 0;
				enemy[i].x = 0;
				enemy[i].direction = 0;
				bullet_shoot = false;
			}
		}
	}
}

/////////////////////// LEVELs
// Set enemy and calck apple
void set_lvl_param(short current_lvl[][arr_size_x], int clx, int cly) {
	static int i = 0;
	for (int y = 0; y < cly; y++) {
		for (int x = 0; x < clx; x++) {
			if (current_lvl[y][x] == i_apple) {
				score = score + 1;
			}

			if (current_lvl[y][x] == i_enemy) {
				obj_init(&enemy[i], x, y, 1, "");
				i++;
				if (i >=5) { i = 0; }
			}
		}
	}

}


// Check next lvl
bool next_lvl(short current_lvl[][arr_size_x]) {
	if (current_lvl[player.y][player.x] == i_exit) {
		score = 0;
		level = level + 1;
		return true;
	}

	return false;
}

// Draw Current Level
int current_lvl_x;
int current_lvl_y;
//
void draw_level(short lvl[][arr_size_x]) {
	// Enemy move
	for (int i = 0; i < 5; i++) { enemy_move(lvl, i); }

	//
	for (int y = 0; y < current_lvl_y; y++) {
		for (int x = 0; x < current_lvl_x; x++) {
			switch(lvl[y][x]) {
				case i_wall:   draw_instance(c_wall,  s_wall);  break;
				case i_box:    draw_instance(c_box,   s_box);  break;
				case i_apple:  draw_instance(c_apple, s_apple); break;
				case i_door:   draw_instance(c_door,  s_door);  break;
				case i_space:  draw_instance(c_space, s_empty); break;
				case i_life:   draw_instance(c_life,  s_life);   break;

				default:
					// Draw dynamic
					if (x == player.x && y == player.y) {
						draw_instance(c_player, player.symbol);
					} else if (x == bullet.x && y == bullet.y) {
						if (bullet_shoot) {
							draw_instance(c_space, " ");
							draw_instance(c_bullet, bullet.symbol);
							draw_instance(c_space, " ");
						} else {
							draw_instance(c_space, s_empty);
						}
					} else if (x == enemy[0].x && y == enemy[0].y) {
							draw_instance(c_enemy, s_enemy);
					} else if (x == enemy[1].x && y == enemy[1].y) {
							draw_instance(c_enemy, s_enemy);
					} else if (x == enemy[2].x && y == enemy[2].y) {
							draw_instance(c_enemy, s_enemy);
					} else if (x == enemy[3].x && y == enemy[3].y) {
							draw_instance(c_enemy, s_enemy);
					} else if (x == enemy[4].x && y == enemy[4].y) {
							draw_instance(c_enemy, s_enemy);
					} else if (x == enemy[5].x && y == enemy[5].y) {
							draw_instance(c_enemy, s_enemy);
					} else {
						draw_instance(c_space, s_empty);
					}
				break;
			} // End switch

			// Open door
			if (score == 0) {
				if (lvl[y][x] == i_door) {
					lvl[y][x] = 0;
				}
			}
		}
		printw("\n");
	}
}

/////////////////////// GAME
// Game Over
void game_over() {
	EXIT = true;
	endwin();
    printf("Game Over!\n");
}

/// Update game
void game(int key, short current_lvl[][arr_size_x]) {
	// Player
	player_move(key);
	player_collision(current_lvl);

	// Bullet
	bulet_collision(current_lvl);

	// Draw map
	draw_level(current_lvl);

	// Over
	if (lifes <= 0) { game_over(); }
}

// Init lvl
void level_init(short index_lvl) {
	static bool init = true;

	if (init == false) {
		if (index_lvl == 1) { init = next_lvl(lvl_one);   game(key_pressed, lvl_one); 	}
		if (index_lvl == 2) { init = next_lvl(lvl_two);   game(key_pressed, lvl_two); 	}
		if (index_lvl == 3) { init = next_lvl(lvl_three); game(key_pressed, lvl_three); }
		if (index_lvl == 4) { init = next_lvl(lvl_fo);	  game(key_pressed, lvl_fo);	}
		if (index_lvl == 5) { init = next_lvl(lvl_five);  game(key_pressed, lvl_five);	}
		if (index_lvl == 6) { init = next_lvl(lvl_six);   game(key_pressed, lvl_six);	}
		if (index_lvl == 7) { init = next_lvl(lvl_win);   game(key_pressed, lvl_win);	}
	} else {
		switch(index_lvl) {
			case 1:
				player.x = 8;
				player.y = 16;
				current_lvl_x = lvl_one_x;
				current_lvl_y = lvl_one_y;
				arr_size_x = level_one_size;
				clear_enemy();
				set_lvl_param(lvl_one, current_lvl_x, current_lvl_y);
				init = false;
			break;

			case 2:
				player.x = 3;
				player.y = 2;
				current_lvl_x = lvl_two_x;
				current_lvl_y = lvl_two_y;
				arr_size_x = level_two_size;
				clear_enemy();
				set_lvl_param(lvl_two, current_lvl_x, current_lvl_y);
				init = false;
			break;

			case 3:
				player.x = 2;
				player.y = 6;
				current_lvl_x = lvl_three_x;
				current_lvl_y = lvl_three_y;
				arr_size_x = level_three_size;
				clear_enemy();
				set_lvl_param(lvl_three, current_lvl_x, current_lvl_y);
				init = false;
			break;

			case 4:
				player.x = 22;
				player.y = 1;
				current_lvl_x = lvl_fo_x;
				current_lvl_y = lvl_fo_y;
				arr_size_x = level_fo_size;
				clear_enemy();
				set_lvl_param(lvl_fo, current_lvl_x, current_lvl_y);
				init = false;
			break;

			case 5:
				player.x = 4;
				player.y = 1;
				current_lvl_x = lvl_five_x;
				current_lvl_y = lvl_five_y;
				arr_size_x = level_five_size;
				clear_enemy();
				set_lvl_param(lvl_five, current_lvl_x, current_lvl_y);
				init = false;
			break;

			case 6:
				player.x = 8;
				player.y = 13;
				current_lvl_x = lvl_six_x;
				current_lvl_y = lvl_six_y;
				arr_size_x = level_six_size;
				clear_enemy();
				set_lvl_param(lvl_six, current_lvl_x, current_lvl_y);
				init = false;
			break;

			case 7:
				player.x = 23;
				player.y = 5;
				current_lvl_x = lvl_win_x;
				current_lvl_y = lvl_win_y;
				arr_size_x = level_win_size;
				clear_enemy();
				set_lvl_param(lvl_win, current_lvl_x, current_lvl_y);
				init = false;
			break;
		}
	}
}

/////////////////////// MAIN
// main func
int main(void) {

	// init obj
	// Player
	obj_init(&player, 5, 5, 0, "|O|");
	// Bullet
	obj_init(&bullet, player.x, player.x, 0, "*");

	// Start curses mode
	initscr();
	keypad(stdscr, TRUE);

	// if not support color
	if (has_colors() == false) {
        endwin();
        printf("Your terminal does not support color\n");
    }

	// Main loop
	while (!EXIT) {
		clear();
		SetColor();

		static int menu_item = 0;
		if (menu == false) {
			// GAME
			printw("\n   apples: %d    lifes: %d    level: %d \n\n", score, lifes, level);
			level_init(level);

			// Shoot
			if (!bullet_shoot) {
					bullet.x = player.x;
					bullet.y = player.y;
				if (key_pressed == vk_space) {
					bullet.direction = dir_shoot;
					bullet_shoot = true;
				}
			} else {
				switch(bullet.direction) {
					case  1: bullet.x = bullet.x + 1; break;
					case -1: bullet.x = bullet.x - 1; break;
					case  2: bullet.y = bullet.y + 1; break;
					case -2: bullet.y = bullet.y - 1; break;
				}
			}
		} else {
			// MENU
			if (key_pressed == KEY_UP)   menu_item--;
			if (key_pressed == KEY_DOWN) menu_item++;
			if (menu_item >= 2) { menu_item = 2; }
			if (menu_item <= 0) { menu_item = 0; }

			printw("\n\n");
			draw_instance(c_wall, menu_logo);

			printw("\n\n\n\n");
			printw("\t\t\t\t  %s \n\n",  menu_item == 0 ? "    > START GAME <" : "      start game");
			printw("\t\t\t\t\t %s \n\n", menu_item == 1 ? "> INFO <" : "  info");
			printw("\t\t\t\t\t %s \n\n", menu_item == 2 ? "> EXIT <" : "  exit");

			printw("\n\n\n\n\n\n");
			printw(" %s", "Develop: uriid1");

			if (key_pressed == vk_enter) { 
				switch(menu_item) {
					case 0:
						menu = false;
					break;

					case 1:
					break;

					case 2:
						endwin();
						EXIT = true;					
					break;
				}
			}
		}

		//
		key_pressed = getch();

		if (key_pressed == 'q') { menu = true; }
	}

	// End curses mode
	endwin();

	return 0;
}
