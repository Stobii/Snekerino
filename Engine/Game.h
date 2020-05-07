/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Board.h"
#include "Snake.h"
#include "Goal.h"
#include "Score.h"
#include "Counter.h"
#include <random>
#include "Obstacle.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
    static Location GetRandomLoc( const int& rangeStartX, const int& rangeEndX, const int& rangeStartY, const int& rangeEndY );
private:
	void ComposeFrame();
	void UpdateModel();
    void Move();
    void BufferKeyboard();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
    char bufferedKeyboard = 'D';
    bool lost = false;
    int timer = 0;
    int movePeriod = 8;
    static constexpr Location start_loc{ Board::width / 2, Board::height / 2 };
    Color border{ 50, 0, 100 };
    Location delta_loc{ 1, 0 };
    Board brd;
    Snake snek;
    static constexpr int maxGoals = 10;
    static constexpr int maxObstacles = (Board::width * Board::height) / 3;
    int nGoals = 0;
    int nObstacles = 0;
    Obstacle obstacles[maxObstacles];
    Color goalColor{ 255, 0, 204 };
    Goal goals[maxGoals];
    Score score;
    Counter counter;
    static std::random_device rd;
    static std::mt19937 rng;
    std::uniform_int_distribution<int> zero100Dist;
	/********************************/
};