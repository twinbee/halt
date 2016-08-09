
#include "Indicator.h"
#include "Clock.h"
#include "Color.h"

Indicator::Indicator( unsigned diameter )
	: CircleView( diameter )
	{ }

void Indicator::draw()
	{
	Color(0.333).scaleValue( g_clock.time() & 1 ? 0.6 : 0.4 ).set();
	drawCircle( 0.99, outline );
	}
