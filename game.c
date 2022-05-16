/*
    ####--------------------------------####
    #--# Author:   by uriid1            #--#
    #--# License:  GNU GPLv3            #--#
    #--# Telegram: @main_moderator      #--#
    #--# E-mail:   appdurov@gmail.com   #--#
    ####--------------------------------####
*/

// Includes
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ncurses.h>

// Key Kode
#define vk_space  32
#define vk_enter  10
int key_pressed = 0;

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
const short c_hud    = 1;

// Const state
bool EXIT = false;

// Game Global var
short level = 1;
short score = 0;
short lifes	= 3;

int apples_in_level = 0;
int bullet_shoot = false;

// Level size
int current_lvl_x;
int current_lvl_y;

// Window width & Height
int w, h;

// index map object
#define i_wall   1
#define i_apple  2
#define i_door   3
#define i_space  4
#define i_life	 5
#define i_exit   6
#define i_enemy_v 7
#define i_box    8
#define i_enemy_h 9

////////////////////
// Menu
///////////////////
const char *menu_logo[7] = {
	"     e Y8b                       888         Y8b Y8b Y888P",
	"    d8b Y8b    888 88e  888 88e  888  ,e e,   Y8b Y8b Y8P   ,8Y88b 888*,8,",
	"   d888b Y8b   888 888b 888 888b 888 d88 88b   Y8b Y8b Y    8  888 888  88",
	"  d888888888b  888 888P 888 888P 888 888        Y8b Y8b     ee 888 888",
    " d8888888b Y8b 888 88.  888 88.  888  .YeeP.     Y8P Y      88 888 888",
    "               888      888",
    "               888      888"
};

// Get char len
int str_len(const char* str) {
	int size = 0;
	while(*str++) ++size;
	return size;
}

// Get logo size
int logo_h_size = sizeof(menu_logo)/sizeof(menu_logo[0]);

// Get logo len
int get_logo_w_size(void) {
	int logo_w_size = 1;

	for (int i = 0; i < logo_h_size; i++) {
		int len = str_len(menu_logo[i]);
		if (len > logo_w_size) {
			logo_w_size = str_len(menu_logo[i]);
		}
	}
	return logo_w_size;
}

// Draw the logo

int logo_w_size = 1;
void draw_logo(int h, int w) {
	// Get w size
	if (logo_w_size == 1) {
		logo_w_size = get_logo_w_size() / 2;
	}

	// Draw
	attron(COLOR_PAIR(c_hud));
	for (int i = 0; i < logo_h_size; i++) {
		mvprintw(3 + i /* Logo Y pos */, w/2 - logo_w_size, menu_logo[i]);
	}
	attroff(COLOR_PAIR(c_hud));
}


/////////////////
// LEVEL MAPS
////////////////
// Map
short arr_size_x;
#define s_wall  "///"
#define s_exit  "***"
#define s_apple "(`)"
#define s_empty "   "
#define s_door  "-^-"
#define s_life  "(+)"
#define s_enemy "(-)"
#define s_box   "[=]"
#define s_space "..."


////////////////
// Level one
///////////////
#define lvl_one_x 27
#define lvl_one_y 20
#define level_one_size lvl_one_x

short lvl_one[lvl_one_y][lvl_one_x] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 3, 1 },
	{ 1, 0, 0, 2, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6, 6, 6, 1 }
};


////////////////
// Level two
////////////////
#define lvl_two_x 27
#define lvl_two_y 20
#define  level_two_size lvl_two_x

short lvl_two[lvl_two_y][lvl_two_x] = {
	{ 1, 1, 4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 8, 8, 0, 0, 0, 0, 3, 0, 0, 6 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 2, 2, 2, 8, 0, 0, 0, 0, 3, 0, 0, 6 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 2, 2, 2, 8, 0, 0, 0, 0, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 2, 2, 2, 8, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 2, 5, 2, 8, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 2, 2, 2, 8, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 2, 2, 2, 8, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 2, 2, 2, 8, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};


////////////////
// Level three
////////////////
#define lvl_three_x 27
#define lvl_three_y 20
#define level_three_size lvl_two_x

short lvl_three[lvl_three_y][lvl_three_x] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 1, 3, 1, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 0, 0, 0, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0 ,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};


