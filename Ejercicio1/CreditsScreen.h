#ifndef CREDITSSCREEN_H
#define CREDITSSCREEN_H

#include "Screen.h"
class CreditsScreen :
	public Screen
{
public:
	virtual int Run(RenderWindow &window);
};

#endif // !CREDITSSCREEN_H