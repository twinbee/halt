
#include "Color.h"
#include "graphics.h"

std::map< std::string, Color > Color::palette;

Color::Color()
	: red(0.5), green(0.5), blue(0.5), alpha(1.0)
	{ }

Color::Color( float r, float g, float b, float a )
	: red(r), green(g), blue(b), alpha(a)
	{ }

Color::Color( float hue )
	:   red( cos(( hue - 0.000 ) * 2 * M_PI ) / 2 + 0.5 ),
	  green( cos(( hue - 0.333 ) * 2 * M_PI ) / 2 + 0.5 ),
	   blue( cos(( hue - 0.667 ) * 2 * M_PI ) / 2 + 0.5 ),
	  alpha( 1.0 )
	{ }

void Color::set()
	{
	glColor4f( red, green, blue, alpha );
	}

float Color::value()
	{ return ( red + green + blue ) / 3; }

Color Color::scaleValue( float v )
	{
	return Color( red * v, green * v, blue * v, alpha );
	}

Color Color::withAlpha( float a )
	{
	return Color( red, green, blue, a );
	}
