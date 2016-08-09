
#include <cmath>

#include "Rainbow.h"
#include "Color.h"
#include "graphics.h"

Rainbow::Rainbow( unsigned diameter )
	: CircleView( diameter )
	{ }

void Rainbow::draw()
	{
	// light on dark
	glColor3f( 0.1, 0.1, 0.1 );
	drawCircle( 0.99, outline );
	drawColorWheel( 18, 1.0, 0.8 );

	// dark on light
	glColor3f( 0.9, 0.9, 0.9 );
	drawCircle( 0.6, outline );
	drawColorWheel( 18, 0.5, 0.45 );
	}

void Rainbow::drawColorWheel( int numColors, float value, float pathRadius )
	{
	float circleRadius = 0.667 * M_PI / numColors * pathRadius;
	float step = 1.0 / numColors;

	for ( float angle = 0; numColors-- ; angle += step )
		{
		gotoPoint( angle, pathRadius );
		Color( angle ).scaleValue( value ).set();
		drawCircle( circleRadius, solid );
		glPopMatrix();
		}
	}
