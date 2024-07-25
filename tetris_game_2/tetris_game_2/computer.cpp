
#include "computer.h"
#include "general.h"

#include <iostream>
#include <Windows.h>

using namespace std;

//Find the best position for the shape for computer player
void computer::find_best_Pos_for_shape()
{
	int best_score = 0;
	int score;

	for (int col = 0; col < GameConfig::GAME_WIDTH; col++)
	{
		for (int row = 0; row < GameConfig::GAME_HEIGHT; row++)
		{
			for (int rotation = 0; rotation < 4; rotation++)
			{
				score = 0;
				if (can_place_tetromino(row, col))
				{
					if (pos_can_Move_Down(row, col))
						score = evaluate_Score(row, col);
				}

				if (best_score < score)
				{
					best_score = score;
					best_pos_x = col;
					best_pos_y = row;
					best_rotate = rotation;
				}
				rotate_ClockWise();
			}
		}
	}
	for (int i = 0; i < best_rotate; i++)
	{
		rotate_ClockWise();
	}
}

//Checks if the shape can move down
bool computer::pos_can_Move_Down(int row, int col)
{

	for (int j = 0; j < GameConfig::BLOCK_SIZE_HEIGHT; j++)
	{
		for (int k = 0; k < GameConfig::BLOCK_SIZE_WIDTH; k++)
		{
			if (shape[j][k] == '*')
			{
				for (int i = row; i > 0; i--)
				{
					if (Game_Board[i + j][col + k] == '*')
						return false;
				}
			}
		}
	}
	return true;
}

//Checks if the place for the shape is valid
bool computer::can_place_tetromino(int row, int col)
{
	for (int i = 0; i < GameConfig::BLOCK_SIZE_HEIGHT; i++)
	{
		for (int j = 0; j < GameConfig::BLOCK_SIZE_WIDTH; j++)
		{
			if ((shape[i][j] == '*') && ((Game_Board[i + row][j + col] == '*') || (Game_Board[i + row][j + col] == '#')
				|| ((j + col) >= GameConfig::GAME_WIDTH) || ((i + row) >= GameConfig::GAME_HEIGHT)
				|| ((j + col) <= 0) || ((i + row) <= 0)))

				return false;
		}
	}
	return true;
}

//Evaluate score for best position of the shape
int computer::evaluate_Score(int row, int col)
{
	int score = 0;
	int rows_cleared = 0;
	char tmpBoard[GameConfig::GAME_HEIGHT][GameConfig::GAME_WIDTH];
	memcpy(tmpBoard, Game_Board, (GameConfig::GAME_HEIGHT * GameConfig::GAME_WIDTH));

	for (int i = 0; i < GameConfig::BLOCK_SIZE_HEIGHT; i++) {
		for (int j = 0; j < GameConfig::BLOCK_SIZE_WIDTH; j++)
		{
			if ((shape[i][j] == '*'))
				tmpBoard[row + i][col + j] = '*';
		}
	}

	int max_height = 0;
	int num_holes = 0;
	int count = 0;
	int height = 0;
	for (int i = 1; i < GameConfig::GAME_HEIGHT; i++)
	{
		count = 0;
		for (int j = 1; j < GameConfig::GAME_WIDTH; j++)
		{

			if (tmpBoard[i][j] == '*')
			{
				height = GameConfig::GAME_HEIGHT - i;
				if (max_height < height)
					max_height = height;
				count++;
				score += ((i * 12) * count);
			}
			else if (tmpBoard[i][j] == ' ')
			{
				if (count > 0)
					num_holes++;
				count = 0;
			}
		}
	}
	score -= (max_height * 100);
	score -= (num_holes * 10);

	for (int i = 1; i < GameConfig::GAME_HEIGHT; i++)
	{
		bool row_complete = true;
		for (int j = 1; j < GameConfig::GAME_WIDTH; j++)
		{
			if (tmpBoard[i][j] != '*')
			{
				row_complete = false;
				break;
			}
		}
		if (row_complete)
			rows_cleared++;
	}
	score += (rows_cleared * 100000);

	switch (difficulty)
	{
	case GameConfig::NOVICE:
	{
		if (rand() % 10 == 0)
			score -= 100000;
		break;
	}
	case GameConfig::GOOD:
	{
		if (rand() % 40 == 0)
			score -= 100000;
		break;
	}
	case GameConfig::BEST:
	{
		break;
	}
	}

	return score;

}

//Finds the best col for a shape for computer player
void computer::best_col()
{
	if ((best_pos_x < (x - (game_Start_Point_x - 1))) && (!Collide_With_Board()) && (can_Move_Left()))
	{
		move_left();
	}
	else if ((best_pos_x > (x - (game_Start_Point_x - 1))) && (!Collide_With_Board()) && (can_Move_Right()))
	{
		move_right();
	}
}

//Find the best position for the bomb for computer player
void computer::find_best_Pos_for_bomb()
{
	int best_explode = 0;
	int count = 0;
	for (int col = 1; col < GameConfig::GAME_WIDTH - 1; col++)
	{

		for (int row = 1; row < GameConfig::GAME_HEIGHT - 1; row++)
		{
			if (Game_Board[row + 1][col] == '*')
			{
				count = 0;
				count = countstars(row + 1, col);
				if (count > best_explode)
				{
					best_explode = count;
					best_pos_x = col;
					best_pos_y = row;
				}
				break;
			}
		}
	}
	box_score += best_explode;
}

//Counts the number of asterisks that the bomb erase
int computer::countstars(int row, int col)
{
	int count = 0;
	for (int i = row - 4; i < row + 5; i++)
	{
		for (int j = col - 4; j < col + 5; j++)
		{
			if ((i < (GameConfig::GAME_HEIGHT - 1)) && (i > 0) && (j > 0) && (j < GameConfig::GAME_WIDTH))
			{
				if (Game_Board[i][j] == '*')
					count++;
			}
		}
	}
	return count;
}