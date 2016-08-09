// Matt's Stuff I want Feb 19, 2006:
//  BRA, BSR, CMP Compare, JMP, JSR, LEA, 
//  NOP, ROL, ROR, RTS, TRAP

// datatypes: byte, char (masqueraded byte), long
 // (can be delayed indefinitely, req changes to the stack)

#include "Lexer.h"

using namespace std;

Lexer::Lexer()
	{
	opcodes.insert("clr");
	opcodes.insert("move");
	opcodes.insert("lea");

//	opcodes.insert("cmp");
	opcodes.insert("add");
	opcodes.insert("sub");
	opcodes.insert("mul");
	opcodes.insert("div");

	opcodes.insert("and");
	opcodes.insert("or");
	opcodes.insert("eor");
	opcodes.insert("not");
	
	opcodes.insert("nop");
	opcodes.insert("stop");
	
//	opcodes.insert("bra");
//	opcodes.insert("beq");
//	opcodes.insert("bne");
	
	dataTypes.insert("word");
	// No more data types for the pure 16-bit version!
	}

void Lexer::operator << ( string s )
	{
	line.clear();
	line.str( s );
	line.seekg( 0 );

	errorMsg.clear();

	token = Token();
	}

bool Lexer::operator >> ( Token& t )
	{
	errorMsg.clear();

	try {
		t = next();
		return !t.is( Token::EndLine );
		}
	catch ( string message )
		{
		while ( isalnum( line.peek() ))
			token.text += line.get();

		t = token;

		errorMsg = string("<lex> ") + message;
		return true;
		}
	}

bool Lexer::success()
	{ return errorMsg.empty(); }

string Lexer::error()
	{ return errorMsg; }

void Lexer::getNumber( string digits )
	{
	// convert digits of any positional number system to bits

	unsigned startLength = token.text.length();
	
	while ( true )	
		{
		char c = line.peek();
		unsigned pos = digits.find(c);
		
		if ( pos == string::npos )
			break;
		
		token.number = token.number * digits.length() + pos;
		token.text += line.get();
		}

	if ( token.text.length() == startLength )
		throw string("expected digit from the set: ") + digits;
	
	if ( isalnum( line.peek() ))
		throw string("never trust a crowded number");
	}

Token Lexer::next()
	{
	token = Token::Unknown;

	line >> ws;

	if ( line.eof())
		{
		token.type = Token::EndLine;
		return token;
		}

	token.position = line.tellg();

	while ( isalpha( line.peek()))	// build alpha string
		token.text += line.get();
	
	if ( token.text == "d" ) // data register
		{
		getNumber("0123456789");

		if ( token.number < 0 || token.number > 7 )
			throw string("data registers range from 0 to 7");

		token.type = Token::DataReg;
		}
	else if ( token.text == "a" ) // address register
		{
		getNumber("0123456789");

		if ( token.number < 0 || token.number > 6 )
			throw string("address registers range from 0 to 6");

		token.type = Token::AddressReg;
		}
	else if ( !token.text.empty() )	// command, opcode, or number base
		{
/*		if (( commands.find( token.text )) != commands.end() )
			token.type = Token::Command;
		else*/ if (( opcodes.find( token.text )) != opcodes.end() )
			token.type = Token::Opcode;
		else if (( dataTypes.find( token.text )) != dataTypes.end() )
			token.type = Token::DataType;
		else if ( token.text == "hex" || token.text == "bin" || token.text == "dec" )
			{
			if ( line.peek() == ':' )	// enforce separator
				token.text += line.get();
			else
				throw string("separate number base from digits with ':'");

			if ( token.text == "hex:" )						// hexadecimal
				getNumber("0123456789abcdef");
			else if ( token.text == "bin:" )				// binary
				getNumber("01");
			else if ( token.text == "dec:" )				// decimal
				getNumber("0123456789");

			token.type = Token::Number;
			}
		else
			token.type = Token::Label;
		}
	else if ( isdigit( line.peek() ))		// decimal (default # base)
		{
		getNumber("0123456789");
		token.type = Token::Number;
		}
	else
		{
		char c = line.get();

		if ( line.eof() )
			{
			token.text = "";
			token.type = Token::EndLine;
			}
		else
			{
			token.text = c;

			switch ( c )
				{
				case ';':
					{
					string restOfLine;
					getline( line, restOfLine );
					token.text += restOfLine;
					token.type = Token::Comment;
					break;
					}
				case '+':
					token.type = Token::Plus;
					break;
				case '-':
					token.type = Token::Minus;
					break;
				case ',':
					token.type = Token::Comma;
					break;
				case '(':
					token.type = Token::OpenParen;
					break;
				case ')':
					token.type = Token::CloseParen;
					break;
				case '[':
					token.type = Token::OpenBracket;
					break;
				case ']':
					token.type = Token::CloseBracket;
					break;
				case '=':
					token.type = Token::Equal;
					break;
				default:
					throw token.text + " is a strange character";
				}
			}
		}

	return token;
	}
