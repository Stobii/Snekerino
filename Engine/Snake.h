#pragma once
#include "Location.h"
#include "Colors.h"
#include "Board.h"

class Snake {
private:
	class Segment {
	public:
		void InitHead( const Location& in_loc, const Color& in_c );
		void InitBody( const Location& in_loc, const Color& in_c );
		void Follow( const Segment& next );
		void Draw( Board& brd ) const;
		void MoveBy( const Location& delta_loc );
		void SetColor( const Color& in_c );
		Location GetLoc() const;
	private:
		Location loc{ 0, 0 };
		Color c;
	};
public:
	Snake( const Location& in_loc );
	void Draw( Board& brd ) const;
	void MoveBy( const Location& delta_loc );
	void Grow( int amount );
	void BodyRainbowColor();
	bool IsInTileExceptLast( const Location& target ) const;
	bool IsInTile( const Location& target ) const;
	const Location GetSegmentLoc( int segment);
	int GetnSegments() {
		return nSegments;
	}
private:
	static constexpr int nSegmentsMax = Board::width * Board::height;
	Segment segments[nSegmentsMax];
	int nSegments = 5;
	Color bodyColor = Colors::Red;
	Color headColor = Colors::White;
	int colorSpeed = 3;
	int r = 255, g = 0, b = 0, dr = 0, dg = 0, db = 0;
};