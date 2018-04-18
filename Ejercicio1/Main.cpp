#include "Screen.h"
#include "MenuScreen.h"
#include "GameScreen.h"
#include "CreditsScreen.h"

int main()
{
	RenderWindow window(VideoMode(800, 600), "TANKARGEDDON");
	vector<Screen*> screens;
	int screen = 0;
	MenuScreen menuScreen;
	screens.push_back(&menuScreen);
	CreditsScreen creditsScreen;
	screens.push_back(&creditsScreen);
	GameScreen gameScreen;
	screens.push_back(&gameScreen);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// CIERRA LA VENTANA
			if ((event.type == Event::Closed) || (event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape))
				window.close();
		}
		if (screen >= 0)
		{
			screen = screens[screen]->Run(window);
		}
	}

	return 0;
}

