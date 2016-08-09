
#include "geometry.h"
#include "graphics.h"

// screen coordinates -----------------------------------------------

point::point( int _x, int _y )
	: x(_x), y(_y) { }

size::size( unsigned _w, unsigned _h )
	: w(_w), h(_h) { }

rect::rect( point p, size s )
	: x(p.x), y(p.y), w(s.w), h(s.h) { }

bool rect::contains( point p )
	{
	return p.x >= x &&
		   p.x <= x + w &&
		   p.y >= y &&
		   p.y <= y + h;
	}

void rect::stroke()
	{
	glBegin( GL_LINE_LOOP );
		glVertex2i( x, y );
		glVertex2i( x + w - 1, y );
		glVertex2i( x + w - 1, y + h - 1 );
		glVertex2i( x, y + h - 1);
	glEnd();
	}

void rect::fill()
	{ glRecti( x, y, x + w, y + h ); }
