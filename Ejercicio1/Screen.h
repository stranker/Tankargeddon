#ifndef SCREEN_H
#define SCREEN_H
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Screen
{
public:
	virtual int	Run(RenderWindow &window) = 0;
	void setTextFormat(Text &text, Font &font, int charSize, string string)
	{
		text.setFont(font);
		text.setCharacterSize(charSize);
		text.setString(string);
	};
};
#endif // !SCREEN_H