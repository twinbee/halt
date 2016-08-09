
#ifndef halt_System_View
#define halt_System_View

#include "CircleView.h"

class TextField; // forward reference

class SystemView : public CircleView
	{
	int code, data, stack;

public:
	SystemView( unsigned diameter );
	
	void randomize( Object* sender );
	void interpret( TextField* sender );
		
	View* click( point );
	void drag( int dx, int dy );

	void draw();
	};

#endif
