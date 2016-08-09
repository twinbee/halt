
#ifndef halt_Document
#define halt_Document

#include <vector>
#include <string>

#include "View.h"

class TextEditor : public View
	{
	std::string docName;

	std::vector<std::string> text;
	std::vector<std::string>::iterator line;
	unsigned cursor;

public:
	TextEditor(std::string _name);

	std::string name();
	void sizeToFit();
	void highlight( unsigned lineNumber );

	View* click( point );
	void key( char );
	bool acceptsKey();

	void draw();
	};

#endif
