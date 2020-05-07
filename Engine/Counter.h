#pragma once
#include "Graphics.h"
#include "Location.h"
#include "Colors.h"

class Counter {
public:
	void Draw( Graphics& gfx ) {
		if( !stopCounting ) {
			float lol = ( float ) timer / ( float ) maxTime;
			int width = ( Graphics::ScreenWidth - 1 ) - ( ( Graphics::ScreenWidth - 1 ) * ( lol ) );
			gfx.DrawRectDim( loc.x, loc.y, width, height, c );
		}
	}
	void Update( int& movePeriod ) {
		if( !stopCounting ) {
			timer++;
			maxTime = 1600 * ( ( 1 / ( float ) movePeriod )   );
			if( timer >= maxTime && movePeriod > 2 ) {
				timer = 0;
				movePeriod -= 1;
			}
			else if( movePeriod == 2 ) {
				stopCounting = true;
			}
		}
	}
private:
	bool stopCounting = false;
	int maxTime = 20;
	int timer = 0;
	static constexpr int height = 10;
	Location loc{ 0, 589 };
	Color c = Colors::Yellow;
};