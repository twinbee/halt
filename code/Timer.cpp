
#include "Timer.h"
#include "Color.h"
#include "graphics.h"
#include "utility.h"

std::vector<Timer*> Timer::timers;
Timer g_timer(1.0);

Timer::Timer( float hertz )
	: Control( size( 30, 30 )), timerID( timers.size()), m_ticks( 0 )
	{
	timers.push_back( this );
	rate( hertz );
	}

float Timer::rate()
	{
	return 1000.0 / m_delay;
	}

void Timer::rate( float hertz )
	{
	clamp<float>( hertz, 1.0, 1000.0 );
	m_delay = static_cast <unsigned> ( 1000.0 / hertz );
	}

void Timer::tick()
	{ ++m_ticks; }

unsigned Timer::ticks()
	{ return m_ticks; }

void Timer::reset()
	{
	enabled( false );
	m_ticks = 0;
	}

void Timer::start()
	{
	enabled( true );
	glutTimerFunc( 0, Timer::trigger, timerID );
	}

void Timer::stop()
	{
	enabled( false );
	}

void Timer::trigger( int id )
	{
	Timer& timer = *(timers[id]);
	if ( timer.enabled())
		{
		timer.sendAction();
		++timer.m_ticks;
		glutTimerFunc( timer.m_delay, Timer::trigger, id );
		}
	}

View* Timer::click( point p )
	{
	enabled() ? stop() : start();
	return this;
	}

void Timer::draw()
	{
	glBegin( GL_QUADS );
		// top
		Color(0.333).scaleValue( 0.75 ).withAlpha( 0.75 ).set();
		glVertex2i( 0, 0 );
		glVertex2i( bounds.w, 0 );

		// bottom
		Color(0.333).scaleValue( 0.25 ).withAlpha( 0.5 ).set();
		glVertex2i( bounds.w, bounds.h );
		glVertex2i( 0, bounds.h );
	glEnd();

	if ( enabled())
		{
		// draw pulsing Pause symbol
		Color(0.333).scaleValue( m_ticks & 1 ? 0.8 : 1.0 ).withAlpha(0.5).set();
		glBegin( GL_QUADS );
			glVertex2i( 7, 7 );
			glVertex2i( 13, 7 );
			glVertex2i( 13, 23 );
			glVertex2i( 7, 23 );
			// prime numbers are good!
			glVertex2i( 17, 7 );
			glVertex2i( 23, 7 );
			glVertex2i( 23, 23 );
			glVertex2i( 17, 23 );
		glEnd();
		}
	else
		{
		// draw Run symbol
		Color(0.333).withAlpha(0.5).set();
		glBegin( GL_TRIANGLES );
			glVertex2i( 8, 5 );
			glVertex2i( 23, 15 );
			glVertex2i( 8, 24 );
		glEnd();

		Color(0.333).set();
		glEnable( GL_LINE_SMOOTH );
		glBegin( GL_LINE_LOOP );
			glVertex2i( 8, 5 );
			glVertex2i( 23, 15 );
			glVertex2i( 8, 24 );
		glEnd();
		glDisable( GL_LINE_SMOOTH );
		}

	glColor4f( 0, 0, 0, 0.5 );
	localRect().stroke();
	}
