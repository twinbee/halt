
#include "Workspace.h"
#include "graphics.h"

Workspace::Workspace( size s )
	: View( s )
	{ }

void Workspace::draw()
	{
	beginLocal();
	
	glBegin( GL_QUADS );
		glColor3f( 0.8, 0.9, 1 );
		glVertex2i( 0, 0 );

		glColor3f( 0.7, 0.8, 1 );
		glVertex2i( bounds.w, 0 );

		glColor3f( 0.2, 0.3, 0.5 );
		glVertex2i( bounds.w, bounds.h );

		glColor3f( 0.1, 0.2, 0.4 );
		glVertex2i( 0, bounds.h );
	glEnd();

	endLocal();

	//beginLocal();
	////<matt>: "pretty prettier snowflakes" 2-18-06
	//const float SFSIZE = 6.0;
	//  glColor4f( 1.0, 1.0, 1.0, 0.15 );
	//if (snowflakes.size() == 0) //how many snowflakes?
	//// 0 is not snowing, 20 enough, 50 too much, 200 blizzard
	//{ for (int i = 0; i <= 50; i++)
	//  snowflakes.push_back
	//  (snowflake(rand()%bounds.w, rand()%bounds.h, rand()%360, ((rand()%2)-1.0)/5.0, ((rand()%2)-1.0)/5.0));
	//}
	//for (int i = 0; i < snowflakes.size(); i++)
	//{
	// snowflakes[i].rz += SFSIZE;
	// if (snowflakes[i].rz >= 360.0) snowflakes[i].rz = 0.0;

	// snowflakes[i].px += 0.5 + snowflakes[i].dx;
	// if (snowflakes[i].px >= bounds.w) snowflakes[i].px = 0.0;

	// snowflakes[i].py += 0.5 + snowflakes[i].dy;
	// if (snowflakes[i].py >= bounds.h) snowflakes[i].py = 0.0;
	// 
	// glPushMatrix();
	// glTranslatef(snowflakes[i].px, snowflakes[i].py, 0.0);
	// //which is pretier? I think the 2nd one is
	// //glRotatef(snowflakes[i].rz, 0.0, 0.0, 1.0);
	// glRotatef(snowflakes[i].rz, 1.0, 0.0, 1.0);
	// glBegin( GL_TRIANGLES );
	//  glVertex2f( - SFSIZE, + SFSIZE);
	//  glVertex2f( 0.0,  - SFSIZE);
	//  glVertex2f( + SFSIZE, + SFSIZE);
	// glEnd();
	// glTranslatef(0.0, SFSIZE/2.0, 0.0);
	// glBegin( GL_TRIANGLES );
	//  glVertex2f( + SFSIZE, - SFSIZE);
	//  glVertex2f( 0.0,  + SFSIZE);
	//  glVertex2f( - SFSIZE, - SFSIZE);
	// glEnd();
	// glPopMatrix();
	//}
	////</matt> snowflakes
	//endLocal();

	drawSubViews();
	}
