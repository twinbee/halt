
#ifndef halt_SystemView
#define halt_SystemView

#include "CircleView.h"

class SystemView : public CircleView
	{
	float m_cpuScale;

	float m_spaces;
	float m_circleRadius;
	float m_pathRadius;
	float m_angleStep;

public:
	SystemView( unsigned diameter );
	
	View* click( point );
	void drag( int dx, int dy );

	void draw();
	};

#endif
