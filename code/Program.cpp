
#include <fstream>

#include "Program.h"

using namespace std;

const string DocumentPath("/Users/merwin/Develop/halt/examples/");

Program::Program(string name)
	: m_name(name)
	{
	if ( ! m_name.empty())
		{
		ifstream file(( DocumentPath + m_name + ".s").c_str());

		if ( file.is_open() )
			{
			string s;
			getline( file, s );
			while ( ! file.eof() )
				{
				m_lines.push_back( Sequence( s ));
				getline( file, s );
				}
			}
		}
	
	if ( m_lines.empty())
		// allow editing of new or empty files
		m_lines.push_back( Sequence ("") );
	}

const string& Program::name() const
	{ return m_name; }

unsigned Program::lineCount() const
	{ return m_lines.size(); }

unsigned Program::lineLength() const
	{
	int max = 0;
	for ( vector<Sequence>::const_iterator i = m_lines.begin(); i != m_lines.end(); ++i )
		{
		int len = i->source().length();
		if ( len > max )
			max = len;
		}
	return max;
	}

const vector<Sequence>& Program::lines() const
	{ return m_lines; }

Sequence& Program::line( unsigned n )
	{
	if ( n < 1 || n > m_lines.size())
		throw string("line number out of range");
	
	return m_lines[ n - 1 ];
	}

void Program::insert( unsigned n, Sequence seq )
	{
	if ( n < 1 || n > m_lines.size())
		throw string("line number out of range");

	m_lines.insert( m_lines.begin() + ( n - 1 ), seq );
	}

void Program::remove( unsigned n )
	{
	if ( n < 1 || n > m_lines.size())
		throw string("line number out of range");
	
	m_lines.erase( m_lines.begin() + ( n - 1 ));
	}

void Program::dump( ostream& out ) const
	{
	out << endl;
	unsigned longest = lineLength();

	for ( vector<Sequence>::const_iterator i = m_lines.begin(); i != m_lines.end(); ++i )
		{
		out << i->source() << string( longest - i->source().length() + 1,' ') << '|';

		if ( i->success() )
			{
			i->dump( out );		// machine code
			out << endl;
			}
		else
			{
			out << "\n\n";
			i->dump( out );		// error messages
			out << endl;
			}
		}
	}
