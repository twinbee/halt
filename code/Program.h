
#ifndef halt_Program
#define halt_Program

#include <vector>
#include <string>
#include <iostream>

#include "Sequence.h"

class Program
	{
	std::string m_name;
	std::vector<Sequence> m_lines;

public:
	Program( std::string name = "");
	
	const std::string& name() const;

	unsigned lineCount() const;
	unsigned lineLength() const;

	const std::vector<Sequence>& lines() const;

	// editing
	Sequence& line( unsigned n );
	void insert( unsigned n, Sequence );
	void remove( unsigned n );
	
	void dump( std::ostream& ) const;
	};

#endif
