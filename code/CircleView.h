
#ifndef halt_circle_view
#define halt_circle_view

#include "View.h"

enum DrawingStyle { stroke, solid, outline };

class CircleView : public View
	{
protected:
	float radians( float angle );
	int numSteps( float radius, float angleSpan );
	void gotoPoint( float angle, float dist );

	void drawPoint( float angle, float dist );
	void drawLine( float angle, float begin, float end );
	void drawArc( float radius, float begin, float end );
	void drawCircle( float radius, DrawingStyle );

//	void drawCirclesOnArc( int numCircles, float pathRadius, float begin, float end, DrawingStyle );

public:
	CircleView( unsigned diameter );
	virtual ~CircleView();

	bool contains( point );
	void beginLocal();
	};

#endif
