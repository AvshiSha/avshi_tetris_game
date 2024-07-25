
#include "player.h"
#include "general.h"
#include "Game_Config.h"
#include <iostream>
#include <stdlib.h> //for rand
#include <time.h> //for time
#include <Windows.h>


using namespace std;

//Check if the shape is in the start point
bool player::start_point() const
{
	if (x == (game_Start_Point_x + (GameConfig::GAME_WIDTH / 2) - 2) && (y == game_Start_Point_y))
		return true;
	else
		return false;
}

// The random for a bomb shape turn
bool player::is_bomb_turn()
{
	if ((rand() % 20) == 0)
		bomb = true;
	else
		bomb = false;

	return bomb;
}

//Remove and arange the board after the explotion of the bomb
void player::bomb_explode()
{
	bomb_range();
	for (int i = bomb_y; i <= bomb_y + range_y; i++)
	{
		for (int j = bomb_x; j <= bomb_x + range_x; j++)
		{
			if (Game_Board[i][j] == '*')
			{
				Game_Board[i][j] = ' ';
				gotoxy(game_Start_Point_x + j - 1, game_Start_Point_y + i - 1);
				cout << Game_Board[i][j];
			}
		}
	}

	for (int i = GameConfig::GAME_HEIGHT - 2; i > 0; i--)
	{
		for (int j = 1; j < GameConfig::GAME_WIDTH - 1; j++)
		{
			if (Game_Board[i][j] == '*')
			{
				Game_Board[i][j] = ' ';
				gotoxy(game_Start_Point_x + j - 1, game_Start_Point_y + i - 1);
				cout << ' ';
				for (int k = i; k < GameConfig::GAME_HEIGHT - 1; k++)
				{
					if ((Game_Board[k + 1][j] == '#') || ((Game_Board[k + 1][j]) == '*'))
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Game_Board_colors[i][j]);
						Game_Board[k][j] = '*';
						gotoxy(game_Start_Point_x + j - 1, game_Start_Point_y + k - 1);
						cout << Game_Board[k][j];
						break;
					}
				}
			}
		}
	}
	range_x = 9;
	range_y = 9;
}

// checks the range for the explotion of the bomb
void player::bomb_range()
{
	for (int i = (x - game_Start_Point_x - 3); i < (x - game_Start_Point_x + 3); i++) //col
	{
		if ((i > 0) && (i < (GameConfig::GAME_WIDTH - 2)))
		{
			bomb_x = i;
			break;
		}
		range_x--;
	}
	if (range_x + bomb_x > GameConfig::GAME_WIDTH)
		range_x = GameConfig::GAME_WIDTH - 1 - bomb_x;
	for (int j = (y - game_Start_Point_y - 3); j < (y - game_Start_Point_y + 3); j++) //row
	{
		if ((j > 0) && (j < GameConfig::GAME_HEIGHT - 2))
		{
			bomb_y = j;
			break;
		}
		range_y--;
	}
	if (range_y + bomb_y > GameConfig::GAME_HEIGHT)
		range_y = GameConfig::GAME_HEIGHT - 1 - bomb_y;
}

//Print the current state of the game board
void player::print_current_board() const
{
	for (int row = 0; row < GameConfig::GAME_HEIGHT; row++)
	{
		for (int col = 0; col < GameConfig::GAME_WIDTH; col++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Game_Board_colors[row][col]);
			gotoxy(game_Start_Point_x + col - 1, game_Start_Point_y + row - 1);
			cout << Game_Board[row][col];
		}
	}

	//printing the current box score
	gotoxy(game_Start_Point_x - 1, GameConfig::GAME_HEIGHT + 2);
	if (game_Start_Point_x > GameConfig::GAME_WIDTH)
		cout << "Box score player R: ";
	else
		cout << "Box score player L: ";
}

