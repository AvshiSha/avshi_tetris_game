#include "human.h"
#include "general.h"
#include "Game_Config.h"
#include "player.h"
#include <iostream>
#include <stdlib.h> //for rand
#include <time.h> //for time
#include <Windows.h>


using namespace std;


//human constructor- getting the players keys for the game
human::human(const char* player_Keys)
{
	for (int i = 0; i < GameConfig::NUM_OF_KEYS; i++)
	{
		keys_For_Play[i] = player_Keys[i];
	}
}

//Flag that checks if the key valid for the current player
bool human::is_Key_Valid(int key)
{
	for (int i = 0; i < GameConfig::NUM_OF_KEYS; i++)
	{
		if (keys_For_Play[i] == (char)key)
			return true;
	}

	return false;
}

//moving the current shape on board
//checks which key pressed, and checks if the movement of the tetromino is valid in the game
void human::move(int key)
{
	if ((key == keys_For_Play[0]) || (key == keys_For_Play[1]))//moving left
	{
		if (can_Move_Left() && !Collide_With_Board())
			move_left();
	}
	else if ((key == keys_For_Play[2]) || (key == keys_For_Play[3]))//moving right
	{
		if (can_Move_Right() && !Collide_With_Board())
			move_right();
	}
	else if ((key == keys_For_Play[4]) || (key == keys_For_Play[5]))//rotate clockwise
	{
		if (!Collide_With_Board() && !is_Square())
			rotate_ClockWise();
	}
	else if ((key == keys_For_Play[6]) || (key == keys_For_Play[7]))//rotate counter clockwise 
	{
		if (!Collide_With_Board() && !is_Square())
			rotate_Counter_ClockWise();
	}
	else if ((key == keys_For_Play[8]) || (key == keys_For_Play[9]))//drop 
	{
		if (can_Move_Down() && !Collide_With_Board())
			move_Down();

	}
}

