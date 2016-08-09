
#ifndef halt_Workspace
#define halt_Workspace

#include "View.h"

#include <vector>

#include <cmath>

class Workspace : public View
	{

public:
	Workspace( size );
	
	struct snowflake
	{ float px, py, rz, dx, dy;
	  snowflake(float x, float y, float r, float vx, float vy) :
		px(x), py(y), rz(r), dx(vx), dy(vy) {}
	};
	std::vector< snowflake > snowflakes;

	void draw();
	};

#endif
