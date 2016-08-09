
#include <cstdlib>
#include <cmath>

#include "SystemView.h"
#include "TextField.h"
#include "Color.h"
#include "graphics.h"

using namespace std;

SystemView::SystemView( unsigned diameter )
	: CircleView( diameter ),
	  code(1), data(1), stack(1)
	{
	methods["randomize"] = (Method) &SystemView::randomize;
	methods["interpret"] = (Method) &SystemView::interpret;
	}

void SystemView::randomize( Object* sender )
	{
	code = rand() % 20;
	data = rand() % 20;
	stack = rand() % 20;
	glutPostRedisplay();
	}

void SystemView::interpret( TextField* sender )
	{
	string s = sender->stringValue();

	if ( s == "reset")
		code = data = stack = 0;
		
	glutPostRedisplay();
	}

View* SystemView::click( point p )
	{
	randomize( NULL );
	parent->bringSubViewToFront( this );
	return this;
	}

void SystemView::drag( int dx, int dy )
	{
	bounds.x += dx;
	bounds.y += dy;
	glutPostRedisplay();
	}

void SystemView::draw()
	{
	glColor4f( 0.1, 0.1, 0.1, 0.8 );
	drawCircle( 0.99, outline );

	// draw the Flame of Computation!
	for ( float f = 0.1; f < 1; f += 0.1 )
		{
		float pos = ( rand() % 16 ) / 16.0;
		glColor4f( 0, 1, 0, 1 - f );
		drawArc( f / 10 + 0.03, pos, pos + 0.333 );
		}

	// draw data registers
	Color::palette["data"].scaleValue( 0.5 ).set();
	drawCirclesOnArc( 8, 0.2, 0.5 / 9, 1 - 0.5 / 9, outline );
	
	// draw memory
	float total = code + data + stack + 3; // leave room for gaps!

	Color::palette["code"].set();
	drawCirclesOnArc( code, 0.7, 0.5 / total, (code + 0.5) / total, outline );

	Color::palette["data"].set();
	drawCirclesOnArc( data, 0.7, (code + 0.5) / total, (code + data + 0.5) / total, outline );

	Color::palette["address"].set();
	drawCirclesOnArc( stack, 0.7, (code + data + 2.5) / total, 1 - 0.5 / total, outline );

	Color().set(); // default color
	glPointSize( 3 );

	// unused address space
	drawPoint((code + data + 1.0) / total, 0.7 );
	drawPoint((code + data + 1.5) / total, 0.7 );
	drawPoint((code + data + 2.0) / total, 0.7 );

	// begin / end boundary
	glLineWidth( 2 );
	drawLine( 0, 0.6, 0.8 );
	glLineWidth( 1 );
	}
