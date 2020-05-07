#pragma once
#include "Graphics.h"
#include "Location.h"
#include "Colors.h"

class Score {
public:
	void IncreaseScore( int amount ) {
		if( score < maxScore ) {
			score += amount;
		}
	}
	void Draw( Graphics& gfx ) {
		/*for( int x = start_loc.x; x < width * score + start_loc.x; x++ ) {
			for( int y = start_loc.y; y < height + start_loc.y; y++ ) {
				gfx.PutPixel( x, y, c );
			}
		}*/
		gfx.DrawRectDim( start_loc.x, start_loc.y, width * score + start_loc.x, height + start_loc.y, c );
	}
private:
	int score = 0;
	static constexpr int height = 18;
	static constexpr int width = 8;
	static constexpr Location start_loc{ 0, 0 };
	static constexpr int maxScore = Graphics::ScreenWidth / width - start_loc.x;
	Color c = Colors::Blue;
};