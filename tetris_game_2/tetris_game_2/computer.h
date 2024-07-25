#pragma once

#include "player.h"
class computer : public player
{
	int best_pos_x; //Best x coordinate for the shape
	int best_pos_y; //Best y coordinate for the shape
	int best_rotate; //Best rotation for the shape
	char difficulty; //Best\good\novice choice

public:

	virtual void set_difficulty(int num)  { difficulty = num; } //Set the difficulty for the computer player
	virtual bool pos_can_Move_Down(int row, int col);  //Checks if the shape can move down
	virtual void find_best_Pos_for_shape(); //Find the best position for the shape for computer player
	virtual bool can_place_tetromino(int row, int col) ; //Checks if the place for the shape is valid
	virtual int evaluate_Score(int row, int col) ; //Evaluate score for best position of the shape
	virtual void best_col(); //Finds the best col for a shape for computer player 
	virtual void find_best_Pos_for_bomb(); //Find the best position for the bomb for computer player
	virtual int countstars(int row, int col); //Counts the number of asterisks that the bomb erase

	//human functions
	bool is_Key_Valid(int key) override { return 0; } // Flag that checks if the key valid for the current player
	void move(int key) {} //moving the current shape on board

};

