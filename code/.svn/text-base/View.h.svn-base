
#ifndef halt_View
#define halt_View

#include <list>

#include "Object.h"
#include "geometry.h"

enum {
	nullKey, enterKey, returnKey,
	leftKey, rightKey, upKey, downKey,
	homeKey, endKey,
	backspaceKey, deleteKey
	};

class View : public Object
	{
protected:
	rect bounds;	// relative to parent View
	View* parent;
	std::list<View*> subViews;

	View* clickSubViews( point );
	void drawSubViews();

	rect localRect();

public:
	View( size );
	virtual ~View();

	void setParent( View* );
	void addSubView( View*, point );
	void bringSubViewToFront( View* );

	point screenPosition();	// relative to window
	rect boundsRect();		// relative to parent

	virtual bool contains( point );

	size getSize();
	void setSize( size );
	
	point getPosition();
	void setPosition( point );

	virtual void beginLocal();	// setup drawing coordinates
	void endLocal();

	// event handling
	virtual View* click( point );
	virtual void drag( int dx, int dy );
	virtual void release();
	virtual void key( char c );
	virtual bool acceptsKey();

	virtual void draw() = 0;
	};

#endif
