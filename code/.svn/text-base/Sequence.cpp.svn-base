
#include <iomanip>
#include <map>

#include "Sequence.h"
#include "Lexer.h"
#include "BitField.h"

using namespace std;

Sequence::Sequence( string sourceText )
	: m_type( Word::Unknown ), m_source( sourceText )
	{
	static Lexer lex;
		
	Token t;
	 
	lex << sourceText;

	if (sourceText != string("") ) //Matt 2-18-06
		while ( lex >> t )
			{
			m_tokens.push_back( t );

			if ( ! lex.success() )
				m_errors.push_back( lex.error() );
			}
	
	translate();
	}

bool Sequence::success() const
	{ return m_errors.empty(); }

void Sequence::dump( ostream& out ) const
	{
	if ( success() )
		{
		out << hex << setfill('0');

		for ( vector<short>::const_iterator i = m_code.begin(); i != m_code.end(); ++i )
			out << ' ' << setw(4) << *i;
		}
	else
		for ( vector<string>::const_iterator i = m_errors.begin(); i != m_errors.end(); ++i )
			out << *i << endl;
	}

Word::Type Sequence::type() const
	{ return m_type; }

const string& Sequence::source() const
	{ return m_source; }

const vector< Token >& Sequence::tokens() const
	{ return m_tokens; }

const vector< short >& Sequence::code() const
	{ return m_code; }


struct EncodeEntry
	{
	short signature;
	Object::Method assemble;

	EncodeEntry( short sig = 0, Object::Method ass = NULL )
		// defaults allow it to be placed in an STL container
		: signature( sig ), assemble( ass )
		{ }
	};

void Sequence::translate()
	{
	static map < string, EncodeEntry > table;
	static bool initialized = false;

	if ( ! initialized )
		{
		table["clr"]  = EncodeEntry( 0x4240, (Method) &Sequence::asm_clr  );
		table["move"] = EncodeEntry( 0x3000, (Method) &Sequence::asm_move );
		table["lea"]  = EncodeEntry( 0x41c0, (Method) &Sequence::asm_lea );

		table["add"]  = EncodeEntry( 0xd040, (Method) &Sequence::asm_add_sub );
		table["sub"]  = EncodeEntry( 0x9040, (Method) &Sequence::asm_add_sub );
		table["mul"]  = EncodeEntry( 0xc1c0, (Method) &Sequence::asm_mul_div );
		table["div"]  = EncodeEntry( 0x81c0, (Method) &Sequence::asm_mul_div );

		table["and"]  = EncodeEntry( 0xc040, (Method) &Sequence::asm_and );
		table["or"]   = EncodeEntry( 0x8040, (Method) &Sequence::asm_or  );
		table["eor"]  = EncodeEntry( 0xb140, (Method) &Sequence::asm_eor );
		table["not"]  = EncodeEntry( 0x4640, (Method) &Sequence::asm_not );
		
		table["nop"]  = EncodeEntry( 0x4e75, NULL );
		table["stop"] = EncodeEntry( 0x4e72, NULL );

		initialized = true;
		}

	// ------------------------------------------------------

	if ( m_tokens.empty() || m_tokens.begin()->is( Token::Comment ))
		return;	// blank lines are okay

	m_tokens.push_back( Token::EndLine );				// should end up here after parse
	token = m_tokens.begin();

	try {
		if ( token->is( Token::Label ))
			++token;

		if ( token->is( Token::DataType ))
			{
			++token;
			m_type = Word::Data;

// <matt> 2-10-05
			// foo datatype [] OR foo datatype [number] or foo datatype [] = n,n,n,...
			bool needToInitArray = false;
			int  numLast         = m_code.size();
			int  arraySize       = 0;

			if ( token->is(Token::OpenBracket) )
				{
				token++;

				if(token->is(Token::Number) )
					{
					arraySize = token->number;

					for (int i = 0; i < (arraySize); i++)
						{
						m_code.push_back(0);
						}

					token++;
					}
				else needToInitArray = true;

				token->mustBe(Token::CloseBracket);
				token++;
				}
			
			else //not an array
			{
				if (token->is(Token::Equal))
				{
				 ++token;
				 token->mustBe(Token::Number);
				 m_code.push_back(token->number);
				 ++token;
				}
				else m_code.push_back(0); //not an array, a single value
			}

			if (needToInitArray)
				{
				token->mustBe(Token::Equal);
				token++;
				token->mustBe(Token::Number); //change later for other datatypes
				m_code.push_back(token->number);
				token++;

				while (token->is(Token::Comma))
					{
					token++;
					token->mustBe(Token::Number);
					m_code.push_back(token->number);
					token++;
					}
				}

			if (arraySize != 0 && token->is(Token::Equal) )
				//the array has a literal number of existing elements
				//replace these by the initializing list
				{
				int i = numLast; //could be 1s err here
				token++;
				token->mustBe(Token::Number);
				m_code[i++] = token->number;
				token++;
				while ( i < m_code.size() && token->is(Token::Comma))
					{
					token++; //comma
					token->mustBe(Token::Number);
					m_code[i++] = token->number;
					token++;
					}
				}
// </matt> 2-10-05
			}

		else if ( token->is( Token::Opcode ))
			{
			const EncodeEntry& entry = table[token->text];
			++token;

			m_type = Word::Instruction;
			m_code.push_back(0); // reserve space for unfinished opcode
			opWord.bits = entry.signature;
			
			if ( entry.assemble != NULL )
				(*this.*(entry.assemble))();
			
			m_code[0] = opWord.bits;
			}
		else
			throw string("expected ") + token->typeString( Token::Opcode ) + " or "
									  + token->typeString( Token::DataType );

		if ( token->is( Token::Comment ))
			++token; // ignore it

		token->mustBe( Token::EndLine );
		}

	catch ( string message )
		{
		m_errors.push_back( string("<parse> ") + message );
		m_code.clear();
		}

	m_tokens.pop_back();	// remove the sentinal
	}