////////////////
// Level fo
////////////////
#define lvl_fo_x 27
#define lvl_fo_y 20
#define level_fo_size lvl_fo_x

short lvl_fo[lvl_fo_y][lvl_fo_x] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 8, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 8, 2, 2, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 8, 2, 7, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 8, 2, 2, 2, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 8, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 2, 2, 2, 8, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 2, 7, 2, 8, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 2, 2, 2, 8, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 1, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};


////////////////
// Level five
////////////////
#define lvl_five_x 27
#define lvl_five_y 20
#define  level_five_size lvl_five_x

short lvl_five[lvl_five_y][lvl_five_x] = {
	{ 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 7, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 6, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 6, 0, 3, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 1, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 0, 1 },
	{ 1, 0, 0, 2, 1, 1, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 5, 8, 2, 1 },
	{ 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 2 ,0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};


////////////////
// Level six
////////////////
#define lvl_six_x 27
#define lvl_six_y 20
#define level_six_size lvl_six_x

short lvl_six[lvl_six_y][lvl_six_x] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 2, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1 },
	{ 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 },
	{ 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 6 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 7, 0, 0, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 7, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 2, 1, 1, 1, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 1, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 2, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6, 1, 1, 1 }
};


////////////////
// Level win
////////////////
#define lvl_win_x 27
#define lvl_win_y 20
#define level_win_size lvl_win_x

