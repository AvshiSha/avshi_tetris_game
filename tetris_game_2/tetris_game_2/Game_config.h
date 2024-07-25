#pragma once
#ifndef __GAME_CONFIG_H
#define __GAME_CONFIG_H
class GameConfig
{
public:

	//keys for our menu
	static constexpr char HUMAN_VS_HUMAN = '1';
	static constexpr char HUMAN_VS_COMPUTER = '2';
	static constexpr char COMPUTER_VS_COMPUTER = '3';
	static constexpr char RESUME_GAME = '4';
	static constexpr char START_GAME_WITH_COLORS = '1';
	static constexpr char START_GAME_WITHOUT_COLORS = '2';
	static constexpr char INSTRUCTIONS_AND_KEYS = '8';
	static constexpr char EXIT_GAME = '9';

	//difficulty
	static constexpr char NOVICE = '1';
	static constexpr char GOOD = '2';
	static constexpr char BEST = '3';

	//escape key
	static constexpr int ESCAPE = 27;

	static constexpr int NUM_OF_KEYS = 10;
	//left player keys for the game
	static constexpr char Keys_Left[10] = { 'A','a','D','d','S','s','W','w','X','x' };
	//right player keys for the game
	static constexpr char Keys_Right[10] = { 'J','j','L','l','K','k','I','i','M','m' };

	//board size
	static constexpr int GAME_WIDTH = 12;
	static constexpr int GAME_HEIGHT = 18;

	//player right starting point
	static constexpr int MIX_X_RIGHT = 50;
	static constexpr int MIX_Y_RIGHT = 0;

	//player left starting point
	static constexpr int MIN_X_LEFT = 0;
	static constexpr int MIX_Y_LEFT = 0;

	//block size
	static constexpr int BLOCK_SIZE = 4;
	static constexpr int BLOCK_SIZE_HEIGHT = 4;
	static constexpr int BLOCK_SIZE_WIDTH = 4;

	//all the shapes of tetris game
	static constexpr char Square_shape[4][4] = {      {'*','*',' ',' '},
													  {'*','*',' ',' '},
													  {' ',' ',' ',' '},
													  {' ',' ',' ',' '} };


	static constexpr char L_shape[4][4] = {          {'*',' ',' ',' '},
													 {'*',' ',' ',' '},
													 {'*','*',' ',' '},
													 {' ',' ',' ',' '} };


	static constexpr char J_shape[4][4] = {          {' ','*',' ',' '},
													 {' ','*',' ',' '},
													 {'*','*',' ',' '},
													 {' ',' ',' ',' '} };

	static constexpr char I_shape[4][4] = {          {'*','*','*','*'},
													 {' ',' ',' ',' '},
													 {' ',' ',' ',' '},
													 {' ',' ',' ',' '} };

	static constexpr char Z_shape[4][4] = {          {'*','*',' ',' '},
													 {' ','*','*',' '},
													 {' ',' ',' ',' '},
													 {' ',' ',' ',' '} };


	static constexpr char S_shape[4][4] = {          {' ','*','*',' '},
													 {'*','*',' ',' '},
													 {' ',' ',' ',' '},
													 {' ',' ',' ',' '} };



	static constexpr char T_shape[4][4] = {          {'*','*','*',' '},
													 {' ','*',' ',' '},
													 {' ',' ',' ',' '},
													 {' ',' ',' ',' '} };


	 
	static constexpr char clear_shape[4][4] = {      {' ',' ',' ',' '},
													 {' ',' ',' ',' '},
													 {' ',' ',' ',' '},
													 {' ',' ',' ',' '} };

	static constexpr char bomb[4][4] = {             {'@',' ',' ',' '},
													 {' ',' ',' ',' '},
													 {' ',' ',' ',' '},
													 {' ',' ',' ',' '} };

};

#endif // !__GAME_CONFIG_H