//drawing the board of the game, the box score, and initialize the starting point of the board
//drawing borders on the top, bottom, left, and right sides of the game board.
void player::draw_tetris_Game(int x, int y)
{

	for (int col = 0; col < GameConfig::GAME_WIDTH; col++)
	{
		gotoxy(col + x - 1, 0);
		Game_Board[0][col] = '#';
		Game_Board_colors[0][col] = (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << Game_Board[0][col];

		gotoxy(col + x - 1, GameConfig::GAME_HEIGHT - 1);
		Game_Board[GameConfig::GAME_HEIGHT - 1][col] = '#';
		Game_Board_colors[GameConfig::GAME_HEIGHT - 1][col] = (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << Game_Board[GameConfig::GAME_HEIGHT - 1][col];
	}

	for (int row = 0; row < GameConfig::GAME_HEIGHT; row++)
	{
		gotoxy(x - 1, row);
		Game_Board[row][0] = '#';
		Game_Board_colors[row][0] = (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << Game_Board[row][0];

		gotoxy(x + GameConfig::GAME_WIDTH - 2, row);
		Game_Board[row][GameConfig::GAME_WIDTH - 1] = '#';
		Game_Board_colors[row][GameConfig::GAME_WIDTH - 1] = (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << Game_Board[row][GameConfig::GAME_WIDTH - 1];
	}

	// Initializing starting point coordinates for the game.
	game_Start_Point_x = x;
	game_Start_Point_y = y;

	// Clearing the interior of the game board for the Tetris shapes.
	for (int row = 1; row < GameConfig::GAME_HEIGHT - 1; row++)
	{
		for (int col = 1; col < GameConfig::GAME_WIDTH - 1; col++)
		{
			Game_Board[row][col] = ' ';
			Game_Board_colors[row][col] = (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
	}

	// printing the new box score
	gotoxy(x - 1, GameConfig::GAME_HEIGHT + 2);
	if (game_Start_Point_x > GameConfig::GAME_WIDTH)
		cout << "Box score player R: ";
	else
		cout << "Box score player L: ";




}

//initialize the starting point of the new shape
void player::init(int x, int y)
{
	this->x = x;
	this->y = y;
}

//setting the current Tetris shape
void player::set_Shape()
{
	if (shape != nullptr)
		delete[] shape;

	shape = nullptr;
}

//drawing the Tetris shape to board
void player::draw() const
{

	for (int i = 0; i < GameConfig::BLOCK_SIZE_HEIGHT; i++)
	{
		for (int j = 0; j < GameConfig::BLOCK_SIZE_WIDTH; j++)
		{
			if ((shape[i][j] == '*') || (shape[i][j] == '@'))
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), shape_color);
				gotoxy(x + j, y + i);
				cout << shape[i][j];
			}
		}
	}
}

//Check if the Tetris shape can move down
bool player::can_Move_Down() const
{
	if (y < GameConfig::GAME_HEIGHT)
		return true;
	else
		return false;
}

//Check if the Tetris shape can move left
bool player::can_Move_Left() const
{
	for (int i = 0; i < GameConfig::BLOCK_SIZE_HEIGHT; i++)
	{
		for (int j = 0; j < GameConfig::BLOCK_SIZE_WIDTH; j++)
		{
			if ((shape[i][j] == '*') || (shape[i][j] == '@'))
			{
				if ((x + j - 1) < game_Start_Point_x)
					return false;
			}
		}
	}
	return true;
}

//Check if the Tetris shape can move right
bool player::can_Move_Right() const
{
	for (int i = 0; i < GameConfig::BLOCK_SIZE_HEIGHT; i++)
	{
		for (int j = 0; j < GameConfig::BLOCK_SIZE_WIDTH; j++)
		{
			if ((shape[i][j] == '*') || (shape[i][j] == '@'))
			{
				if ((x + j + 3) >= game_Start_Point_x + GameConfig::GAME_WIDTH)
					return false;
			}
		}
	}
	return true;
}

//check if the current shape is not collide with the board
bool player::Collide_With_Board() const
{
	for (int i = 0; i < GameConfig::BLOCK_SIZE_HEIGHT; i++)
	{
		for (int j = 0; j < GameConfig::BLOCK_SIZE_WIDTH; j++)
		{
			if ((shape[i][j] == '*') || (shape[i][j] == '@')) //the shape on the current board
			{
				int board_Row_Boundries = y - game_Start_Point_y + i + 2; //row boundries of the board
				int board_Col_Boundries = x - game_Start_Point_x + j + 1; //colomn boundries of the board
				if (board_Col_Boundries < 0) //collosion with left border
					return true;
				else if (board_Col_Boundries >= GameConfig::GAME_WIDTH) //collosion with right border
					return true;
				else if (board_Row_Boundries >= GameConfig::GAME_HEIGHT) //collosion with down border
					return true;
				else if (Game_Board[board_Row_Boundries][board_Col_Boundries] == '#') //collosion with the border
					return true;
				else if (Game_Board[board_Row_Boundries][board_Col_Boundries] == '*') //collosion with one of the printed astrisks
					return true;
			}
		}
	}
	return false;
}

//Flag for checking if the game is over
bool player::is_Game_Over() const
{
	for (int i = 0; i < GameConfig::BLOCK_SIZE_HEIGHT; i++)
	{
		for (int j = 0; j < GameConfig::BLOCK_SIZE_WIDTH; j++)
		{
			if (shape[i][j] == '*' && ((y - 1) < game_Start_Point_y)) //if any part of the Tetris shape is above the game board.
				return true;
		}

	}
	return false;
}

//clearing block from current board
void player::clear_Block() const
{
	for (int i = 0; i < GameConfig::BLOCK_SIZE_HEIGHT; i++)
	{
		for (int j = 0; j < GameConfig::BLOCK_SIZE_WIDTH; j++)
		{
			if ((shape[i][j] == '*') || (shape[i][j] == '@'))
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE));
				gotoxy(x + j, y + i);
				cout << ' ';
			}
		}
	}
}

