
#ifndef halt_Token
#define halt_Token

#include <string>

struct Token
	{
	enum Type
		{
		Unknown, EndLine, Comment,
		Command, DataType, Opcode,
		DataReg, AddressReg, Number, Label,
		Equal, Plus, Minus, Comma,
		OpenParen, CloseParen, OpenBracket, CloseBracket
		};

	Type type;
	unsigned position;
	std::string text;
	int number;

	Token( Type = Unknown );

	bool is( Type ) const;
	void mustBe( Type ) const;
	std::string typeString( int t = -1 ) const;
	};

#endif
