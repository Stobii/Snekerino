#pragma once
#include "Obstacle.h"
#include "Game.h"

void Obstacle::Draw( Board& brd )
{
	brd.DrawCell( loc, c );
}

Obstacle Obstacle::CreateNewObstacle( const Snake& snek )
{
	int tries = 0;
	Obstacle obstacle;
	do {
		obstacle.loc = Game::GetRandomLoc( 0, Board::width - 1, 0, Board::height - 1 );
		tries++;
	} while( snek.IsInTile( obstacle.loc ) && tries < 1500 );
	return obstacle;
}

bool Obstacle::Colliding( const Snake& snek )
{
	return snek.IsInTile( loc );
}

Location Obstacle::GetLoc() const
{
	return loc;
}
