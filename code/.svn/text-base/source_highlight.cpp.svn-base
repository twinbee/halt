
#include "source_highlight.h"
#include "graphics.h"
#include "Color.h"

using namespace std;

void initSourceHighlight()
	{
	Color::palette["Klingon"]			= Color::palette["error"];

	Color::palette["opcode"]			= Color::palette["code"];

	Color::palette["data register"]		= Color::palette["data"];
	Color::palette["number"]			= Color::palette["data"];
	Color::palette["data type"]			= Color::palette["data"];

	Color::palette["address register"]	= Color::palette["address"];
	Color::palette["label"]				= Color::palette["address"];
	}

void drawSourceCode( const vector<Token>& tokens, point p, float intensity )
	{
	for ( vector<Token>::const_iterator t = tokens.begin(); t != tokens.end(); ++t )
		{
		Color::palette[ t->typeString() ].scaleValue( intensity ).set();
		drawText( t->text, point( p.x + t->position * fontWidth, p.y ));
		}
	}
