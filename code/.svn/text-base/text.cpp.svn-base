
#include "text.h"
#include "graphics.h"

using namespace std;

// typography
void* font = GLUT_BITMAP_9_BY_15;
const int fontWidth = 9;
const int fontHeight = 15;
const int leading = 2;
const int margin = 10;


void drawText( string s, point p )
	{
	glRasterPos2i( p.x, p.y + fontHeight - 4 );

	const int len = s.length();
	for ( int i = 0; i < len; ++i )
		glutBitmapCharacter( font, s[i]);
	}
