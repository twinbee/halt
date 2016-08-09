
#ifndef halt_Memory
#define halt_Memory

#include <vector>

#include "Sequence.h"
#include "Program.h"

class Memory
	{
	std::vector< Word > contents;

public:
	void clear();
	
	// append "things" to memory
	void operator << ( const Sequence& );
	void operator << ( const Program& );

	unsigned short size() const;
	unsigned age( unsigned short address ) const;

	const Word& peek( unsigned short address ) const;

	short read( unsigned short address, Word::Type ) const;
	void write( unsigned short address, Word::Type, short value );
	};

extern Memory g_mem;

#endif
