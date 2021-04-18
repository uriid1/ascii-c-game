#include <stdio.h>
#include <string.h>
#include <ncurses.h>

// Const
#define nil -1

// Key Kode
#define vk_left   68
#define vk_right  67
#define vk_up     65
#define vk_down   66
#define vk_space  32
#define vk_enter  10

// Map
#define wall  "###"
#define apple " @ "
#define empty "   "
#define door  "^^^"

// Game Global var
int level 	 = 1;
int score    = 0;
int game_key = 0;
int bullet_shoot = false;

//////// LEVELS
// Lvl 1
#define lvl_one_x 27
#define lvl_one_y 20
short lvl_one[lvl_one_y][lvl_one_x] = {
	// Level one
	{ 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 6, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 6, 1, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 6, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 6, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 1 },
	{ 6, 1, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 6, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 6, 1, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 6, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 6, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 1 },
	{ 6, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 6, 1, 0, 0, 0, 0, 1, 5, 5, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 6, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 6, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 6, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 6, 1, 0, 3, 0, 0, 1, 0, 7, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 6, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 6, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 1 },
	{ 6, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 6, 1, 1, 1, 1, 1, 1, 6, 6, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	//
};

// Lvl 2
#define lvl_two_x 7
#define lvl_two_y 9
short lvl_two[lvl_two_y][lvl_two_x] = {
	// Level two
	{ 6, 1, 1, 1, 1, 1, 1 },
	{ 6, 1, 0, 0, 0, 0, 1 },
	{ 6, 1, 0, 0, 0, 0, 1 },
	{ 6, 1, 0, 0, 0, 0, 1 },
	{ 6, 1, 0, 0, 0, 0, 1 },
	{ 6, 1, 0, 0, 0, 0, 1 },
	{ 6, 1, 0, 0, 0, 0, 1 },
	{ 6, 1, 0, 0, 0, 0, 1 },
	{ 6, 1, 1, 1, 1, 1, 1 }
	//
};

// Get apples from start level
void calc_apple() {
	for (int y = 0; y < lvl_one_y; y++) {
		for (int x = 0; x < lvl_one_x; x++) {
			if (lvl_one[y][x] == 3) {
				score = score + 1;
			}
		}
	}
}

// Open door event
void open_door() {
	if (score == 0) {
		for (int y = 0; y < lvl_one_y; y++) {
			for (int x = 0; x < lvl_one_x; x++) {
				if (lvl_one[y][x] == 5) {
					lvl_one[y][x] = 0;
				}
			}
		}
	}
}

// Class
struct obj {
	char symbol[20];
	int x;
	int y;
	int direction;
};

// Create objects
struct obj player={};
struct obj bullet={};

// Playes method move
int dir_x;
int dir_y;
int dir_shoot;
void player_move(int key) {

	// Key check
	int key_left  = (key == vk_left)  ? 1 : 0;
	int key_right = (key == vk_right) ? 1 : 0;
	int key_down  = (key == vk_down)  ? 1 : 0;
	int key_up    = (key == vk_up)    ? 1 : 0;

	dir_x = key_right - key_left;
	dir_y = key_down  - key_up;


	// Animation and direction shoot
	if (dir_x == 0 && dir_y == 0) {
		strcpy(player.symbol, "|0|");
	} else {
		if (dir_x == 1)  { dir_shoot =  1; strcpy(player.symbol, "/0/");   }
		if (dir_x == -1) { dir_shoot = -1; strcpy(player.symbol, "\\0\\"); }
		if (dir_y == -1) { dir_shoot = -2; strcpy(player.symbol, "/0\\");  }
		if (dir_y == 1)  { dir_shoot =  2; strcpy(player.symbol, "\\0/");  }
	}

	player.x = player.x + dir_x;
	player.y = player.y + dir_y;
}

// Color
void SetColor() {
	start_color();
	init_pair(1, COLOR_BLACK,  COLOR_GREEN);	// Bullet
	init_pair(2, COLOR_WHITE,  COLOR_BLUE);		// Empty
	init_pair(3, COLOR_BLACK,  COLOR_YELLOW);	
	init_pair(4, COLOR_WHITE,  COLOR_MAGENTA);
	init_pair(5, COLOR_YELLOW, COLOR_BLACK); 	// Enemy
	init_pair(6, COLOR_BLACK,  COLOR_RED); 		// Door
	init_pair(7, COLOR_BLACK,  COLOR_BLACK); 	// Door
}


// Draw colored instance
void draw_instance(int color, char name[]) {
	attron(COLOR_PAIR(color));
	printw(name);
	attroff(COLOR_PAIR(color));
}


// Draw Current Level
int current_lvl_x = lvl_one_x;
int current_lvl_y = lvl_one_y;

int arr_size_x = 27;
void draw_level(short lvl[][arr_size_x]) {
	for (int y = 0; y < current_lvl_y; y++) {
		for (int x = 0; x < current_lvl_x; x++) {

			switch(lvl[y][x]) {
				case 1: draw_instance(2, wall);   break;
				case 3: draw_instance(3, apple);  break;
				case 5: draw_instance(5, door);   break;
				case 6: draw_instance(7, "   ");  break;
				case 7: draw_instance(1, "-->");  break;

				default: 
					// Draw dynamic
					if (x == player.x && y == player.y) {
						draw_instance(4, player.symbol);
					} else if (x == bullet.x && y == bullet.y) {
						if (bullet_shoot) {
							draw_instance(2, " ");
							draw_instance(1, bullet.symbol);
							draw_instance(2, " ");
						} else {
							draw_instance(2, empty);
						}
					} else {
						draw_instance(2, empty);
					}
				break;
			}

		}
		printw("\n");
	}
}

void game(int key, short current_lvl[][arr_size_x]) {

	player_move(key);

	// refresh();
	// printw("%d \n", KEY_UP);
	// endwin();
	
	{ // Player Collision
		if (current_lvl[player.y][player.x] == 1 || 
			current_lvl[player.y][player.x] == 5)
		{
			player.x = player.x - dir_x;
			player.y = player.y - dir_y;
		}

		// Eat apple
		if (current_lvl[player.y][player.x] == 3)
		{
			current_lvl[player.y][player.x] = 0;
			score = score - 1;
		}

		// Get key
		if (current_lvl[player.y][player.x] == 7)
		{
			current_lvl[player.y][player.x] = 0;
			game_key = game_key + 1;
		}
	}


	{ // Bullet collision
		if (current_lvl[bullet.y][bullet.x] == 1 ||
			current_lvl[bullet.y][bullet.x] == 5 ||
			current_lvl[bullet.y][bullet.x] == 6)
		{
			bullet_shoot = false;
		}
	}

	// Draw map
	open_door();

	draw_level(current_lvl);
}

int main(void) {

	calc_apple();

	// Playes
	strcpy(player.symbol, "|O|");
	player.x = 5;
	player.y = 5;

	// Bullet
	strcpy(bullet.symbol, "*");
	bullet.x = player.x;
	bullet.y = player.y;
	int bullet_direction;

	// Keykode check
	int key_pressed;

	// Start curses mode
	initscr();

	if (has_colors() == false) {
        endwin();
        printf("Your terminal does not support color\n");
        //exit(1);
    }

	// Print it on to the real screen
	// refresh();

	// Main loop
	do {
		SetColor();
		clear();

		printw("\n   apples: %d    key: %d    level: %d \n\n", score, game_key, level);

		// Main game loop
		game(key_pressed, lvl_one);

		// Shoot
		if (!bullet_shoot) {
				bullet.x = player.x;
				bullet.y = player.y;
			if (key_pressed == vk_space) {
				bullet_direction = dir_shoot;
				bullet_shoot = true;
			}
		} else {
			switch(bullet_direction) {
				case  1: bullet.x = bullet.x + 1; break;
				case -1: bullet.x = bullet.x - 1; break;
				case  2: bullet.y = bullet.y + 1; break;
				case -2: bullet.y = bullet.y - 1; break;
			}
		}

	} while ((key_pressed = getch()) != 'q');

	// End curses mode
	endwin();

	return 0;
}