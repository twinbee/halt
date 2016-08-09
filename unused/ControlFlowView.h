
#ifndef halt_ControlFlowView
#define halt_ControlFlowView

#include "CircleView.h"

class ControlFlowView : public CircleView
	{
	unsigned code;
	float radius;

	void drawArcBetween( unsigned src, unsigned dest );

public:
	ControlFlowView( unsigned diameter );

	void randomize( Object* sender );
	
	void draw();
	};

#endif
