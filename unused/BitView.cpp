
#include "BitView.h"
#include "graphics.h"

BitView::BitView( unsigned bits, Color c )
	: View( size(( 1 << bits ) + 2, bits + 2 )), m_bits( bits ), m_color( c )
	{ }

void BitView::draw()
	{
	glColor3f( 0, 0, 0 );
	localRect().stroke();

	glBegin( GL_POINTS );
	for ( unsigned n = 0; n < ( 1U << m_bits ); ++n )
		for ( unsigned b = 0; b < m_bits; ++b )
			{
			m_color.scaleValue((( n >> b ) bitand 1 ) ? 0.6 : 0.4 ).set();
			glVertex2i( n + 1, m_bits - b );
			}
	glEnd();
	}
