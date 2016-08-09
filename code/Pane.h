
#ifndef halt_Pane
#define halt_Pane

// Panes can be dragged around in the workspace.
// They're a place to hold useful widgets.

#include "View.h"

class Pane : public View
	{

public:
	Pane( size );
	
	View* click( point );
	void drag( int dx, int dy );

	void draw();
	};

#endif
