#include "Goal.h"
#include "Game.h"


Goal Goal::CreateNewGoal()
{
	Goal goal;
	goal.loc = Game::GetRandomLoc( 0, Board::width - 1, 0, Board::height - 1 );
	return goal;
}

void Goal::Draw( Board& brd )
{
	brd.DrawCell( loc, c );
}

void Goal::ColorChange( Color& in_c )
{
	int g = in_c.GetG();
	int b = in_c.GetB();
	int dc = 5;

	if( g <= 0 ) {
		in_c.SetR( 254 );
	}
	else if( g >= 255  ) {
		in_c.SetR( 255 );
	}

	/*if( b <= 0 ) {
		db = -db;
	}
	else if(  b >= 255 ) {
		db = -db;
	}*/
	if( in_c.GetR() == 254 ) {
		g += dc;
		b += dc;
	}
	else if( in_c.GetR() == 255 ) {
			g -= dc;
			b -= dc;
		}

	if( g < 0 ) {
		g = 0;
	}
	else if( g > 255 ) {
		g = 255;
	}

	if( b < 0 ) {
		b = 0;
	}
	else if( b > 255 ) {
		b = 255;
	}

	in_c.SetG( g );
	in_c.SetB( b );
}

void Goal::SetColor( const Color& in_c )
{
	c = in_c;
}

void Goal::CollidingRespawn( const Snake& player )
{
	int tries = 0;
	do {
		loc = Game::GetRandomLoc( 0, Board::width - 1, 0, Board::height - 1 );
		tries++;
	} while( player.IsInTile( loc ) && tries < 500 );
}

Location Goal::GetLocation() const
{
	return loc;
}
