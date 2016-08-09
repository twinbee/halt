
#include <iostream>

#include "Object.h"

using namespace std;

Object::Object()
	{ }

Object::~Object()
	{ }

bool Object::doAction( string message, Object* sender )
	{
	map< string, Action >::iterator found = actions.find( message );

	if ( found != actions.end() )
		{
		Action action = found->second;
		(*this.*action)( sender );
		return true;
		}
	else
		{
		clog << "huh?" << endl;
		return false;
		}
	}
