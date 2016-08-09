
#ifndef halt_Clock
#define halt_Clock

// Make Clock a Control. Connect it to Processor. Indicator = Clock. Click to pause/resume.

class Clock
	{
	unsigned m_time;

public:
	Clock();

	void reset();
	void tick();
	unsigned time();
	};

extern Clock g_clock;

#endif
