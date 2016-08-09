
#include "Pane.h"
#include "graphics.h"

Pane::Pane( size s )
	: View( s )
	{ }

View* Pane::click( point p )
	{
	View* v = clickSubViews( p );

	if ( v == this )
		{
		parent->bringSubViewToFront( this );
		return this;
		}
	else
		return v;
	}

void Pane::drag( int dx, int dy )
	{
	bounds.x += dx;
	bounds.y += dy;
	glutPostRedisplay();
	}

void Pane::draw()
	{
	glColor4f( 0.1, 0.1, 0.1, 0.8 );
	localRect().fill();

	glColor3f( 0, 0, 0 );
	localRect().stroke();

	drawSubViews();
	}
