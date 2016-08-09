
#include <string>

#include "EA.h"

short EA::category[] = {
//-----------------------------------------------------------
	data |    0   |    0    | alterable,	// DataDirect
	  0  |    0   |    0    | alterable,	// AddressDirect
	data | memory | control | alterable,	// AddressIndirect
	data | memory |    0    | alterable,	// PostIncrement
	data | memory |    0    | alterable,	// PreDecrement
	data | memory | control | alterable,	// Absolute
	data | memory |    0    |     0,     	// Immediate
//-----------------------------------------------------------
	  0  |    0   |    0    |     0			// Unknown
	};

EA::EA( short _mode, short _reg )
	: mode( static_cast<EA::Mode>(_mode )), reg(_reg )
	{
	if ( _mode > Unknown )			// wow, that's deep!
		throw std::string("weird EA");
	}

bool EA::inCategory( short flags )
	{
	return ( category[ mode ] & flags ) == flags;
	}