EA Sequence::parseOperand()
	{
	EA ea;

	if ( token->is( Token::DataReg ))
		{
		ea = EA( EA::DataDirect, token->number );
		++token;
		}
	else if ( token->is( Token::AddressReg ))
		{
		ea = EA( EA::AddressDirect, token->number );
		++token;
		}
	else if ( token->is( Token::OpenParen ))
		{
		(++token)->mustBe( Token::AddressReg );
		short reg = token->number;
		(++token)->mustBe( Token::CloseParen );
		if ((++token)->is( Token::Plus ))
			{
			++token;
			ea = EA( EA::PostIncrement, reg );
			}
		else
			ea = EA( EA::AddressIndirect, reg );
		}
	else if ( token->is( Token::Minus ))
		{
		if (( ++token )->is( Token::Number ))
			{
			ea = EA( EA::Immediate, 0 );
			m_code.push_back( -( token->number ));
			++token;
			}
		else
			{
			(token++)->mustBe( Token::OpenParen );
			(token++)->mustBe( Token::AddressReg );

			ea = EA( EA::PreDecrement, token->number );

			(token++)->mustBe( Token::CloseParen );
			}
		}
	else if ( token->is( Token::Label ))
		{
		ea = EA( EA::Absolute, 0 );
		m_code.push_back( 0 );
		++token;
		}
	else if ( token->is( Token::Number ))
		{	
		ea = EA( EA::Immediate, 0 );
		m_code.push_back( token->number );
		++token;
		}
	else
		throw string("weird operand");

	return ea;
	}

// -------------------------------------------------------

void Sequence::asm_clr()
	{
	EA dest = parseOperand();

	if ( !dest.inCategory( EA::data | EA::alterable ))
		throw string("destination must be alterable data");

	opWord.insert( dest.reg, 0, 3 );
	opWord.insert( dest.mode, 3, 3 );
	}

