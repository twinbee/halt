//////////////////////////////////////////////////////////
// Bitfield allows packing and unpacking of bits 
//  Each bitfield object holds sizeof short * 8 
//  16 bits on most systems
// (be careful, may not be portable)

#ifndef halt_BitField
#define halt_BitField

struct BitField
	{
	short bits;
	
	BitField( short integer = 0 );
	
	void insert( short newValue, unsigned pos, unsigned numBits = 1 );
	short extract( unsigned pos, unsigned numBits = 1 );
	short extend( unsigned pos, unsigned numBits );
	};

#endif
