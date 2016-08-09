
#ifndef halt_TextField
#define halt_TextField

#include <string>

#include "Control.h"

class TextField : public Control
	{
	unsigned cursor;
	std::string value;

public:
	TextField( size );
	
	View* click( point );
	void key( char c );
	bool acceptsKey();

	std::string stringValue();
	void stringValue( std::string );

	void draw();
	};

#endif
