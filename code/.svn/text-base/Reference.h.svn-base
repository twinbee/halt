
#ifndef Reference_Interface
#define Reference_Interface

#include "EA.h"

class Reference : public EA
	{
	unsigned short address;
	short value;

	bool hasAddress;
	bool hasValue;
	bool dirty;

	void init();

public:
	Reference( short _mode = EA::Unknown, short _reg = 0 );
	Reference( EA );

	short getAddress();
	short read();
	void write( short newValue );
	};

#endif
