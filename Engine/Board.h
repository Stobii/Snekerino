#pragma once
#include "Location.h"
#include "Colors.h"
#include "Graphics.h"
#include <random>

class Board {
public:
	Board( Graphics& gfx );
	void DrawCell( const Location& loc, const Color c);
	void DrawBorder( Color c );
	bool InsideBoard( const Location& loc );
	static constexpr int dimension = 12;
	static constexpr int width = 62;
	static constexpr int height = 46;
private:
	static constexpr int borderWidth = 6;
	static constexpr int borderHeight = 6;
	static constexpr int offsetX = ( Graphics::ScreenWidth - ( dimension * width ) ) / 2;
	static constexpr int offsetY = ( Graphics::ScreenHeight - ( dimension * height ) ) / 2;
	Graphics& gfx;
};