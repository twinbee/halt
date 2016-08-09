
#include "View.h"
#include "graphics.h"

using namespace std;

View::View( size s )
	: bounds( rect( point(), s )), parent( NULL )
	{ }

View::~View()
	{
	list<View*>::iterator i;
	for ( i = subViews.begin(); i != subViews.end(); ++i )
		delete *i;
	}

size View::getSize()
	{ return size( bounds.w, bounds.h ); }

void View::setSize( size s )
	{
	bounds.w = s.w;
	bounds.h = s.h;
	}

point View::getPosition()
	{ return point( bounds.x, bounds.y ); }

void View::setPosition( point p )
	{
	bounds.x = p.x;
	bounds.y = p.y;
	}

void View::setParent( View* v )
	{
	parent = v;
	}

void View::addSubView( View* v, point p )
	{
	v->setPosition( p );
	v->setParent( this );
	subViews.insert( subViews.begin(), v );
	}

void View::bringSubViewToFront( View* v )
	{
	if ( v != subViews.front() )
		{
		subViews.remove( v );
		subViews.insert( subViews.begin(), v );
		glutPostRedisplay();
		}

	if ( parent != NULL )
		parent->bringSubViewToFront( this );
	}

View* View::clickSubViews( point p )
	{
	list<View*>::iterator i;
	for ( i = subViews.begin(); i != subViews.end(); ++i )
		{
		rect r = (**i).boundsRect();
		point local( p.x - r.x, p.y - r.y );
		if ((**i).contains( local ))
			return (**i).click( local );
		}
	return this;
	}

View* View::click( point p )
	{ return clickSubViews( p ); }

void View::drag( int dx, int dy )
	{ }

void View::release()
	{ }

void View::key( char c )
	{ }

bool View::acceptsKey()
	{ return false; }

point View::screenPosition()
	{
	point p ( bounds.x, bounds.y );
	if ( parent != NULL )
		{
		point pp = parent->screenPosition();
		p.x += pp.x;
		p.y += pp.y;
		}
	return p;
	}

rect View::boundsRect()
	{ return bounds; }

rect View::localRect()
	{ return rect( point(), size( bounds.w, bounds.h )); }

bool View::contains( point p )
	{ return localRect().contains( p ); }

void View::beginLocal()
	{
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();
//	gluOrtho2D ( -0.5, bounds.w + 0.5, bounds.h + 0.5, -0.5 ); // center each pixel
	gluOrtho2D ( 0, bounds.w, bounds.h, 0 );

	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();
	glTranslatef( 0.375, 0.375, 0 );

	point s = screenPosition();

	glViewport( s.x, glutGet(GLUT_WINDOW_HEIGHT) - s.y - bounds.h, bounds.w, bounds.h );
	glScissor( s.x, glutGet(GLUT_WINDOW_HEIGHT) - s.y - bounds.h, bounds.w, bounds.h );
	}

void View::endLocal()
	{
	glMatrixMode( GL_PROJECTION );
	glPopMatrix();

	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();
	}

void View::drawSubViews()
	{
	list<View*>::reverse_iterator i;
	for ( i = subViews.rbegin(); i != subViews.rend(); ++i )
		{
		(**i).beginLocal();
		(**i).draw();
		(**i).endLocal();
		}
	}
