
#include "Control.h"
#include "graphics.h"

using namespace std;

Control::Control( size s, string label )
	: View( s ),
	  target( NULL ), m_enabled( true ), m_label( label )
	{ }

Control::~Control()
	{ }
	
void Control::connect( Object* o, string message )
	{
	target = o;
	action = message;
	}

void Control::sendAction()
	{
	if ( target && !action.empty() )
		target->doAction( action, this );
	}

bool Control::enabled()
	{ return m_enabled; }

void Control::enabled( bool newValue )
	{ m_enabled = newValue; }

string Control::label()
	{ return m_label; }

void Control::label( string newLabel )
	{
	m_label = newLabel;
	glutPostRedisplay();
	}
