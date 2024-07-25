#pragma once

#ifndef __HUMAN_H
#define __HUMAN_H

#include "Game_Config.h"

#include "player.h"



class human : public player
{
	char keys_For_Play[10]; // Array to get player keys

public:

	human(const char* player_Keys); //getting the players keys for the game
	virtual bool is_Key_Valid(int key); // Flag that checks if the key valid for the current player
	virtual void move(int key); //moving the current shape on board


	//computer functions
	void set_difficulty(int num) {}  //Set the difficulty for the computer player
    bool pos_can_Move_Down(int row, int col)  override { return false; } //Checks if the shape can move down
    void find_best_Pos_for_shape()  override {} //Find the best position for the shape for computer player
	bool can_place_tetromino(int row, int col)  override { return false; }//Checks if the place for the shape is valid
	int evaluate_Score(int row, int col)  override { return 0; } //Evaluate score for best position of the shape
	void best_col() override {} //Finds the best col for a shape for computer player 
    void find_best_Pos_for_bomb() {} //Find the best position for the bomb for computer player
};

#endif // !__HUMAN_H

