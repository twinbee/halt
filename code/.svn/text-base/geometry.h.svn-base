
#ifndef halt_geometry
#define halt_geometry

// screen coordinates
struct point
	{
	int x, y;
	point( int = 0, int = 0 );
	};

struct size
	{
	unsigned w, h;
	size( unsigned = 0, unsigned = 0 );
	};

struct rect
	{
	int x, y, w, h;

	rect( point, size );
	bool contains( point p );

	void stroke();
	void fill();
	};

#endif
