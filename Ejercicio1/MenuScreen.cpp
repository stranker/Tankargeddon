#include "MenuScreen.h"

int MenuScreen::Run(RenderWindow & window)
{
	Font guiFont;
	guiFont.loadFromFile("8-Bit Madness.ttf");
	Clock clockLoop, clockGame;
	clockLoop.restart();
	clockGame.restart();
	float inputDelay = 0.2;
	bool canInput = true;
	Text title;
	Text playButton;
	Text exitButton;
	Text creditsButton;
	Sprite tankSprite;
	Texture textureTank;
	int focusPos = 0;
	textureTank.loadFromFile("PlayerTank.png", IntRect(0, 0, 68, 56));
	tankSprite.setTexture(textureTank);
	tankSprite.setScale(0.5, 0.5);
	setTextFormat(title, guiFont, 120, "TANKARGEDDON");
	setTextFormat(playButton, guiFont, 70, "Play");
	setTextFormat(creditsButton, guiFont, 70, "Credits");
	setTextFormat(exitButton, guiFont, 70, "Exit");

	title.setPosition(40, 0);
	playButton.setPosition(window.getSize().x, 300);
	creditsButton.setPosition(window.getSize().x, 370);
	exitButton.setPosition(window.getSize().x, 440);

	title.setFillColor(Color(204, 24, 24, 255));
	title.setOutlineThickness(2);
	title.setOutlineColor(Color(254, 255, 251, 255));

	playButton.setFillColor(Color(117, 154, 93, 255));
	playButton.setOutlineThickness(2);
	playButton.setOutlineColor(Color(255, 255, 255, 255));

	creditsButton.setFillColor(Color(117, 154, 93, 255));
	creditsButton.setOutlineThickness(2);
	creditsButton.setOutlineColor(Color(255, 255, 255, 255));

	exitButton.setFillColor(Color(117, 154, 93, 255));
	exitButton.setOutlineThickness(2);
	exitButton.setOutlineColor(Color(255, 255, 255, 255));
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// CIERRA LA VENTANA
			if ((event.type == Event::Closed) || (event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape))
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Down) and canInput)
		{
			canInput = false;
			clockLoop.restart();
			focusPos++;
			if (focusPos > 2)
				focusPos = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Up) and canInput)
		{
			canInput = false;
			clockLoop.restart();
			focusPos--;
			if (focusPos < 0)
				focusPos = 2;
		}
		if (!canInput)
		{
			if (clockLoop.getElapsedTime().asSeconds() > inputDelay)
				canInput = true;
		}
		switch (focusPos)
		{
		case 0:
		{
			tankSprite.setPosition(playButton.getPosition().x - 56, playButton.getPosition().y + 40);
			playButton.setFillColor(Color(155, 193, 70, 255));
			exitButton.setFillColor(Color(117, 154, 93, 255));
			creditsButton.setFillColor(Color(117, 154, 93, 255));
			break;
		}
		case 1:
		{
			tankSprite.setPosition(creditsButton.getPosition().x - 56, creditsButton.getPosition().y + 40);
			playButton.setFillColor(Color(117, 154, 93, 255));
			exitButton.setFillColor(Color(117, 154, 93, 255));
			creditsButton.setFillColor(Color(155, 193, 70, 255));
			break;
		}
		case 2:
		{
			tankSprite.setPosition(exitButton.getPosition().x - 56, exitButton.getPosition().y + 40);
			playButton.setFillColor(Color(117, 154, 93, 255));
			exitButton.setFillColor(Color(155, 193, 70, 255));
			creditsButton.setFillColor(Color(117, 154, 93, 255));
			break;
		}
		default:
			break;
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Return) and canInput)
		{
			canInput = false;
			clockLoop.restart();
			switch (focusPos)
			{
			case 0:
			{
				return 2;
				break;
			}
			case 1:
			{
				return 1;
				break;
			}
			case 2:
			{
				window.close();
				break;
			}
			default:
				break;
			}
		}
		if (title.getPosition().y < 101)
			title.move(0, 0.1*clockGame.getElapsedTime().asSeconds());
		if (playButton.getPosition().x > 318)
			playButton.move(-0.1*clockGame.getElapsedTime().asSeconds(), 0);
		if (creditsButton.getPosition().x > 318)
			creditsButton.move(-0.1*clockGame.getElapsedTime().asSeconds(), 0);
		if (exitButton.getPosition().x > 318)
			exitButton.move(-0.1*clockGame.getElapsedTime().asSeconds(), 0);
			
		window.clear();
		window.draw(title);
		window.draw(playButton);
		window.draw(creditsButton);
		window.draw(exitButton);
		window.draw(tankSprite);
		window.display();
	}
	return -1;
}