void Sequence::asm_move()
	{
	EA src = parseOperand();
	opWord.insert( src.reg, 0, 3 );
	opWord.insert( src.mode, 3, 3 );

	(token++)->mustBe( Token::Comma );

	EA dest = parseOperand();

	if ( !dest.inCategory( EA::data | EA::alterable ))
		throw string("destination must be alterable data");

	opWord.insert( dest.mode, 6, 3 );
	opWord.insert( dest.reg, 9, 3 );
	}

void Sequence::asm_lea()
	{
	EA src = parseOperand();
	if ( ! src.inCategory( EA::control ))
		throw string("source must be a control addressing mode");
	opWord.insert( src.reg, 0, 3 );
	opWord.insert( src.mode, 3, 3 );

	(token++)->mustBe( Token::Comma );

	EA dest = parseOperand();
	
	if ( ! dest.mode == EA::AddressDirect )
		throw string("destination must be an address register");

	opWord.insert( dest.mode, 6, 3 );
	opWord.insert( dest.reg, 9, 3 );
	}

void Sequence::asm_add_sub()
	{
	EA src = parseOperand();
	(token++)->mustBe( Token::Comma );
	EA dest = parseOperand();
	
	if ( dest.mode == EA::DataDirect )
		{
		opWord.insert( dest.mode, 9, 3 );
		opWord.insert( 0, 8 ); // op-mode
		opWord.insert( src.reg, 0, 3 );
		opWord.insert( src.mode, 3, 3 );
		}
	else if ( src.mode == EA::DataDirect )
		{
		opWord.insert( src.mode, 9, 3 );
		opWord.insert( 1, 8 ); // op-mode
		opWord.insert( dest.reg, 0, 3 );
		opWord.insert( dest.mode, 3, 3 );
		}
	else
		throw string("at least one operand must be a data register");
	}

void Sequence::asm_mul_div()
	{
	EA src = parseOperand();
	if ( ! src.inCategory( EA::data ))
		throw string("source must be data, not address");
	opWord.insert( src.reg, 0, 3 );
	opWord.insert( src.mode, 3, 3 );

	(token++)->mustBe( Token::Comma );

	EA dest = parseOperand();
	if ( ! dest.mode == EA::DataDirect )
		throw string("destination must be a data register");
	opWord.insert( dest.reg, 9, 3 );
	}

void Sequence::asm_and()
	{
	EA src = parseOperand();
	opWord.insert( src.reg, 0, 3 );
	opWord.insert( src.mode, 3, 3 );

	(token++)->mustBe( Token::Comma );

	EA dest = parseOperand();
	opWord.insert( dest.mode, 6, 3 );
	opWord.insert( dest.reg, 9, 3 );
	}

void Sequence::asm_or()
	{
	EA src = parseOperand();
	opWord.insert( src.reg, 0, 3 );
	opWord.insert( src.mode, 3, 3 );

	(token++)->mustBe( Token::Comma );

	EA dest = parseOperand();
	opWord.insert( dest.mode, 6, 3 );
	opWord.insert( dest.reg, 9, 3 );
	}

void Sequence::asm_eor()
	{
	EA src = parseOperand();
	if ( ! src.mode == EA::DataDirect )
		throw string("source must be a data register");
	opWord.insert( src.reg, 9, 3 );

	(token++)->mustBe( Token::Comma );

	EA dest = parseOperand();
	if ( ! dest.inCategory( EA::data | EA::alterable ))
		throw string("destination must be alterable data");
	opWord.insert( dest.reg, 0, 3 );
	opWord.insert( dest.mode, 3, 3 );
	}

void Sequence::asm_not()
	{
	EA dest = parseOperand();
	opWord.insert( dest.reg, 0, 3 );
	opWord.insert( dest.mode, 3, 3 );
	}
