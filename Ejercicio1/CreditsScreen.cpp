#include "CreditsScreen.h"

int CreditsScreen::Run(RenderWindow & window)
{
	Font guiFont;
	guiFont.loadFromFile("8-Bit Madness.ttf");
	Text textCredits;
	Text fontCredit;
	Text programmer;
	Text artist;
	Text itchio;
	Text escapeButton;
	setTextFormat(textCredits, guiFont, 75, "CREDITS");
	setTextFormat(fontCredit, guiFont, 40, "Font: robotdude@att.net");
	setTextFormat(programmer, guiFont, 40, "Programmer: Daniel H. Natarelli");
	setTextFormat(artist, guiFont, 40, "2dArtist: Daniel H. Natarelli");
	setTextFormat(itchio, guiFont, 30, "https://stranker.itch.io/");
	setTextFormat(escapeButton, guiFont, 30, "Press ESCAPE to exit");

	textCredits.setPosition(250, 80);
	fontCredit.setPosition(180, 250);
	programmer.setPosition(130, 300);
	artist.setPosition(160, 350);
	itchio.setPosition(220, 400);
	escapeButton.setPosition(520, 550);

	textCredits.setFillColor(Color(82, 160, 208, 255));
	fontCredit.setFillColor(Color(255, 99, 71, 255));
	programmer.setFillColor(Color(255, 99, 71, 255));
	artist.setFillColor(Color(255, 99, 71, 255));
	itchio.setFillColor(Color(255, 99, 71, 255));
	escapeButton.setFillColor(Color(255, 255, 255, 255));

	textCredits.setOutlineThickness(2);
	fontCredit.setOutlineThickness(1);
	programmer.setOutlineThickness(1);
	artist.setOutlineThickness(1);
	itchio.setOutlineThickness(1);

	textCredits.setOutlineColor(Color(255, 255, 255));

	Clock clock;
	float alphaChange = 0;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			// CIERRA LA VENTANA
			if (event.type == Event::Closed)
				window.close();
			if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape))
				return 0;

		}

		alphaChange = clock.getElapsedTime().asSeconds() * 50;

		fontCredit.setOutlineColor(Color(255, 255, 255, alphaChange));
		programmer.setOutlineColor(Color(255, 255, 255, alphaChange));
		artist.setOutlineColor(Color(255, 255, 255, alphaChange));
		itchio.setOutlineColor(Color(255, 255, 255, alphaChange));
		window.clear();
		window.draw(textCredits);
		window.draw(fontCredit);
		window.draw(artist);
		window.draw(programmer);
		window.draw(itchio);
		window.draw(escapeButton);
		window.display();
	}
	return 0;
}
