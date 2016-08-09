
#include <fstream>

#include "TextEditor.h"
#include "text.h"
#include "graphics.h"
#include "utility.h"

using namespace std;

const string DocumentPath("/Users/merwin/Develop/HALT/programs/");

TextEditor::TextEditor(string _name)
	: View( size() ), docName(_name), cursor(0)
	{
	ifstream file(( DocumentPath + _name + ".s").c_str());

	if ( file.is_open() )
		{
		string s;
		getline( file, s );
		while ( ! file.eof() )
			{
			text.push_back( s );
			getline( file, s );
			}
		}

	if ( text.empty() )
		text.push_back("");

	line = text.begin();
	}

void TextEditor::sizeToFit()
	{
	bounds.w = 0;
	bounds.h = text.size() * ( fontHeight + leading ) - leading + 2 * margin;

	vector< string >::iterator i;
	for ( i = text.begin(); i != text.end(); ++i )
		{
		int lineLength = glutBitmapLength( font, (const unsigned char*) i->c_str());
		if ( lineLength > bounds.w )
			bounds.w = lineLength;
		}
	
	bounds.w += 2 * margin;
	
	// assume parent is an otherwise empty pane
	if ( parent != NULL )
		parent->setSize( size( bounds.w + 20, bounds.h + 20 ));
	}

string TextEditor::name()
	{ return docName; }

View* TextEditor::click( point p )
	{
	parent->bringSubViewToFront( this );
	
	unsigned lineNumber = ( p.y - margin ) / ( fontHeight + leading ) + 1;
	clamp <unsigned> ( lineNumber, 1, text.size() );
	line = text.begin() + ( lineNumber - 1 );
	
	cursor = ( p.x - margin ) / fontWidth;
	clamp <unsigned> ( cursor, 0, line->length() );

	glutPostRedisplay();
	
	return this;
	}

void TextEditor::key( char c )
	{
	switch ( c )
		{
		case upKey:
			if ( line != text.begin() )
				{
				--line;
				clamp <unsigned> ( cursor, 0, line->length() );
				}
			break;
		
		case downKey:
			if ( line != text.end() - 1 )
				{
				++line;
				clamp <unsigned> ( cursor, 0, line->length() );
				}
			break;
		
		case returnKey:
			{
			string before = line->substr( 0, cursor );
			string after = line->substr( cursor, line->length() - cursor );

			int lineNumber = line - text.begin() + 1;

			*line = after;
			text.insert( line, before );

			line = text.begin() + lineNumber;
			cursor = 0;

			sizeToFit();
			}
			break;

		case backspaceKey:
			if ( cursor == 0 )
				{
				if ( line != text.begin() )
					{
					--line;
					cursor = line->length();
					*line += *( line + 1 );
					text.erase( line + 1 );
					sizeToFit();
					}
				}
			else
				{
				*line = line->substr( 0, cursor - 1 ) + 
						line->substr( cursor, line->length() - cursor );
				--cursor;
				sizeToFit();
				}
			break;

		case deleteKey:
			if ( cursor == line->length() )
				{ // merge text
				if ( line != text.end() - 1 )
					{
					*line += *( line + 1 );
					text.erase( line + 1 );
					sizeToFit();
					}
				}
			else // delete character
				{
				*line = line->substr( 0, cursor ) + 
						line->substr( cursor + 1, line->length() - cursor - 1 );
				sizeToFit();
				}
			break;

		case leftKey:
			if ( cursor > 0  )
				--cursor;
			break;

		case rightKey:
			if ( cursor < line->length() )
				++cursor;
			break;

		case homeKey:
			cursor = 0;
			break;

		case endKey:
			cursor = line->length();
			break;

		default:
			// [ to-do : test if c is in allowed character set ]
			// insert character at cursor location
			*line = line->substr( 0, cursor ) + c +
					line->substr( cursor, line->length() - cursor );
			++cursor;
			sizeToFit();
		}
	
	if ( text.empty() )
		{
		text.push_back("");
		line = text.begin();
		cursor = 0;
		}

	glutPostRedisplay();
	}

bool TextEditor::acceptsKey()
	{ return true; }

void TextEditor::highlight( unsigned lineNumber )
	{
	rect (
		point( 0, lineNumber * (fontHeight + leading) + margin - leading / 2 ),
		size( bounds.w, fontHeight + leading )
		).fill();
	}

void TextEditor::draw()
	{
	rect r = localRect();

	glColor4f( 1, 1, 1, 0.8 );
	r.fill();

	if ( line != text.end() )
		{
		glColor4f( 0.2, 0.3, 0.5, 0.1 );
		highlight( line - text.begin() );

		// draw cursor
		glColor4f( 0.2, 0.3, 0.5, 0.75 );
		glBegin( GL_LINES );
			int x = cursor * fontWidth + margin;
			int y = ( line - text.begin() ) * (fontHeight + leading) + margin;
			glVertex2i( x, y );
			glVertex2i( x, y + fontHeight );
		glEnd();
		}

	int y = margin;

	glColor3f( 0, 0, 0 );
	vector< string >::iterator i;
	for ( i = text.begin(); i != text.end(); ++i )
		{
		drawText( *i, point( margin, y ));
		y += fontHeight + leading;
		}

	r.stroke();
	}
