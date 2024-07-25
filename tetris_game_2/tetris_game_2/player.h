
#pragma once

#include "Game_Config.h"



class player
{
protected:
	int x = 1; //x-coordinate of the current position
	int y = 1; //y-coordinate of the current position
	char(*shape)[4] = nullptr;  //Pointer to a 2D array representing the current shape
	int shape_color = 1; //Color of the current shape
	bool add_colors = 1; //Flag indicating whether to add colors
	char Game_Board[GameConfig::GAME_HEIGHT][GameConfig::GAME_WIDTH] = {};   //2D array representing the game board
	int Game_Board_colors[GameConfig::GAME_HEIGHT][GameConfig::GAME_WIDTH] = {};  //2D array representing the colors on the game board
	int game_Start_Point_x = 1; //Initial x-coordinate for the game
	int game_Start_Point_y = 1; //Initial y-coordinate for the game
	int box_score = 0;

	bool bomb = false; // Flag for if there is a bomb
	int bomb_x; //x coordinate of the bomb
	int bomb_y; //y coordinate of the bomb
	int range_x = 9; //The range width of the explotion
	int range_y = 9; //The range height of the explotion
public:

	bool check_if_bomb() const { return bomb; } //Checks if the new shape is a bomb
	bool is_bomb_turn(); // The random for a bomb shape turn
	void bomb_explode(); //Remove and arange the board after the explotion of the bomb
	void bomb_range(); // checks the range for the explotion of the bomb



	void box_Score() const; //display the current score
	void set_box_Score() { box_score = 0; } //set the box score
	int check_score() const { return box_score; } //check the current box score


	void set_colors(bool add_colors) { this->add_colors = add_colors; } //Flag to whether add colors to the game
	void draw_tetris_Game(int x, int y); //drawing the board of the game, the box score, and initialize the starting point of the board
	void print_current_board() const; //Print the current state of the game board
	void print_Block_To_Board(); //printing the current shape on the game board
	void draw() const;//drawing the Tetris shape to board
	void clear_Block() const; //clearing block from current board

	void get_Shape(); //getting the next Tetris shape
	void get_shape_color(); //get the color of the current shape
	void set_Shape(); //setting the current Tetris shape

	void init(int x, int y); //initialize the starting point of the new shape
	bool Collide_With_Board() const; //check if the current shape is not collide with the board
	bool is_Square() const; // checks if the current shape is square
	//flag for checking if a player can move on the board
	bool can_Move_Left() const;
	bool can_Move_Right() const;
	bool can_Move_Down() const;
	//if the player can move, then move to the current position
	void move_right() { x++; }
	void move_left() { x--; }
	void move_Down() { y++; }

	bool is_Collide_After_Rotate(char(*rotate)[4]) const; //checks if the current shape after rotate is collide with board
	void rotate_ClockWise(); //rotating the current shape clockwise
	void rotate_Counter_ClockWise(); //rotating the current shape counter clockwise

	bool row_Of_Astrisks(); //checking if a row is completely filled with asterisks
	void remove_Row(); // remove a filled row from the game board

	bool is_Game_Over() const; //Flag for checking if the game is over

	bool start_point() const; //Check if the shape is in the start point
	
	virtual bool is_Key_Valid(int key) = 0; // Flag that checks if the key valid for the current human player
	virtual void move(int key) = 0; //moving the current shape on board


	
	virtual void find_best_Pos_for_bomb() = 0; //Find the best position for the bomb for computer player
	virtual void set_difficulty(int num) { int difficulty = num; } //Set the difficulty for the computer player
	virtual bool pos_can_Move_Down(int row, int col) = 0; //Checks if the shape can move down
	virtual void find_best_Pos_for_shape() = 0; //Find the best position for the shape for computer player
	virtual bool can_place_tetromino(int row, int col) = 0; //Checks if the place for the shape is valid
	virtual int evaluate_Score(int row, int col) = 0; //Evaluate score for best position of the shape
	virtual void best_col() = 0; //Finds the best col for a shape for computer player
};


