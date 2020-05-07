#include "Snake.h"
#include <assert.h>


void Snake::Segment::InitHead( const Location& in_loc, const Color& in_c )
{
	loc = in_loc;
	c = in_c;
}

void Snake::Segment::InitBody( const Location& in_loc, const Color& in_c )
{
	loc = in_loc;
	c = in_c;
}

void Snake::Segment::Follow( const Segment& next )
{
	loc = next.loc;
}

void Snake::Segment::Draw( Board& brd ) const
{
	brd.DrawCell( loc, c );
}

void Snake::Segment::MoveBy( const Location& delta_loc )
{
	assert( abs( delta_loc.x ) + abs( delta_loc.y ) == 1 );
	loc.Add( delta_loc );
}

void Snake::Segment::SetColor( const Color& in_c )
{
	c = in_c;
}

Location Snake::Segment::GetLoc() const
{
	return loc;
}

Snake::Snake( const Location& in_loc )
{
	assert( in_loc.x >= 0 );
	assert( in_loc.x < Board::width );
	assert( in_loc.y >= 0 );
	assert( in_loc.y < Board::height );
	segments[0].InitHead( in_loc, headColor );
	for( int i = nSegments - 1; i > 0; i-- ) {
		segments[i].InitBody( in_loc, bodyColor );
	}
}

void Snake::Draw( Board& brd ) const
{
	for( int i = 0; i < nSegments; i++ ) {
		segments[i].Draw( brd );
	}
}

void Snake::MoveBy( const Location& delta_loc )
{
	for( int i = nSegments - 1; i > 0; i-- ) {
		segments[i].Follow( segments[i - 1] );
	}
	segments[0].MoveBy( delta_loc );
}

void Snake::Grow( int amount )
{
	for( int i = 0; i < amount; i++ ) {
		if( nSegments < nSegmentsMax ) {
			segments[nSegments].InitBody( segments[nSegments - 1].GetLoc(), bodyColor );
			nSegments++;
		}
	}
}

void Snake::BodyRainbowColor()
{
	r = bodyColor.GetR();
	g = bodyColor.GetG();
	b = bodyColor.GetB();

	r += dr;
	g += dg;
	b += db;

	if( r > 255 ) {
		r = 255;
	}
	else if( r < 0 ) {
		r = 0;
	}
	if( g > 255 ) {
		g = 255;
	}
	else if( g < 0 ) {
		g = 0;
	}
	if( b > 255 ) {
		b = 255;
	}
	else if( b < 0 ) {
		b = 0;
	}

	bodyColor.SetR( r );
	bodyColor.SetG( g );
	bodyColor.SetB( b );

	if( r == 255 && g == 0 && b == 0 )
	{
		dr = 0; dg = colorSpeed; db = 0;
	}

	if( r == 255 && g == 255 && b == 0 )
	{
		dr = -colorSpeed; dg = 0; db = 0;
	}

	if( r == 0 && g == 255 && b == 0 )
	{
		dr = 0; dg = 0; db = colorSpeed;
	}

	if( r == 0 && g == 255 && b == 255 )
	{
		dr = 0; dg = -colorSpeed; db = 0;
	}

	if( r == 0 && g == 0 && b == 255 )
	{
		dr = colorSpeed; dg = 0; db = 0;
	}

	if( r == 255 && g == 0 && b == 255 )
	{
		dr = 0; dg = 0; db = -colorSpeed;
	}

	for( int i = 1; i < nSegments; i++ ) {
		segments[i].SetColor(bodyColor);
	}

}

bool Snake::IsInTileExceptLast( const Location& target ) const
{
	for( int i = 1; i < nSegments - 1; i++ ) {
		if( segments[i].GetLoc() == target ) {
			return true;
		}
	}
	return false;
}

bool Snake::IsInTile( const Location& target ) const
{
	for( int i = 0; i < nSegments; i++ ) {
		if( segments[i].GetLoc() == target ) {
			return true;
		}
	}
	return false;
}
const Location Snake::GetSegmentLoc( int segment )
{
	return segments[segment].GetLoc();
}
