
#include "ProgramEditor.h"
#include "Memory.h"
#include "Color.h"
#include "source_highlight.h"
#include "graphics.h"
#include "utility.h"

using namespace std;

ProgramEditor::ProgramEditor()
	: View( size() ), m_program( NULL ), m_line( 0 ), m_cursor( 0 )
	{
	initSourceHighlight();
	}

Program* ProgramEditor::program()
	{
	return m_program;
	}

void ProgramEditor::program( Program* p )
	{
	m_program = p;

	m_line = 1;
	m_cursor = 0;

	sizeToFit();
	}

void ProgramEditor::sizeToFit()
	{
	bounds.w = m_program->lineLength() * fontWidth + 2 * margin;
	bounds.h = m_program->lineCount() * ( fontHeight + leading ) - leading + 2 * margin;
	
	g_mem.clear();
	g_mem << *m_program;
	}

void ProgramEditor::highlight( unsigned lineNumber )
	{
	rect (
		point( 0, (lineNumber - 1) * (fontHeight + leading) + margin - leading / 2 ),
		size( bounds.w, fontHeight + leading )
		).fill();
	}

void ProgramEditor::mark( unsigned lineNumber )
	{
	rect (
		point( 0, (lineNumber - 1) * (fontHeight + leading) + margin - leading / 2 ),
		size( margin / 2, fontHeight + leading )
		).fill();
	}

View* ProgramEditor::click( point p )
	{
	parent->bringSubViewToFront( this );
	
	m_line = ( p.y - margin ) / ( fontHeight + leading ) + 1;
	clamp <unsigned> ( m_line, 1, m_program->lineCount() );
	
	m_cursor = ( p.x - margin + fontWidth / 2 ) / fontWidth;
	clamp <unsigned> ( m_cursor, 0, m_program->line( m_line ).source().length());

	glutPostRedisplay();
	
	return this;
	}

void ProgramEditor::drag( int dx, int dy )
	{
	bounds.x += dx;
	bounds.y += dy;
	glutPostRedisplay();
	}

void ProgramEditor::key( char c )
	{
	string text = m_program->line( m_line ).source();
	string before = text.substr( 0, m_cursor );
	string after = text.substr( m_cursor, text.length() - m_cursor );

	switch ( c )
		{
		case upKey:
			if ( m_line > 1 )
				{
				--m_line;
				clamp <unsigned> ( m_cursor, 0, m_program->line( m_line ).source().length());
				}
			break;

		case downKey:
			if ( m_line < m_program->lineCount())
				{
				++m_line;
				clamp <unsigned> ( m_cursor, 0, m_program->line( m_line ).source().length());
				}
			break;

		case leftKey:
			if ( m_cursor > 0 )
				--m_cursor;
			break;

		case rightKey:
			if ( m_cursor < text.length())
				++m_cursor;
			break;		

		case homeKey:
			m_cursor = 0;
			break;

		case endKey:
			m_cursor = text.length();
			break;

		case returnKey:
			{
			m_program->insert( m_line++, Sequence( before ));
			m_program->line( m_line ) = Sequence( after );
			
			m_cursor = 0;

			sizeToFit();
			break;
			}

		case backspaceKey:
			if ( m_cursor == 0 )
				{
				if ( m_line > 1 )
					{
					string prevText = m_program->line( --m_line ).source();
					m_cursor = prevText.length();
					m_program->line( m_line ) = Sequence( prevText + text );
					m_program->remove( m_line + 1 );
					sizeToFit();
					}
				}
			else
				{
				m_program->line( m_line ) =
					Sequence( before.substr( 0, before.length() - 1 ) + after );
				
				--m_cursor;
				sizeToFit();
				}
			break;

		case deleteKey:
			if ( m_cursor == text.length())
				{ // merge text
				if ( m_line != m_program->lineCount())
					{
					string nextText = m_program->line( m_line + 1 ).source();
					m_program->line( m_line ) = Sequence( text + nextText );
					m_program->remove( m_line + 1 );
					sizeToFit();
					}
				}
			else // delete character
				{
				m_program->line( m_line ) =
					Sequence( before + after.substr( 1, after.length() - 1 ));

				sizeToFit();
				}
			break;
		
		default:
			m_program->line( m_line ) = Sequence( before + c + after );
			++m_cursor;
			sizeToFit();
		}
	
	clamp <unsigned> ( m_cursor, 0, m_program->line( m_line ).source().length());

	glutPostRedisplay();
	}

void ProgramEditor::draw()
	{
	rect r = localRect();

	glColor4f( 0.1, 0.1, 0.1, 0.8 );
	r.fill();

	if ( m_line )
		{
		int x = m_cursor * fontWidth + margin;
		int y = (m_line - 1) * (fontHeight + leading) + margin - leading / 2;

		glColor4f( 0.1, 0.1, 0.1, 0.5 );
		highlight( m_line );

		// draw cursor
		glColor4f( 1, 1, 1, 0.25 );
		glBegin( GL_LINES );
			glVertex2i( x, y );
			glVertex2i( x, y + fontHeight + leading );
		glEnd();

		glPointSize( 1 );
		glColor3f( 1, 1, 1 );
		glBegin( GL_POINTS );
			glVertex2i( x - 1, y );
			glVertex2i( x, y + 1 );
			glVertex2i( x + 1, y );

			y += fontHeight + leading - 1;

			glVertex2i( x - 1, y );
			glVertex2i( x, y - 1 );
			glVertex2i( x + 1, y );
		glEnd();
		}

	int y = margin;

	for ( unsigned i = 1; i <= m_program->lineCount(); ++i )
		{
		const Sequence& line = m_program->line(i);
		if ( ! line.success())
			{
			Color::palette["error"].set();
			mark( i );
			}

		
		drawSourceCode( line.tokens(), point( margin, y ), 1.0 );
		y += fontHeight + leading;
		}

	glColor3f( 0, 0, 0 );
	r.stroke();
	}

bool ProgramEditor::acceptsKey()
	{ return true; }
