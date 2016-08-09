
#ifndef halt_Object
#define halt_Object

#include <string>
#include <map>

class Object
	{
public:
	typedef void ( Object::*Method )();
	typedef void ( Object::*Action )( Object* sender );

protected:
	std::map< std::string, Action > actions;

public:
	Object();
	virtual ~Object();

	bool doAction( std::string message, Object* sender = NULL );
	};

#endif
