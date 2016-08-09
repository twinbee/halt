
#include "CircleView.h"
#include "graphics.h"

CircleView::CircleView( unsigned diameter )
	: View( size( diameter, diameter ))
	{ }

CircleView::~CircleView()
	{ }

bool CircleView::contains( point p )
	{
	float radius = bounds.w / 2.0;
	float x = p.x - radius;
	float y = p.y - radius;
	return ( sqrt( x * x + y * y )) <= radius;
	}

void CircleView::beginLocal()
	{
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();

	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();

	point s = screenPosition();

	glViewport( s.x, glutGet(GLUT_WINDOW_HEIGHT) - s.y - bounds.h, bounds.w, bounds.h );
	glScissor( s.x, glutGet(GLUT_WINDOW_HEIGHT) - s.y - bounds.h, bounds.w, bounds.h );

	// [ todo : clip drawing to circle instead of whole bounding box -- STENCIL BUFFER ]
	}

float CircleView::radians( float angle )
	{
	// rotate, reverse, and scale to standard radians
	return (1.25 - angle) * 2 * M_PI;
	}

int CircleView::numSteps( float radius, float angleSpan )
	{
	return static_cast<int>( bounds.w / 5 * angleSpan * radius ) + 10;
	}

void CircleView::gotoPoint( float angle, float dist )
	{
	angle = radians( angle );
	glPushMatrix();
	glTranslatef( dist * cos( angle ), dist * sin( angle ), 0 );
	}

void CircleView::drawPoint( float angle, float dist )
	{
	gotoPoint( angle, dist );
	glBegin( GL_POINTS );
		glVertex2f( 0, 0 );
	glEnd();
	glPopMatrix();
	}

void CircleView::drawLine( float angle, float begin, float end )
	{
	angle = radians( angle );

	float x = cos( angle );
	float y = sin( angle );

	glBegin( GL_LINES );
		glVertex2f( begin * x, begin * y );
		glVertex2f( end * x, end * y );
	glEnd();
	}

void CircleView::drawCircle( float radius, DrawingStyle style )
	{
	glEnable( GL_LINE_SMOOTH );

	int i, n = numSteps( radius, 1.0 );
	float angle, step = 2 * M_PI / n;

	if ( style == solid || style == outline )
		{
		glBegin( GL_POLYGON );
			for ( angle = 0, i = n; i--; angle += step )
				glVertex2f( radius * cos( angle ), radius * sin( angle ));
		glEnd();
		}
	
	float mainColor[4];

	if ( style == outline )
		{
		glGetFloatv( GL_CURRENT_COLOR, mainColor );
		glColor3f( 0, 0, 0 );
		}

	glBegin( GL_LINE_LOOP );
		for ( angle = 0, i = n; i-- ; angle += step )
			glVertex2f( radius * cos( angle ), radius * sin( angle ));
	glEnd();

	if ( style == outline )
		glColor4fv( mainColor );

	glDisable( GL_LINE_SMOOTH );
	}

void CircleView::drawArc( float radius, float begin, float end )
	{
	glEnable( GL_LINE_SMOOTH );

	if ( end < begin )	// swap if wrong order
		{
		float temp = end;
		end = begin;
		begin = temp;
		}

	int n = numSteps( radius, end - begin );

	begin = radians( begin );
	end = radians( end );
	
	float step = (end - begin) / n;

	glBegin( GL_LINE_STRIP );
		for ( float angle = begin; n-- ; angle += step )
			glVertex2f( radius * cos( angle ), radius * sin( angle ));

		// complete the arc -- remember this isn't a line loop
		glVertex2f( radius * cos( end ), radius * sin( end ));
	glEnd();

	glDisable( GL_LINE_SMOOTH );
	}
