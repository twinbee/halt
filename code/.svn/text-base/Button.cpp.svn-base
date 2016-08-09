
#include "Button.h"
#include "graphics.h"
#include "text.h"

using namespace std;

Button::Button( string label )
	: Control( size( label.length() * fontWidth + 2 * margin, 30 ), label )
	{ }

View* Button::click( point p )
	{
	sendAction();
	return this;
	}

void Button::draw()
	{
	glBegin( GL_QUADS );
		// top
		glColor4f( 0.8, 0.9, 1, 0.75 );
		glVertex2i( 0, 0 );
		glVertex2i( bounds.w, 0 );

		// bottom
		glColor4f( 0.2, 0.3, 0.5, 0.5 );
		glVertex2i( bounds.w, bounds.h );
		glVertex2i( 0, bounds.h );
	glEnd();

	glColor3f( 1, 1, 1 );
	drawText( m_label, point( bounds.w / 2 - m_label.length() * fontWidth / 2,
							  bounds.h / 2 - fontHeight / 2 ));
	
	glColor4f( 0, 0, 0, 0.5 );
	localRect().stroke();
	}
