
#include "ControlFlowView.h"
#include "graphics.h"
#include "Color.h"

ControlFlowView::ControlFlowView( unsigned diameter )
	: CircleView( diameter ),
	  code( 9 ), radius( 0.7 )
	{
	methods["randomize"] = (Method) &ControlFlowView::randomize;
	}

void ControlFlowView::randomize( Object* sender )
	{
	code = rand() % 20 + 5;
	glutPostRedisplay();
	}

void ControlFlowView::drawArcBetween( unsigned src, unsigned dest )
	{
	float srcAngle = (src + 1.0) / (code + 1);
	float destAngle = (dest + 1.0) / (code + 1);

	if ( dest == src + 1 )
		{
		// normal instruction sequence
		drawArc( radius, srcAngle, destAngle );
		}
	else if ( dest > src )
		{
		// branch forward
		drawArc( destAngle - srcAngle, srcAngle, destAngle );
//		gotoPoint( srcAngle + 0.5 * (destAngle - srcAngle), radius + destAngle - srcAngle );
//		drawArc( destAngle - srcAngle, srcAngle + 0.5, destAngle + 0.5 );
//		glPopMatrix();
		}
	else if ( dest < src )
		{
		// branch backward
		
		}
	else
		{
		// branch to self
		
		}
	}

void ControlFlowView::draw()
	{
	glColor4f( 0.2, 0.2, 0.2, 0.5 );
	drawCircle( 0.99, outline );

	Color::palette["code"].scaleValue( 0.75 ).set();
	drawArcBetween( 0, 1 );
	drawArcBetween( 0, 2 );
	drawArcBetween( 0, 3 );

	Color::palette["code"].scaleValue( 0.5 ).set();
	drawCirclesOnArc( code, radius, 0.5 / (code + 1), 1 - 0.5 / (code + 1), outline );

	// begin/end boundary
	glColor3f( 0, 0, 0 );
	drawLine( 0, 0.6, 0.8 );
	}
