
#include "TextField.h"
#include "text.h"
#include "graphics.h"
#include "utility.h"

using namespace std;

TextField::TextField( size s )
	: Control( s ), cursor( 0 )
	{ }

View* TextField::click( point p )
	{
	cursor = ( p.x - 5 ) / fontWidth;
	clamp <unsigned> ( cursor, 0, value.length() );

	glutPostRedisplay();

	return this;
	}
	
string TextField::stringValue()
	{ return value; }

void TextField::stringValue( string newValue )
	{
	value = newValue;
	cursor = value.length();
	}

void TextField::key( char c )
	{
	switch ( c )	
		{
		case enterKey:
		case returnKey:
			sendAction();
			break;

		case backspaceKey:
			if ( cursor > 0  )
				{
				value = value.substr( 0, cursor - 1 ) + 
						value.substr( cursor, value.length() - cursor );
				--cursor;
				}
			break;

		case deleteKey:
			if ( cursor < value.length() )
				{
				value = value.substr( 0, cursor ) + 
						value.substr( cursor + 1, value.length() - cursor - 1 );
				}
			break;

		case leftKey:
			if ( cursor > 0  )
				--cursor;
			break;

		case rightKey:
			if ( cursor < value.length() )
				++cursor;
			break;

		case upKey:		// ignore these
		case downKey:	// TextField is for a single line
			break;

		case homeKey:
			cursor = 0;
			break;

		case endKey:
			cursor = value.length();
			break;

		default:
			// [ to-do : test if c is in allowed character set ]
			// insert character at cursor location
			value = value.substr( 0, cursor ) + c +
					value.substr( cursor, value.length() - cursor );

			++cursor;
		}

	glutPostRedisplay();
	}

bool TextField::acceptsKey()
	{ return true; }

void TextField::draw()
	{
	rect r = localRect();
	// background
	// [ todo : replace with single background fill ]
	glColor4f( 0.8, 0.9, 1, 0.7 );
	r.fill();
	glColor4f( 0.2, 0.3, 0.5, 0.15 );
	r.fill();

	// text
	glColor3f( 0, 0, 0 );
	drawText( value, point( margin, bounds.h / 2 - fontHeight / 2 ));

	// cursor
	glColor4f( 0.2, 0.3, 0.5, 0.75 );
	glBegin( GL_LINES );
		int x = cursor * fontWidth + margin;
		int y = bounds.h / 2 - fontHeight / 2;
		glVertex2i( x, y );
		glVertex2i( x, y + fontHeight );
	glEnd();
	
	// border
	glColor3f( 0, 0, 0 );
	r.stroke();
	}
