#ifndef MENUSCREEN_H
#define MENUSCREEN_H


#include "Screen.h"
class MenuScreen :
	public Screen
{
public:
	virtual int Run(RenderWindow &window);
};

#endif // !MENUSCREEN_H