
#ifndef halt_EA
#define halt_EA

// Writing code to handle all combinations of addressing modes for all
// instructions, both at translation-time and run-time, would be cumbersome
// and error prone. EA allows us to build or manipulate operands,
// while Reference lets us use them. Reference is an EA in action.

struct EA
	{
	enum Mode
		{
		DataDirect,			// d?
		AddressDirect,		// a?
		AddressIndirect,	// (a?)
		PostIncrement,		// (a?)+
		PreDecrement,		// -(a?)
		Absolute,			// (label) or (hex:100)
		Immediate,			// 1234
	//----------------------//
		Unknown
		};

	enum Category
		{
		data = 8,
		memory = 4,
		control = 2,
		alterable = 1
		};

	Mode mode;
	short reg;

	EA( short _mode = Unknown, short _reg = 0 );
	bool inCategory( short flags ); // bit-or multiple categories together to test at once

private:
	static short category[ Unknown + 1 ];
	};

#endif
