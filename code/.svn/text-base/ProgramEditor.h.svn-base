
#ifndef halt_ProgramEditor
#define halt_ProgramEditor

#include "View.h"
#include "Program.h"

class ProgramEditor : public View
	{
	Program* m_program;
	unsigned m_line;
	unsigned m_cursor;
	
public:
	ProgramEditor();

	Program* program();
	void program( Program* );

	void sizeToFit();
	void highlight( unsigned lineNumber );
	void mark( unsigned lineNumber );

	View* click( point );
	void drag( int dx, int dy );
	void key( char );
	bool acceptsKey();

	void draw();
	};

#endif
