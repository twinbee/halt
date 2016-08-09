
#include <string>
#include "Memory.h"

using namespace std;

Memory g_mem;

void Memory::clear()
	{ contents.clear(); }

void Memory::operator << ( const Sequence& seq )
	{
	for ( vector<short>::const_iterator i = seq.code().begin(); i != seq.code().end(); ++i )
		contents.push_back( Word( *i, seq.type()));
	}

void Memory::operator << ( const Program& prog )
	{
	prog.dump( cout );

	for ( vector<Sequence>::const_iterator i = prog.lines().begin(); i != prog.lines().end(); ++i )
		*this << *i;
	}

unsigned short Memory::size() const
	{ return contents.size(); }

unsigned Memory::age( unsigned short address ) const
	{
	if ( address >= contents.size())
		throw string("Memory::age, address out of bounds");

	return contents[ address ].age();
	}

const Word& Memory::peek( unsigned short address ) const
	{
	if ( address >= contents.size())
		throw string("Memory::peek, address out of bounds");

	return contents[ address ];
	}

short Memory::read( unsigned short address, Word::Type type ) const
	{
	if ( address >= contents.size())
		throw string("Memory::read, address out of bounds");

	return contents[ address ].read();
	}

void Memory::write( unsigned short address, Word::Type type, short newValue )
	{
	if ( address >= contents.size())
		throw string("Memory::write, address out of bounds");

	contents[ address ].write( newValue );
	}
