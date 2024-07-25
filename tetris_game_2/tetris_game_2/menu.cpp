#pragma warning(disable:4996)

#include "menu.h"
#include "human.h"
#include "player.h"
#include "computer.h"
#include "general.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include "Game_Config.h"



using namespace std;

// the menu of the tetris game
void menu::get_Menu()
{
    cout << "Hello and welcome to Roni and Avshi's Tetris game :)" << endl;
    bool endGame = true;
    bool break9 = false;
    bool add_colors = false;
    player* player[2];
    srand(time(NULL)); // for the rand function in get_Shape and get_Shape_color functions in tetrominoes class
    while (true)
    {
        cout << "Please enter:" << endl;
        cout << "(1) Start a new game - Human vs Human" << endl;
        cout << "(2) Start a new game - Human vs Computer" << endl;
        cout << "(3) Start a new game - Computer vs Computer" << endl;
        if (endGame == false)//flag if there is game that hasn't finish
        {
            cout << "(4) resume game" << endl;
        }
        cout << "(8) Instructions and Keys" << endl;
        cout << "(9) Exit" << endl;

        while (true)
        {
            int num = getch();

            clrscr();
            //initilize a new game for two players,human VS human
            if (num == GameConfig::HUMAN_VS_HUMAN)
            {
                player[0] = new human(GameConfig::Keys_Left);
                player[1] = new human(GameConfig::Keys_Right);
                add_colors = game_with_color();
                start_Game(player[0], player[1],add_colors);
                endGame = game(player[0], player[1]);
                clrscr();
                if (endGame)
                {
                    delete[] player;
                }
                break;
            }
            //initilize a new game for two players,human VS computer
            else if (num == GameConfig::HUMAN_VS_COMPUTER)
            {
                
                player[0] = new human(GameConfig::Keys_Left);
                player[1] = new computer();
                add_colors = game_with_color();
                int diff = choose_level();
                player[1]->set_difficulty(diff);
                start_Game(player[0], player[1], add_colors);
                endGame = game(player[0], player[1]);
                clrscr();
                if (endGame)
                {
                    delete[] player;
                }
                break;
            }
            //initilize a new game for two players,computer VS compuer
            else if (num == GameConfig::COMPUTER_VS_COMPUTER) 
            {
                
                player[0] = new computer();
                player[1] = new computer();
                add_colors = game_with_color();
                int diff = choose_level();
                player[0]->set_difficulty(diff);
                player[1]->set_difficulty(diff);
                start_Game(player[0], player[1], add_colors);
                endGame = game(player[0], player[1]);
                clrscr();
                if (endGame)
                {
                    delete[] player;
                }
                break;
            }
            //resume the game that already started
            else if ((num == GameConfig::RESUME_GAME) && (endGame == false))
            {
                
                player[0]->print_current_board();
                player[1]->print_current_board();
                endGame = game(player[0], player[1]);
                clrscr();
                if (endGame)
                {
                    delete[] player;
                }
                break;
            }
            //getting the instruction and keys of the game
            else if (num == GameConfig::INSTRUCTIONS_AND_KEYS)
            {
                instructions_and_keys();
                break;
            }
            //player wants to stop plat the game
            else if (num == GameConfig::EXIT_GAME)
            {
                cout << endl << "Thank you for playing with us :)" << endl;
                break9 = true;
                break;
            }
        }
        if (break9)
        {
            break;
        }
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

//shows the instructions and keys of the game
void menu::instructions_and_keys()
{
    cout << "Instructions:\n\n";
    cout << "In Tetris, your strategy is to bring down blocks from the top of the screen, to fill the empty rows and by that clearing them\n";
    cout << "You can move the blocks from left to right, and rotate them clockwise and counter clockwise\n";
    cout << "Plus, you can make them fall faster if you are sure of your positioning\n";
    cout << "In our game, there are 2 players: Player left and Player right\n";
    cout << "The keys of player Left:\n" << "'A' - Left\n" << "'D' - RIght\n" << "'S' - Rotate clockwise\n" << "'W' - Rotate counter clockwise\n" << "'X' - Drop\n";
    cout << "The keys of player Right:\n" << "'J' - Left\n" << "'L' - RIght\n" << "'K' - Rotate clockwise\n" << "'I' - Rotate counter clockwise\n" << "'M' - Drop\n";
    cout << "The game ends and the winner decleared if a Tetrimino reaches the top\n";
    cout << "Enjoy the game!\n";
    cout << "Please press ESC key to go back to menu\n";

    while (true)
    {

        if (_kbhit())
        {
            int getBack = _getch();
            if (getBack == 27)
            {
                clrscr();
                break;
            }
        }
    }
    return;
}

bool menu::game_with_color()
{
    cout << "Please choose:" << endl;
    cout << "(1) Game with colors" << endl;
    cout << "(2) Game without colors" << endl;
    while (true)
    {
        int num = getch();
        if (num == GameConfig::START_GAME_WITH_COLORS)
        {
            clrscr();
            return true;
        }
        else if (num == GameConfig::START_GAME_WITHOUT_COLORS)
        {
            clrscr();
            return false;
        }
    }
}

//initialize the start of the game
void menu::start_Game(player* p1, player* p2, bool add_colors)
{
    p1->set_box_Score();
    p2->set_box_Score();
    p1->draw_tetris_Game(GameConfig::MIN_X_LEFT + 1, GameConfig::MIX_Y_LEFT + 1);
    p2->draw_tetris_Game(GameConfig::MIX_X_RIGHT + 1, GameConfig::MIX_Y_RIGHT + 1);
    p1->init((GameConfig::GAME_WIDTH / 2) - 1, 1);
    p1->set_Shape();
    p2->set_Shape();
    p2->init(GameConfig::MIX_X_RIGHT + (GameConfig::GAME_WIDTH / 2) - 1, GameConfig::MIX_Y_RIGHT + 1);
    p1->set_colors(add_colors);
    p2->set_colors(add_colors);
    p1->get_shape_color();
    p2->get_shape_color();
}

// choose best, good or novice for computer player
int menu::choose_level() 
{
    int diff;
    clrscr();
    cout << "please choose Difficulty:" << endl;
    cout << "(1) Novice" << endl;
    cout << "(2) Good" << endl;
    cout << "(3) Best" << endl;
    while (true)
    {
        int num = getch();
        if ((num == GameConfig::NOVICE) || (num == GameConfig::GOOD) || (num == GameConfig::BEST))
        {
            diff = num;
            break;
        }
    }
    clrscr();
    return diff;
}

// the game
bool menu::game(player* p1, player* p2)
{
    bool endgame;
    bool escape_pressed = false;

    while (true)
    {
        if (p1->start_point())
        {
            p1->is_bomb_turn();
            p1->get_Shape();

            if (p1->check_if_bomb())
                p1->find_best_Pos_for_bomb();
            else
                p1->find_best_Pos_for_shape();
        }

        if (p2->start_point())
        {
            p2->is_bomb_turn();
            p2->get_Shape();

            if (p2->check_if_bomb())
                p2->find_best_Pos_for_bomb();
            else
                p2->find_best_Pos_for_shape();
        }
       
        int key_Pressed = 0;
        while (_kbhit()) //while both of the players pressing keys to move on the board
        {
            key_Pressed = _getch();
            if (key_Pressed == GameConfig::ESCAPE) //if one of the players wants to exit
            {
                escape_pressed = true;
                endgame = false; //update that the game is not over
                break;
            }
            else if (p1->is_Key_Valid(key_Pressed)) //checks if the key valid for left player
            {
                p1->move(key_Pressed);
            }
            else if (p2->is_Key_Valid(key_Pressed)) //checks if the key valid for right player
            {
                p2->move(key_Pressed);
            }
        }
        if (escape_pressed == true)
        {
            break;
        }

        p1->best_col(); //for computer player
        p2->best_col(); // for computer player

        p1->draw(); //drawing left player shape
        p2->draw(); //drawing right player shape

        Sleep(750); //sleep function for represent the movement of the tetromino

        p1->clear_Block(); //clearing left player shape
        p2->clear_Block(); //clearing right player shape

        if (p2->can_Move_Down() && !p2->Collide_With_Board()) //checks if the right player can move down
        {
            p2->move_Down();
        }
        else if (p2->is_Game_Over()) //flag for checking if the player right reach the top
        {
            p2->box_Score();
            p2->draw();
            if (p1->is_Game_Over()) //flag to check if left player also reach the top
            {
                p1->box_Score();
                p1->draw();
                gotoxy(0, GameConfig::GAME_HEIGHT + 4);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                cout << "Game Over! :(\n\n";
                //check who won from the box score
                if (p1->check_score() == p2->check_score())
                    cout << "It's a tie Game, every player with " << p1->check_score() << " points!!";
                else if (p1->check_score() > p2->check_score())
                    cout << "Player Left Win with " << p1->check_score() << " points!!";
                else
                    cout << "Player Right Win with " << p2->check_score() << " points!!";
                Sleep(4000); //showing who won

            }
            else
            {
                gotoxy(0, GameConfig::GAME_HEIGHT + 4);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                cout << "Game Over! :(\n\n";
                cout << "Player Left Win with " << p1->check_score() << " points!!";
                Sleep(4000); //showing who won
            }
            p2->set_Shape(); //deallocate right player shape
            p1->set_Shape(); //deallocate left player shape
            endgame = true; //update that the game is over
            break;
        }
        else
        {
            if (p2->check_if_bomb())
            {
                p2->bomb_explode();
            }
            else
            {
                p2->print_Block_To_Board();
            }
            while (p2->row_Of_Astrisks()) //checks if there is a row full of astrisks
            {
                p2->remove_Row();
            }

            p2->box_Score();//update box score of right player
            p2->init(GameConfig::MIX_X_RIGHT + (GameConfig::GAME_WIDTH / 2) - 1, GameConfig::MIX_Y_RIGHT + 1);
            p2->set_Shape();
            p2->get_shape_color();
        }

        if (p1->can_Move_Down() && !p1->Collide_With_Board()) //checks if the right player can move down
        {
            p1->move_Down();
        }
        else if (p1->is_Game_Over()) // flag for checking if the player left reach the top
        {
            p1->draw();
            p1->box_Score(); //update the box score of left player

            p1->set_Shape(); //deallocate left player shape
            p2->set_Shape(); //deallocate right player shape
            gotoxy(0, GameConfig::GAME_HEIGHT + 4);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            cout << "Game Over! :(\n\n";
            cout << "Player Right Win with " << p2->check_score() << " points!!";
            Sleep(4000);
            endgame = true; //update that the game is over
            break;
        }
        else
        {
            if (p1->check_if_bomb())
            {
                p1->bomb_explode();
            }
            else
            {
                p1->print_Block_To_Board();//print to board
            }
            while (p1->row_Of_Astrisks())
            {
                p1->remove_Row();
            }
            p1->box_Score();
            p1->init((GameConfig::GAME_WIDTH / 2) - 1, 1);
            p1->set_Shape();// return nullptr to shape
            p1->get_shape_color();
        }

    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    return endgame; //return whether the game ends or not
}
