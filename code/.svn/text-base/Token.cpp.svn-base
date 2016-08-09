
#include "Token.h"

using namespace std;

Token::Token( Type t )
	: type(t), position(0), number(0)
	{ }

string Token::typeString( int t ) const
	{
	static const string tokenNames[] =
		{
		"Klingon","end of line","comment",
		"command","data type","opcode",
		"data register","address register","number","label",
		"equal","plus","minus","comma",
		"open paren","close paren","open bracket","close bracket"
		};

	return tokenNames[( t == -1 ) ? type : t ];
	}

bool Token::is( Type t ) const
	{
	return type == t;
	}

void Token::mustBe( Type t ) const
	{
	if ( type != t )
		throw string("expected ") + typeString( t ) + ", not " + typeString();
	}
