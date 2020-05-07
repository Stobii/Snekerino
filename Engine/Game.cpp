/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd( gfx ),
	snek( start_loc ),
	zero100Dist( 0, 100 )
{
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	Obstacle obstacle;
	counter.Update( movePeriod );
	Goal::ColorChange( goalColor );
	for( int i = 0; i < nGoals; i++ ) {
		goals[i].SetColor( goalColor );
	}
	if( !lost ) {
		timer++;
		BufferKeyboard();

		if( timer >= movePeriod ) {
			if( zero100Dist( rng ) <= 25 && nGoals < maxGoals ) {
				goals[nGoals] = Goal::CreateNewGoal();
				nGoals++;
			}
			if( zero100Dist( rng ) <= 8 && nObstacles < maxObstacles ) {
				obstacles[nObstacles] = Obstacle::CreateNewObstacle( snek );
				nObstacles++;
			}

			Move();
			timer = 0;
			Location nextHeadLoc = snek.GetSegmentLoc( 0 );
			nextHeadLoc.Add( delta_loc );
			snek.MoveBy( delta_loc );

			for( int i = 0; i < nGoals; i++ ) {
				if( snek.IsInTile( goals[i].GetLocation() ) ) {
					goals[i].CollidingRespawn( snek );
					snek.Grow( 5 );
					score.IncreaseScore( 1 );
				}
			}

			for( int i = 0; i < nObstacles; i++ ) {
				if( snek.IsInTile( obstacles[i].GetLoc() ) ) {
					lost = true;
				}
			}

			if( snek.IsInTileExceptLast( nextHeadLoc ) || !brd.InsideBoard( nextHeadLoc ) ) {
				lost = true;
			}

		}
	}
}

void Game::Move()
{
	if( bufferedKeyboard == 'D' && delta_loc.x != -1 ) {
		delta_loc = { 1, 0 };
	}
	if( bufferedKeyboard == 'A' && delta_loc.x != 1 ) {
		delta_loc = { -1, 0 };
	}
	if( bufferedKeyboard == 'S' && delta_loc.y != -1 ) {
		delta_loc = { 0, 1 };
	}
	if( bufferedKeyboard == 'W' && delta_loc.y != 1 ) {
		delta_loc = { 0, -1 };
	}
}
void Game::BufferKeyboard()
{
	if( wnd.kbd.KeyIsPressed( 'D' ) && bufferedKeyboard != 'D' ) {
		bufferedKeyboard = 'D';
	}
	if( wnd.kbd.KeyIsPressed( 'A' ) && bufferedKeyboard != 'A' ) {
		bufferedKeyboard = 'A';
	}
	if( wnd.kbd.KeyIsPressed( 'S' ) && bufferedKeyboard != 'S' ) {
		bufferedKeyboard = 'S';
	}
	if( wnd.kbd.KeyIsPressed( 'W' ) && bufferedKeyboard != 'W' ) {
		bufferedKeyboard = 'W';
	}
}


void Game::ComposeFrame()
{
	if( !lost ) {
		brd.DrawBorder( border );
		snek.BodyRainbowColor();
		counter.Draw( gfx );
	}
	for( int i = 0; i < nGoals; i++ ) {
		goals[i].Draw( brd );
	}
	for( int i = 0; i < nObstacles; i++ ) {
		obstacles[i].Draw( brd );
	}
	snek.Draw( brd );
	score.Draw( gfx );

	/*std::uniform_int_distribution<> colorDist(0, 255);
	for( int y = 0; y < brd.GetBoardHeight(); y++ ) {
		for( int x = 0; x < brd.GetBoardWidth(); x++ ) {
			Location loc = { x, y };
			Color c( colorDist( rng ), colorDist( rng ), colorDist( rng ) );
			brd.DrawCell( loc, c );
		}
	}*/
}

std::random_device Game::rd;
std::mt19937 Game::rng( Game::rd() );


Location Game::GetRandomLoc( const int& rangeStartX, const int& rangeEndX, const int& rangeStartY, const int& rangeEndY )
{
	std::uniform_int_distribution<int> xDist( rangeStartX, rangeEndX );
	std::uniform_int_distribution<int> yDist( rangeStartY, rangeEndY );
	return { xDist( rng ), yDist( rng ) };
}