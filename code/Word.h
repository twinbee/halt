
#ifndef halt_Word
#define halt_Word

class Word
	{
public:
	enum Type { Unknown, Data, Address, Instruction };

protected:	
	short m_value;
	Type m_type;
	mutable unsigned m_timestamp;

public:
	Word( short v = 0, Type t = Unknown );

	short read() const;
	void write( short );
	
	unsigned age() const;
	Type type() const;
	short peek() const;
	void touch();
	};

#endif
