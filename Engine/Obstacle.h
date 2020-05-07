#pragma once
#include "Board.h"
#include "Location.h"
#include "Colors.h"
#include "Snake.h"

class Obstacle {
public:
	void Draw( Board& brd );
	static Obstacle CreateNewObstacle( const Snake& snek);
	bool Colliding( const Snake& snek );
	Location GetLoc() const;
private:
	Location loc;
	Color c{ 100, 100, 100 };
};