short lvl_win[lvl_win_y][lvl_win_x] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
	{ 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
	{ 1, 2, 2, 1, 2, 2, 1, 2, 2, 1, 1, 2, 2, 1, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
	{ 1, 2, 2, 1, 2, 2, 1, 2, 1, 0, 0, 1, 2, 1, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
	{ 1, 2, 2, 1, 2, 2, 1, 2, 1, 0, 0, 1, 2, 1, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
	{ 1, 2, 2, 1, 2, 2, 1, 2, 1, 0, 0, 1, 2, 1, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
	{ 1, 2, 2, 1, 1, 1, 1, 2, 2, 1, 1, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
	{ 1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
	{ 1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
	{ 1, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
	{ 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2, 2, 2, 2, 1 },
	{ 1, 2, 2, 1, 2, 2, 2, 2, 1, 2, 1, 2, 1, 2, 2, 2, 1, 1, 2, 1, 2, 1, 2, 2, 2, 2, 1 },
	{ 1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 2, 1, 2, 2, 2, 2, 1 },
	{ 1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 },
	{ 1, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 1, 1, 2, 1, 2, 1, 2, 2, 1, 2, 1, 2, 2, 2, 2, 1 },
	{ 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
	{ 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 ,2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
	{ 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};


//////////////////
//  COLORSHEME
//////////////////
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
	init_pair(c_enemy,  COLOR_RED,      COLOR_BLACK);
	init_pair(c_box,    COLOR_YELLOW,   COLOR_BLACK);
}

// Draw colored instance
#define td_indent 2 // Top & down ident
#define symbol_count 3

void draw_instance(int y, int x, int color, char name[]) {
	attron(COLOR_PAIR(color));

	// Win offset
	int win_xoffset = ceil(w/2);
	int win_yoffset = ceil(h/2);
	
	// Level offset
	int lvl_xoffset = ceil((current_lvl_x/2)*symbol_count)+2;
	int lvl_yoffset = ceil((current_lvl_y+(td_indent*2))/2)-1 /* +1 indent hud */;

	mvprintw(
		/* Y pos */ (win_yoffset - lvl_yoffset) + (y+td_indent), 
		/* X pos */ (win_xoffset - lvl_xoffset) + (x*symbol_count), 
		/* S pos */ name
	);
	attroff(COLOR_PAIR(color));
}

//////////////
// OBJECT 
//////////////
// Class
struct class_obj {
	char symbol[20];
	int hsp;
	int vsp;
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
		if (enemy[index].direction == 1 || enemy[index].direction == -1)  {
			// VSP
			if (current_lvl[enemy[index].y + enemy[index].vsp][enemy[index].x] == i_wall || 
				current_lvl[enemy[index].y + enemy[index].vsp][enemy[index].x] == i_door || 
				current_lvl[enemy[index].y + enemy[index].vsp][enemy[index].x] == i_box)
			{
				enemy[index].direction *= -1;
			}
			
			enemy[index].vsp = 1 * enemy[index].direction;
			enemy[index].y += enemy[index].vsp;
			
			return;
		}

		if (enemy[index].direction == 2 || enemy[index].direction == -2){
		 	// HSP
			if (current_lvl[enemy[index].y][enemy[index].x + enemy[index].hsp] == i_wall || 
				current_lvl[enemy[index].y][enemy[index].x + enemy[index].hsp] == i_door || 
				current_lvl[enemy[index].y][enemy[index].x + enemy[index].hsp] == i_box)
			{
				enemy[index].direction *= -1;
			}

			enemy[index].hsp = 1 * enemy[index].direction;
			enemy[index].x += enemy[index].hsp;

			return;
		}
}

// Enemy update
void enemy_update(short current_lvl[][arr_size_x]) {
	for (int i = 0; i < sizeof(enemy)/sizeof(enemy[0]); i++) {
		enemy_move(current_lvl, i);
	}
}

// Enemy clear
void clear_enemy() {
	for (int i = 0; i < sizeof(enemy)/sizeof(enemy[0]); i++) {
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

/////////////
// PLAYER
////////////
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
		if ( dir_x ==  1 ) { dir_shoot =  1; strcpy(player.symbol, "|0>"  ); }
		if ( dir_x == -1 ) { dir_shoot = -1; strcpy(player.symbol, "<0|"  ); }
		if ( dir_y == -1 ) { dir_shoot = -2; strcpy(player.symbol, "/0\\" ); }
		if ( dir_y ==  1 ) { dir_shoot =  2; strcpy(player.symbol, "\\0/" ); }
	}

	player.hsp = 1 * dir_x;
	player.vsp = 1 * dir_y;

	if (player.hsp != 0) {
		player.vsp = 0;
	} else if (player.vsp != 0) {
		player.hsp = 0;
	}

	player.x += player.hsp;
	player.y += player.vsp;
}

// Collsiion
void player_collision(short current_lvl[][arr_size_x]) {
	switch(current_lvl[player.y][player.x]) {
		
		// Collision
		case i_wall: 	// wall
		case i_box:  	// box
		case i_door: 	// door
		case i_space: 	// space
			player.x -= player.hsp;
			player.y -= player.vsp;
		break;

		// Apple collision
		case i_apple:
			current_lvl[player.y][player.x] = 0;
			score = score + 1;
		break;

		// key
		case i_life:
			current_lvl[player.y][player.x] = 0;
			lifes = lifes + 1;
		break;
	}

	// Enemy collision
	for (short i = 0; i < sizeof(enemy)/sizeof(enemy[0]); i++) {
		if (player.y == enemy[i].y &&
			player.x == enemy[i].x)
		{
			lifes = lifes - 1; 
		}
	}

}


/////////////
// BULLET
////////////
void bullet_collision(short current_lvl[][arr_size_x]) {
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
	if (bullet_shoot) {
		for (int i = 0; i < sizeof(enemy)/sizeof(enemy[0]); i++) {
			// Vertival collision
			if (enemy[i].vsp != 0) {
				if (bullet.y == enemy[i].y &&
				    bullet.x == enemy[i].x || 
				    bullet.y - enemy[i].direction == enemy[i].y &&
				    bullet.x == enemy[i].x)
				{
					enemy[i].y = 0;
					enemy[i].x = 0;
					enemy[i].direction = 0;
					bullet_shoot = false;
					break;
				}
			}

			// Horizontal collision
			if (enemy[i].hsp != 0) {
				if (bullet.y == enemy[i].y &&
				    bullet.x == enemy[i].x || 
				    bullet.y == enemy[i].y &&
				    bullet.x - enemy[i].direction == enemy[i].x)
				{
					enemy[i].y = 0;
					enemy[i].x = 0;
					enemy[i].direction = 0;
					bullet_shoot = false;
					break;
				}
			}
		}
	}

}


/////////////
// LEVELS
////////////
// Set enemy and calck apple
void set_lvl_param(short current_lvl[][arr_size_x], int clx, int cly) {
	static int i = 0;
	for (int y = 0; y < cly; y++) {
		for (int x = 0; x < clx; x++) {
			if (current_lvl[y][x] == i_apple) {
				apples_in_level = apples_in_level + 1;
			}

			if (current_lvl[y][x] == i_enemy_v) {
				obj_init(&enemy[i], x, y, 1, "");
				i++;
			} else if (current_lvl[y][x] == i_enemy_h) {
				obj_init(&enemy[i], x, y, 2, "");
				i++;
			}

			if (i >= sizeof(enemy)/sizeof(enemy[0])) {
				i = 0;
			}
		}
	}

}


// Check next lvl
bool next_lvl(short current_lvl[][arr_size_x]) {
	if (current_lvl[player.y][player.x] == i_exit) {
		score = 0;
		apples_in_level = 0;
		level = level + 1;
		return true;
	}

	return false;
}

// Draw Current Level
void draw_level(short lvl[][arr_size_x]) {
	for (int y = 0; y < current_lvl_y; y++) {
		for (int x = 0; x < current_lvl_x; x++) {
			switch(lvl[y][x]) {

				// Draw static object
				case i_wall:   draw_instance(y, x, c_wall,  s_wall);  break;
				case i_box:    draw_instance(y, x, c_box,   s_box);   break;
				case i_apple:  draw_instance(y, x, c_apple, s_apple); break;
				case i_door:   draw_instance(y, x, c_door,  s_door);  break;
				case i_space:  draw_instance(y, x, c_wall,  s_space); break;
				case i_life:   draw_instance(y, x, c_life,  s_life);  break;
				case i_exit:   draw_instance(y, x, c_life,  s_exit);  break;

				// Draw dynamic object
				default:

					// Draw player
					if (x == player.x && y == player.y) {
						draw_instance(y, x, c_player, player.symbol);
						break;
					}

					// Draw bullet
					if (x == bullet.x && y == bullet.y) {
						if (!bullet_shoot) {
							break;
						}
						draw_instance(y, x, c_bullet, bullet.symbol);
					}

					// Draw enemy
					for (int i = 0; i < 5; i++) {
						if (x == enemy[i].x && y == enemy[i].y) {
							draw_instance(y, x, c_enemy, s_enemy);
							break;
						}
					}

				break;
			}

			// Open door
			if (score == apples_in_level) {
				if (lvl[y][x] == i_door) {
					lvl[y][x] = 0;
				}
			}
		}
	}
}

//////////////
// GAME
/////////////

// Hud
void draw_hud() {
	if (score == 0) {
		mvprintw(1, 2, "apples: %d%%   lifes: %d   level: %d\n", score, lifes, level);
		return;
	}

	mvprintw(1, 2, "apples: %d%%   lifes: %d   level: %d\n", ((score * 100) / apples_in_level), lifes, level);
}

// Game Over
void game_over() {
	EXIT = true;
	endwin();
    printf("Game Over!\n");
}

void bullet_update(void) {
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
			case 1:
				bullet.hsp = 1;
				bullet.vsp = 0;
			break;

			case -1:
				bullet.hsp = -1;
				bullet.vsp = 0;
			break;

			case 2:
				bullet.hsp = 0;
				bullet.vsp = 1;
			break;

			case -2:
				bullet.hsp = 0;
				bullet.vsp = -1;
			break;
		}

		bullet.x += bullet.hsp;
		bullet.y += bullet.vsp;
	}
}

// Update game
void game_update(int key, short current_lvl[][arr_size_x]) {
	// Player
	player_move(key);
	player_collision(current_lvl);

	// Enemy
	enemy_update(current_lvl);

	// Bullet
	bullet_update();
	bullet_collision(current_lvl);

	// Draw map
	draw_level(current_lvl);

	// Over
	if (lifes <= 0)
		game_over();
}

// Init lvl
void level_init(short index_lvl) {
	static bool init = true;

	if (!init) {
		if (index_lvl == 1) { init = next_lvl(lvl_one);   game_update(key_pressed, lvl_one);   }
		if (index_lvl == 2) { init = next_lvl(lvl_two);   game_update(key_pressed, lvl_two);   }
		if (index_lvl == 3) { init = next_lvl(lvl_three); game_update(key_pressed, lvl_three); }
		if (index_lvl == 4) { init = next_lvl(lvl_fo);    game_update(key_pressed, lvl_fo);    }
		if (index_lvl == 5) { init = next_lvl(lvl_five);  game_update(key_pressed, lvl_five);  }
		if (index_lvl == 6) { init = next_lvl(lvl_six);   game_update(key_pressed, lvl_six);   }
		if (index_lvl == 7) { init = next_lvl(lvl_win);   game_update(key_pressed, lvl_win);   }
		
		return;
	}

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



///////////////
// MAIN
//////////////
int main(void) {

	////////////////////
	// Enum game state
	///////////////////
	typedef enum {
		STATE_MENU,
		STATE_INFO,
		STATE_GAME,
		STATE_EXIT,
	} game_states;

	// Init current state
	game_states current_state;
	current_state = STATE_MENU;


	//////////////
	// init obj
	//////////////
	// Player
	obj_init(&player, 5 /* x pos */, 5 /* y pos */, 0, "|O|");

	// Bullet
	obj_init(&bullet, player.x, player.x, 0, " * ");

	// Start curses mode
	initscr();
	keypad(stdscr, TRUE);
	savetty();
    cbreak();
    noecho();
    timeout(0);
    leaveok(stdscr, TRUE);
    curs_set(0);

	// if not support color
	if (!has_colors()) {
        endwin();
        printf("Your terminal does not support color\n");
    }

    ////////////////
    // Main loop
    ///////////////

	// Menu item
	// Item start game
	const char *item_start_game[2] = {
		"> START GAME <",
		"start game",
	};

	// Item info
	const char *item_info[2] = {
		"> INFO <",
		"info",
	};

	// Item exit
	const char *item_exit[2] = {
		"> EXIT <",
		"exit",
	};

	while (!EXIT) {

		// Color
		SetColor();

		// Get window width & Height
		getmaxyx(stdscr, h, w);

		// Menu state
		static int menu_item = 0;
		if (key_pressed == KEY_UP)   menu_item--;
		if (key_pressed == KEY_DOWN) menu_item++;

		if (menu_item >= 2) menu_item = 2;
		if (menu_item <= 0) menu_item = 0;

		// In menu state
		switch(current_state) {
			// Menu
			case STATE_MENU:
				// Logo
				draw_logo(h, w);

				///////////
				// Items
				//////////
				// Item start game
				int select_start_game = menu_item == 0 ? 0 : 1;
				mvprintw(h/2 - logo_h_size + 9, w/2 - str_len(item_start_game[select_start_game])/2, item_start_game[select_start_game]);

				// Item info
				int select_info = menu_item == 1 ? 0 : 1;
				mvprintw(h/2 - logo_h_size + 11, w/2 - str_len(item_info[select_info])/2, item_info[select_info]);

				// Item exit
				int select_exit = menu_item == 2 ? 0 : 1;
				mvprintw(h/2 - logo_h_size + 13, w/2 - str_len(item_exit[select_exit])/2, item_exit[select_exit]);

				// By dev
				mvprintw(h-2, 2, "Develop: uriid1");

				// Draw box
				attron(COLOR_PAIR(c_hud));
				box(stdscr, 0, 0);
				attron(COLOR_PAIR(c_hud));

				// Click handler
				if (key_pressed == vk_enter) { 
					switch(menu_item) {
						case 0:
							current_state = STATE_GAME;
						break;

						case 1:
							// Info page is dev
							// current_state = STATE_INFO;
						break;

						case 2:
							current_state = STATE_EXIT;
						break;
					}
				}
			break;

			//
			case STATE_INFO:
				// In dev
			break;

			//
			case STATE_GAME:
				level_init(level);
				draw_hud();
				box(stdscr, 0, 0);
			break;

			//
			case STATE_EXIT:
				endwin();
				EXIT = TRUE;
			break;
		}

		// Exit to menu
		if (key_pressed == 'q')
			current_state = STATE_MENU;

		// Get key pressed
		key_pressed = wgetch(stdscr);
		napms(100);
		key_pressed = wgetch(stdscr);

		// Clear
		erase();

	}

	// End curses mode
	endwin();

	return 0;
}
