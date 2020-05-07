#include "Board.h"

Board::Board( Graphics& gfx )
	:
	gfx(gfx)
{
}

void Board::DrawCell( const Location& loc, const Color c )
{
	gfx.DrawRectDim( 2+ loc.x * dimension + offsetX,  2 + loc.y * dimension + offsetY, dimension - 2, dimension - 2, c );
}

void Board::DrawBorder( Color c )
{
	for( int y = offsetY - borderHeight; y < height * dimension + offsetY + borderHeight; y++ ) {
		for( int x = offsetX - borderWidth; x < width * dimension + offsetX + borderWidth; x++ ) {
			gfx.PutPixel( x, y, c );
		}
	}
	for( int y = offsetY; y < height * dimension + offsetY; y++ ) {
		for( int x = offsetX; x < width * dimension + offsetX; x++ ) {
			gfx.PutPixel( x, y, Colors::Black );
		}
	}
}

bool Board::InsideBoard( const Location& loc )
{
	return loc.x >= 0 && loc.x < width&& loc.y >= 0 && loc.y < height;
}
