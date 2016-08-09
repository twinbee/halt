
#include "ProcessorView.h"
#include "Color.h"
#include "graphics.h"

ProcessorView::ProcessorView( unsigned diameter )
	: CircleView( diameter )
	{ }

View* ProcessorView::click( point p )
	{
	parent->bringSubViewToFront( this );
	return this;
	}

void ProcessorView::drag( int dx, int dy )
	{
	bounds.x += dx;
	bounds.y += dy;
	glutPostRedisplay();
	}

void ProcessorView::draw()
	{
	glColor4f( 0.1, 0.1, 0.1, 0.8 );
	drawCircle( 0.99, outline );

	const float spaces = 10.0;
	const float circleRadius = 0.6 * M_PI / spaces;
	const float pathRadius = 0.9 - circleRadius;
	const float angleStep = 1.0 / spaces;

	float angle = 1.5 * angleStep;

	for ( unsigned reg = 0; reg <= 7; ++reg )
		{
		float intensity;
		switch ( g_cpu.age( reg ))
			{
			case 0: intensity = 1.0; break;
			case 1: intensity = 0.8; break;
			case 2: intensity = 0.6; break;
			case 3: intensity = 0.4; break;
			default: intensity = 0.2;
			}
		Color::palette["data"].scaleValue( intensity ).set();

		gotoPoint( angle, pathRadius );
			drawCircle( circleRadius, outline );
		glPopMatrix();
		
		angle += angleStep;
		}
	}
