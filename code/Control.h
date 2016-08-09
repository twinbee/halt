
#ifndef halt_control
#define halt_control

#include "View.h"
#include <string>

class Control : public View
	{
	Object* target;
	std::string action;

protected:
	bool m_enabled;
	std::string m_label;

public:
	Control( size, std::string label = "" );
	virtual ~Control();
	
	void connect( Object*, std::string message );
	void sendAction();

	std::string label();
	void label( std::string newLabel );

	bool enabled();
	void enabled( bool );
	};

#endif
