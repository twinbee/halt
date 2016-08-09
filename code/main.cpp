
#include "graphics.h"
#include "Color.h"
#include "Workspace.h"
#include "ProgramEditor.h"
#include "SystemView.h"
#include "ControlPane.h"

// globals -----------------------------------------

Workspace* screen;

View* mouseTarget;	// drag, release go to View that received initial click
View* keyTarget;

bool dragging = false;
point dragOrigin;

// setup OpenGL ----------------------------------------

void initGL()
	{
	glShadeModel( GL_SMOOTH );

	glEnable( GL_SCISSOR_TEST );

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	}

// GLUT callbacks ------------------------------------------

void keyboard( unsigned char key, int x, int y )
	{
	if ( keyTarget )
		{
		switch ( key )
			{
			case 0x03:	key = enterKey;			break;
			case 0x0d:	key = returnKey;		break;
		#ifdef __APPLE__
			case 0x08:	key = deleteKey;		break;
			case 0x7f:	key = backspaceKey;		break;
		#else
				// <matt>
				//	running on a windows PC or Linux
				//	this could cause trouble if we are running Linux on a Mac
				// </matt>
				// <mike>
				//	What kind of nutjob would do that? Oh wait, that's me...
				//	Let's not cater to extreme minorities.
				// </mike>
			case 0x7f:	key = deleteKey;		break;
			case 0x08:	key = backspaceKey;		break;
		#endif
			}

		keyTarget->key( key );
		}
	}

void special( int rawKey, int x, int y )
	{
	if ( keyTarget )
		{
		char key = nullKey;

		switch ( rawKey )
			{
			case GLUT_KEY_LEFT:		key = leftKey;		break;
			case GLUT_KEY_RIGHT:	key = rightKey;		break;
			case GLUT_KEY_UP:		key = upKey;		break;
			case GLUT_KEY_DOWN:		key = downKey;		break;
			case GLUT_KEY_HOME:		key = homeKey;		break;
			case GLUT_KEY_END:		key = endKey;		break;
			}

		keyTarget->key( key );
		}
	}

void mouse( int Button, int state, int x, int y )
	{
	if ( state == GLUT_DOWN )
		{
		mouseTarget = screen->click( point( x, y ));

		if ( mouseTarget->acceptsKey())
			keyTarget = mouseTarget;

		dragOrigin = point( x, y );
		dragging = true;
		}
	else
		{
		mouseTarget->release();
		dragging = false;
		}
	}

void motion( int x, int y )
	{
	if ( dragging )
		{
		mouseTarget->drag( x - dragOrigin.x, y - dragOrigin.y );
		dragOrigin = point( x, y );
		}
	}

void reshape( int w, int h )
	{ screen->setSize( size( w, h )); }

void display()
	{
	screen->draw();
	glutSwapBuffers();
	}

// --------------------------------------------------

int main( int argc, char* argv[] )
	{
	// setup GLUT ---------------------------------------
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );

	glutInitWindowSize( 640, 480 );
	glutCreateWindow("Humane Assembly Language Tools");

	glutDisplayFunc( display );
	glutReshapeFunc( reshape );
	glutKeyboardFunc( keyboard );
	glutSpecialFunc( special );
	glutMouseFunc( mouse );
	glutMotionFunc( motion );

	//glutIdleFunc( display ); // for snowflakes

	initGL();

	// ooh, pretty colors! -------------------------------
	Color::palette["error"] = Color( 0 );
	Color::palette["command"] = Color( 0.8 );
	Color::palette["code"] = Color( 0.333 );
	Color::palette["data"] = Color( 0.6 );
	Color::palette["address"] = Color( 0.1 );

	// create the interface ------------------------------
	screen = new Workspace( size( glutGet( GLUT_WINDOW_WIDTH ),
								  glutGet( GLUT_WINDOW_HEIGHT )));

	screen->addSubView( new SystemView( 350 ), point( 20, 20 ));

	screen->addSubView( new ControlPane, point( 400, 20 ));

	ProgramEditor* progEdit = new ProgramEditor;
	progEdit->program( new Program("test"));
	screen->addSubView( progEdit, point( 400, 90 ));

	mouseTarget = screen;
	keyTarget = progEdit;

	// start the application -----------------------------
	glutMainLoop();

	return 0;
	}
