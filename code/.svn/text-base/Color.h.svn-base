
#ifndef halt_color
#define halt_color

#include <map>
#include <string>

class Color
	{
public:
	static std::map< std::string, Color > palette;

protected:
	float red, green, blue;
	float alpha;

	Color( float r, float g, float b, float a = 1.0 );

public:
	Color();
	Color( float hue );

	void set();

	float value();
	Color scaleValue( float v );
	Color withAlpha( float a );
	};

#endif
