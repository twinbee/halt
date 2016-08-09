
#ifndef halt_text
#define halt_text

#include <string>

#include "geometry.h"

// typography
extern void* font;
extern const int fontWidth;
extern const int fontHeight;
extern const int margin;
extern const int leading;

void drawText( std::string, point );

#endif
