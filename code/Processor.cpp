
#include "Processor.h"
#include "Memory.h"
#include "Reference.h"

using namespace std;

Processor g_cpu;

Processor::Processor()
	{
	regs << Sequence("word[8]");
	reset();
	}

unsigned Processor::age( unsigned short address ) const
	{
	return regs.age( address );
	}

void Processor::reset()
	{
	pc = 0;
	ir.bits = 0;

	for ( int i = 0; i <= 7; ++i )
		{
		regs.write( i, Word::Data, 0 );
		a[i] = 0;
		}

	setFlags( 0 );
	}

bool Processor::smoothSailing()
	{ return m_running && ! m_error; }

void Processor::step()
	{
	m_running = true;
	m_error = false;

	try {
		ir = fetch();
		Method execute = decode();

		cout << mnemonic << endl;

		(*this.*execute)();
		}
	catch ( string message )
		{
		cerr << "<run> " << message << endl;
		m_error = true;
		}
	}

short Processor::fetch()
	{
	return g_mem.read( pc++, Word::Instruction );
	}

Object::Method Processor::decode()
	{
	struct DecodeEntry
		{
		string mnemonic;
		short signature;
		short mask;
		Method execute;
		};

	static const DecodeEntry table[] = {

		{ "clr",  0x4240, 0xffc0, (Method) &Processor::exec_clr },
		{ "move", 0x3000, 0xf000, (Method) &Processor::exec_move },
		{ "lea",  0x41c0, 0xf1c0, (Method) &Processor::exec_lea },

		{ "add",  0xd040, 0xf0c0, (Method) &Processor::exec_add },
		{ "sub",  0x9040, 0xf0c0, (Method) &Processor::exec_sub },
		{ "mul",  0xc1c0, 0xf1c0, (Method) &Processor::exec_mul },
		{ "div",  0x81c0, 0xf1c0, (Method) &Processor::exec_div },

		{ "and",  0xc040, 0xf0c0, (Method) &Processor::exec_and },
		{ "or",   0x8040, 0xf0c0, (Method) &Processor::exec_or },
		{ "eor",  0xb140, 0xf1c0, (Method) &Processor::exec_eor },
		{ "not",  0x4640, 0xffc0, (Method) &Processor::exec_not },

		{ "nop",  0x4e75, 0xffff, (Method) &Processor::exec_nop },
		{ "stop", 0x4e72, 0xffff, (Method) &Processor::exec_stop },

		{ "???", 0, 0, (Method) &Processor::exec_undefined }
		};

	DecodeEntry entry;
	unsigned index = 0;

	do
		entry = table[ index++ ];
	while (( ir.bits & entry.mask ) != entry.signature );
	
	mnemonic = entry.mnemonic;
	return entry.execute;
	}

void Processor::setFlags( short foo )
	{
	negative = foo < 0;
	zero = foo == 0;
	}

// -------------------------------------------------------

void Processor::exec_clr()
	{
	Reference dest( ir.extract( 3, 3 ), ir.extract( 0, 3 ));
	
	if ( !dest.inCategory( EA::data | EA::alterable ))
		throw string("operand must be alterable data");
	
	dest.write( 0 );
	setFlags( 0 );
	}

void Processor::exec_move()
	{
	Reference src( ir.extract( 3, 3 ), ir.extract( 0, 3 ));
	Reference dest( ir.extract( 6, 3 ), ir.extract( 9, 3 ));

	short result = src.read();
	dest.write( result );
	
	setFlags( result );
	}

void Processor::exec_lea()
	{
	Reference src( ir.extract( 3, 3 ), ir.extract( 0, 3 ));
	Reference dest( ir.extract( 6, 3 ), ir.extract( 9, 3 ));

	short result = src.read();
	dest.write( result );
	
	setFlags( result );
	}

void Processor::exec_add()
	{
	EA dataReg( EA::DataDirect, ir.extract( 9, 3 ));
	EA ea( ir.extract( 3, 3 ), ir.extract( 0, 3 ));

	bool eaIsDest = (bool) ir.extract( 8 );

	Reference src( eaIsDest ? dataReg : ea );
	Reference dest( eaIsDest ? ea : dataReg );
	
	if ( eaIsDest && !dest.inCategory( EA::alterable | EA::memory ))
		throw string("destination must be alterable memory");
	
	short result = src.read() + dest.read();

	dest.write( result );
	setFlags( result );
	}

void Processor::exec_sub()
	{
	EA dataReg( EA::DataDirect, ir.extract( 9, 3 ));
	EA ea( ir.extract( 3, 3 ), ir.extract( 0, 3 ));

	bool eaIsDest = (bool) ir.extract( 8 );

	Reference src( eaIsDest ? dataReg : ea );
	Reference dest( eaIsDest ? ea : dataReg );
	
	if ( eaIsDest && !dest.inCategory( EA::alterable | EA::memory ))
		throw string("destination must be alterable memory");
	
	short result = src.read() - dest.read();

	dest.write( result );
	setFlags( result );
	}

void Processor::exec_mul()
	{
	Reference src( ir.extract( 3, 3 ), ir.extract( 0, 3 ));
	Reference dest( EA::DataDirect, ir.extract( 9, 3 ));

	if ( !src.inCategory( EA::data ))
		throw string("source must be data");

	short result = src.read() * dest.read();

	dest.write( result );
	setFlags( result );
	}

void Processor::exec_div()
	{
	Reference src( ir.extract( 3, 3 ), ir.extract( 0, 3 ));
	Reference dest( EA::DataDirect, ir.extract( 9, 3 ));

	if ( !src.inCategory( EA::data ))
		throw string("source must be data");

	short result = dest.read() / src.read();

	dest.write( result );
	setFlags( result );
	}

void Processor::exec_and()
	{
	throw string("under construction");

//	Reference src( ir.extract( 3, 3 ), ir.extract( 0, 3 ));
//	Reference dest( ir.extract( 6, 3 ), ir.extract( 9, 3 ));
//
//	short result = src.read() & dest.read();
//
//	dest.write( result );
//	setFlags( result );
	}

void Processor::exec_or()
	{
	throw string("under construction");

//	Reference src( ir.extract( 3, 3 ), ir.extract( 0, 3 ));
//	Reference dest( ir.extract( 6, 3 ), ir.extract( 9, 3 ));
//
//	short result = src.read() | dest.read();
//
//	dest.write( result );
//	setFlags( result );
	}

void Processor::exec_eor()
	{
	throw string("under construction");

//	Reference src( ir.extract( 3, 3 ), ir.extract( 0, 3 ));
//	Reference dest( ir.extract( 6, 3 ), ir.extract( 9, 3 ));
//
//	short result = src.read() ^ dest.read();
//
//	dest.write( result );
//	setFlags( result );
	}

void Processor::exec_not()
	{
	throw string("under construction");

//	Reference dest( ir.extract( 3, 3 ), ir.extract( 0, 3 ));
//
//	short result = ~ dest.read();
//
//	dest.write( result );
//	setFlags( result );
	}

void Processor::exec_nop()
	{ /* do nothing! */ }

void Processor::exec_stop()
	{ m_running = false; }

void Processor::exec_undefined()
	{ throw string("weird opcode -- oops!"); }
