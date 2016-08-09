
#ifndef halt_Lexer
#define halt_Lexer

#include <string>
#include <sstream>
#include <set>

#include "Token.h"

class Lexer
	{
	std::istringstream line;
	std::string errorMsg;

	Token token;
	Token next();
	void getNumber( std::string digits );

	std::set< std::string > opcodes;
	std::set< std::string > dataTypes;

public:
//	std::set< std::string > commands;

	Lexer();

	void operator << ( std::string );	// sets line of source text
	bool operator >> ( Token& );		// returns false if no more tokens

	bool success();
	std::string error();
	};

#endif