//get the color of the current shape
void player::get_shape_color()
{
	if (add_colors == true)
		shape_color = (rand() % 5) + 1; //Randomly selects a color for the Tetris shape
	else
		shape_color = (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

//getting the next Tetris shape
void player::get_Shape()
{

	if ((shape == nullptr) && (bomb == false))
	{
		// Allocates memory for the new Tetris shape
		shape = new char[GameConfig::BLOCK_SIZE_HEIGHT][GameConfig::BLOCK_SIZE_WIDTH];
		int select_Shape = (rand() % 7); //Randomly selects the shape to the game
		switch (select_Shape)
		{
		case 0:
		{
			for (int i = 0; i < GameConfig::BLOCK_SIZE_HEIGHT; i++)
			{
				for (int j = 0; j < GameConfig::BLOCK_SIZE_WIDTH; j++)
				{
					shape[i][j] = GameConfig::Square_shape[i][j];
				}
			}
			break;
		}
		case 1:
		{
			for (int i = 0; i < GameConfig::BLOCK_SIZE_HEIGHT; i++)
			{
				for (int j = 0; j < GameConfig::BLOCK_SIZE_WIDTH; j++)
				{
					shape[i][j] = GameConfig::L_shape[i][j];
				}
			}
			break;
		}
		case 2:
		{
			for (int i = 0; i < GameConfig::BLOCK_SIZE_HEIGHT; i++)
			{
				for (int j = 0; j < GameConfig::BLOCK_SIZE_WIDTH; j++)
				{
					shape[i][j] = GameConfig::J_shape[i][j];
				}
			}
			break;
		}
		case 3:
		{
			for (int i = 0; i < GameConfig::BLOCK_SIZE_HEIGHT; i++)
			{
				for (int j = 0; j < GameConfig::BLOCK_SIZE_WIDTH; j++)
				{
					shape[i][j] = GameConfig::I_shape[i][j];
				}

			}
			break;
		}
		case 4:
		{
			for (int i = 0; i < GameConfig::BLOCK_SIZE_HEIGHT; i++)
			{
				for (int j = 0; j < GameConfig::BLOCK_SIZE_WIDTH; j++)
				{
					shape[i][j] = GameConfig::Z_shape[i][j];
				}

			}
			break;
		}
		case 5:
		{
			for (int i = 0; i < GameConfig::BLOCK_SIZE_HEIGHT; i++)
			{
				for (int j = 0; j < GameConfig::BLOCK_SIZE_WIDTH; j++)
				{
					shape[i][j] = GameConfig::S_shape[i][j];
				}

			}
			break;
		}
		case 6:
		{
			for (int i = 0; i < GameConfig::BLOCK_SIZE_HEIGHT; i++)
			{
				for (int j = 0; j < GameConfig::BLOCK_SIZE_WIDTH; j++)
				{
					shape[i][j] = GameConfig::T_shape[i][j];
				}

			}
			break;
		}
		}
	}
	else if (bomb == true)
	{
		shape = new char[GameConfig::BLOCK_SIZE_HEIGHT][GameConfig::BLOCK_SIZE_WIDTH];
		for (int i = 0; i < GameConfig::BLOCK_SIZE_HEIGHT; i++)
		{
			for (int j = 0; j < GameConfig::BLOCK_SIZE_WIDTH; j++)
			{
				shape[i][j] = GameConfig::bomb[i][j];
			}

		}
	}
}

//printing the current shape on the game board
void player::print_Block_To_Board()
{
	for (int i = 0; i < GameConfig::BLOCK_SIZE_HEIGHT; i++)
	{
		for (int j = 0; j < GameConfig::BLOCK_SIZE_WIDTH; j++)
		{
			if (shape[i][j] == '*')
			{
				box_score++;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), shape_color);
				Game_Board[y - game_Start_Point_y + i + 1][x - game_Start_Point_x + j + 1] = '*';
				Game_Board_colors[y - game_Start_Point_y + i + 1][x - game_Start_Point_x + j + 1] = shape_color;
				gotoxy(x + j, y + i);
				cout << Game_Board[y - game_Start_Point_y + i + 1][x - game_Start_Point_x + j + 1];
			}
		}
	}
}

