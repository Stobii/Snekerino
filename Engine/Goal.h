#pragma once
#include "Location.h"
#include "Board.h"
#include "Colors.h"
#include "Snake.h"
#include <random>

class Goal {
public:
	static Goal CreateNewGoal();
	void Draw( Board& brd );
	static void ColorChange( Color& in_c );
	void SetColor( const Color& in_c );
	void CollidingRespawn( const Snake& player );
	Location GetLocation() const;
private:
	Location loc;
	Color c{ 255, 0, 204 };
};