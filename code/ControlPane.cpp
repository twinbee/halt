
#include "ControlPane.h"
#include "Processor.h"
#include "graphics.h"

ControlPane::ControlPane()
	: Pane( size()),
	  resetButton( new Button("Reset")),
	  stepButton( new Button("Step"))
	{
	addSubView( resetButton, point( 10, 10 ));

	addSubView( stepButton,
		point( resetButton->getPosition().x + resetButton->getSize().w + 10, 10 ));

	addSubView( &g_timer,
		point( stepButton->getPosition().x + stepButton->getSize().w + 10, 10 ));

	rect r = g_timer.boundsRect();

	setSize( size( r.x + r.w + 10, r.h + 20 ));

	actions["reset"] = (Action) &ControlPane::reset;
	actions["step"] = (Action) &ControlPane::step;
	
	resetButton->connect( this,"reset");
	stepButton->connect( this,"step");
	g_timer.connect( this,"step");

	reset( this );
	}

void ControlPane::reset( Object* sender )
	{
	g_timer.stop();
	g_timer.rate( 10.0 ); // hertz

	g_cpu.reset();
	
	glutPostRedisplay();
	}

void ControlPane::step( Object* sender )
	{
	// If a program is running, continue it.
	// The user can also force a step.

	if ( ! g_timer.enabled()) // user initiated step
		g_timer.tick();

	g_cpu.step();

	if ( ! g_cpu.smoothSailing())
		g_timer.stop();

	glutPostRedisplay();
	}
