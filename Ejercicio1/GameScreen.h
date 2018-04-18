#ifndef GAMESCREEN_H
#define GAMESCREEN_H


#include "Screen.h"
class GameScreen :
	public Screen
{
public:
	virtual int Run(RenderWindow &window);
};

#endif // !GAMESCREEN_H