// Tetris_Game_Exe_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Tetris game by Avshi Sharabani 318799608 and Roni Kenigsberg 207106931
#include <iostream>
#include <Windows.h>
#include <conio.h>

#include "general.h"
#include "Game_Config.h"
#include "human.h"
#include "menu.h"

int main()
{
    menu Game;
    Game.get_Menu(); //getting our menu

    gotoxy(0, GameConfig::GAME_HEIGHT + 3);
}