//rotating the current shape clockwise
void player::rotate_ClockWise()
{
	char rotate[4][4]; //making a temporary 2D array to rotate the shape

	for (int i = 0; i < GameConfig::BLOCK_SIZE_HEIGHT; i++)
	{
		for (int j = 0; j < GameConfig::BLOCK_SIZE_WIDTH; j++)
		{

			rotate[i][j] = shape[GameConfig::BLOCK_SIZE - j - 1][i]; //getting the down left position

		}
	}
	if (!is_Collide_After_Rotate(rotate)) //checks if the rotate shape is not out of board
	{
		for (int i = 0; i < GameConfig::BLOCK_SIZE_HEIGHT; i++)
		{
			for (int j = 0; j < GameConfig::BLOCK_SIZE_WIDTH; j++)
			{
				shape[i][j] = rotate[i][j];
			}

		}
	}
}

//rotating the current shape counter clockwise
void player::rotate_Counter_ClockWise()
{
	char rotate[4][4]; //making a temporary 2D array to rotate the shape

	for (int i = 0; i < GameConfig::BLOCK_SIZE_HEIGHT; i++)
	{
		for (int j = 0; j < GameConfig::BLOCK_SIZE_WIDTH; j++)
		{

			rotate[i][j] = shape[j][GameConfig::BLOCK_SIZE - i - 1];//getting the up right position

		}
	}
	if (!is_Collide_After_Rotate(rotate)) //checks if the rotate shape is not out of board
	{
		for (int i = 0; i < GameConfig::BLOCK_SIZE_HEIGHT; i++)
		{
			for (int j = 0; j < GameConfig::BLOCK_SIZE_WIDTH; j++)
			{
				shape[i][j] = rotate[i][j];
			}

		}
	}
}

//checks if the current shape after rotate is collide with board
bool player::is_Collide_After_Rotate(char(*rotate)[4]) const
{
	for (int i = 0; i < GameConfig::BLOCK_SIZE_HEIGHT; i++)
	{
		for (int j = 0; j < GameConfig::BLOCK_SIZE_WIDTH; j++)
		{
			if ((rotate[i][j] == '*')) //rotate shape
			{
				int board_Row_Boundries = y - game_Start_Point_y + i + 2;//row boundries of the board
				int board_Col_Boundries = x - game_Start_Point_x + j + 1;//colomn boundries of the board
				if (board_Col_Boundries < 0) //collosion with left border
					return true;
				else if (board_Col_Boundries >= GameConfig::GAME_WIDTH) //collosion with right border
					return true;
				else if (board_Row_Boundries >= GameConfig::GAME_HEIGHT) //collosion with down border
					return true;
				else if (Game_Board[board_Row_Boundries][board_Col_Boundries] == '#') //collosion with the border
					return true;
				else if (Game_Board[board_Row_Boundries][board_Col_Boundries] == '*') //collosion with one of the printed astrisks
					return true;
			}
		}
	}
	return false;
}

//checking if a row is completely filled with asterisks
bool player::row_Of_Astrisks()
{
	int count = 0;//counting the number of astrisks each row
	for (int i = 1; i < GameConfig::GAME_HEIGHT - 1; i++)
	{
		for (int j = 1; j < GameConfig::GAME_WIDTH - 1; j++)
		{
			if (Game_Board[i][j] == '*')
				count++;
		}
		if (count == 10)
		{
			box_score += 10; //plus 10 in the score board
			y = i + 1; //number of row to delete the astrisks
			return true;
		}
		count = 0;
	}

	return false;
}

//remove a filled row from the game board
void player::remove_Row()
{
	//Shifts the rows above the filled row of astrisks down to remove it 
	for (int i = y - 1; i > 1; i--)
	{
		for (int j = 0; j < GameConfig::GAME_WIDTH - 1; j++)
		{
			Game_Board[i][j] = Game_Board[i - 1][j];
			Game_Board_colors[i][j] = Game_Board_colors[i - 1][j];
		}
	}

	//prints the new board without the filled row of astrisks
	for (int i = 1; i < GameConfig::GAME_HEIGHT - 1; i++)
	{
		for (int j = 0; j < GameConfig::GAME_WIDTH - 2; j++)
		{
			gotoxy(game_Start_Point_x + j - 1, game_Start_Point_y + i - 1);
			if (Game_Board[i][j] != '*' && Game_Board[i][j] != '#')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE));
				cout << ' ';
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Game_Board_colors[i][j]);
			cout << Game_Board[i][j];

		}
	}
}

//checks if the current shape is square, if is squre, dont rotate
bool player::is_Square() const
{
	if ((shape[0][0] == GameConfig::Square_shape[0][0]) &&
		(shape[0][1] == GameConfig::Square_shape[0][0]) &&
		(shape[1][0] == GameConfig::Square_shape[0][0]) &&
		(shape[1][1] == GameConfig::Square_shape[0][0]))

		return true;
	else
		return false;

}

//display the current score
void player::box_Score() const
{
	gotoxy(game_Start_Point_x + 20, GameConfig::GAME_HEIGHT + 2);
	cout << box_score;
}
