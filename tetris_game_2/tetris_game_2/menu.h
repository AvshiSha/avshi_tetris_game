#pragma once

#include "player.h"
class menu
{

public:

	void get_Menu(); // the menu of the tetris game
	void instructions_and_keys(); //shows the instructions and keys of the game
	bool game(player* p1, player* p2); // the game
	void start_Game(player* comp1, player* comp2, bool add_colors); //initialize the start of the game
	int  choose_level(); //choose best, good or novice for computer player
	bool game_with_color();
};

