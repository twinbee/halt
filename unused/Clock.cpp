
#include "Clock.h"

Clock g_clock;

Clock::Clock()
	: m_time( 0 )
	{ }

void Clock::reset()
	{ m_time = 0; }

void Clock::tick()
	{ ++m_time; }

unsigned Clock::time()
	{ return m_time; }
