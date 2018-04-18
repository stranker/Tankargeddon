#include "GameScreen.h"
#include "PlayerTank.h"
#include "EnemyTank.h"

using namespace sf;
using namespace std;


bool collideBulletEnemy(Bullet b, PlayerTank &player)
{
	bool contact = false;
	if (b.getSprite().getGlobalBounds().intersects(player.getSprite().getGlobalBounds()))
	{
		player.setLife(player.getLife() - 1);
		contact = true;
	}
	return contact;
}

bool collideBulletPlayer(Bullet b, vector<EnemyTank> &enemies, int &score, int wave)
{
	bool contact = false;
	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (b.getSprite().getGlobalBounds().intersects(enemies[i].getSprite().getGlobalBounds()))
		{
			score += enemies[i].getScore() * wave;
			enemies.erase(enemies.begin() + i);
			contact = true;
		}
	}
	return contact;
}

void createEnemies(EnemyTank &enemy, vector<EnemyTank> &enemies, int wave)
{
	for (int i = 0; i < wave; i++)
	{
		int numRandom = rand() % 4;
		Vector2f position;
		switch (numRandom)
		{
		case 0:
		{
			position = Vector2f(0, 0);
			break;
		}
		case 1:
		{
			position = Vector2f(0, 600);
			break;
		}
		case 2:
		{
			position = Vector2f(800, 0);
			break;
		}
		case 3:
		{
			position = Vector2f(800, 600);
			break;
		}
		default:
			break;
		}
		enemy.getSprite().setPosition(position);
		enemies.push_back(EnemyTank(enemy));
	}
}

int GameScreen::Run(RenderWindow &window)
{
	// BACKGROUND
	Texture textBackground;
	Sprite spriteBackground;
	textBackground.loadFromFile("Background.png");
	spriteBackground.setTexture(textBackground);
	// SCORE Y WAVE
	int score = 0, wave = 1;
	float newWaveTime = 4;
	bool spawning = false;
	bool gameOver = false;
	Clock gameClock, newWaveClock, tutorialClock;
	// LIMITO LOS FRAMERATE
	window.setFramerateLimit(60);
	// CREO PERSONAJE
	PlayerTank player(3, 70.0);
	player.getSprite().setPosition(window.getSize().x / 2, window.getSize().y / 2);
	// ENEMIES
	EnemyTank enemyTank(1, 50.0);
	vector<EnemyTank> enemies;
	createEnemies(enemyTank, enemies, wave);
	// BALAS
	vector<Bullet> playerBullets;
	vector<Bullet> enemyBullets;
	// SEMILLA RANDOM
	srand(time(NULL));
	// FONT
	Font guiFont;
	guiFont.loadFromFile("8-Bit Madness.ttf");
	// GUI
	Texture textGuiPlayer;
	Sprite guiPlayer;
	textGuiPlayer.loadFromFile("PlayerTank.png", IntRect(0, 0, 68, 56));
	guiPlayer.setTexture(textGuiPlayer);
	guiPlayer.setScale(0.5, 0.5);

	Text textPlayerLives, textScore, textWaves, tutArrow, tutSpace, endGame, endPress;
	setTextFormat(textPlayerLives, guiFont, 40, "x" + to_string(player.getLife()));
	setTextFormat(textScore, guiFont, 40, "Score " + to_string(score));
	setTextFormat(textWaves, guiFont, 40, "Wave " + to_string(wave));
	setTextFormat(endGame, guiFont, 100, "GAME OVER");
	setTextFormat(endPress, guiFont, 60, "Press ESCAPE to continue");
	setTextFormat(tutArrow, guiFont, 70, "USE ARROWS TO MOVE");
	setTextFormat(tutSpace, guiFont, 70, "USE SPACE TO SHOOT");


	guiPlayer.setPosition(10, 15);
	textPlayerLives.setPosition(50, 0);
	textScore.setPosition(300, 0);
	textWaves.setPosition(650, 0);
	tutArrow.setPosition(125, 400);
	tutSpace.setPosition(125, 450);
	endGame.setPosition(200, 250);
	endPress.setPosition(100, 500);

	textPlayerLives.setFillColor(Color::Black);
	textScore.setFillColor(Color::Black);
	textWaves.setFillColor(Color::Black);
	tutArrow.setFillColor(Color::Black);
	tutSpace.setFillColor(Color::Black);
	endGame.setFillColor(Color::Black);
	endPress.setFillColor(Color::Black);



	while (window.isOpen())
	{
		// CALCULO DELTATIME
		sf::Time deltaTime = gameClock.restart();

		sf::Event event;
		while (window.pollEvent(event))
		{
			// CIERRA LA VENTANA
			if (event.type == Event::Closed)
				window.close();
			if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape))
				return 0;
		}

		if (player.getLife() > 0)
			player.update(deltaTime.asSeconds(), playerBullets);
		else
			gameOver = true;

		// SIN ENEMIGOS, SPAWNEARLOS
		if (enemies.size() == 0 && !spawning)
		{
			newWaveClock.restart();
			wave++;
			spawning = true;
		}
		// SPAWN
		if (newWaveClock.getElapsedTime().asSeconds() > newWaveTime && spawning)
		{
			spawning = false;
			createEnemies(enemyTank, enemies, wave);
		}
		// UPDATE ENEMIGOS
		for (size_t i = 0; i < enemies.size(); i++)
		{
			enemies[i].update(deltaTime.asSeconds(), enemyBullets);
		}
		// LOGICA BALAS PLAYER
		for (size_t i = 0; i < playerBullets.size(); i++)
		{
			if (playerBullets[i].isOffScreen())
				playerBullets.erase(playerBullets.begin() + i);
			else
			{
				playerBullets[i].update(deltaTime.asSeconds());
				if (collideBulletPlayer(playerBullets[i], enemies, score, wave))
					playerBullets.erase(playerBullets.begin() + i);
			}
		}
		// LOGICA BALAS ENEMIGAS
		for (size_t i = 0; i < enemyBullets.size(); i++)
		{
			if (enemyBullets[i].isOffScreen())
				enemyBullets.erase(enemyBullets.begin() + i);
			else
			{
				enemyBullets[i].update(deltaTime.asSeconds());
				if (collideBulletEnemy(enemyBullets[i], player))
					enemyBullets.erase(enemyBullets.begin() + i);
			}
		}
		// GUI
		textPlayerLives.setString("x" + to_string(player.getLife()));
		textWaves.setString("wave " + to_string(wave));
		textScore.setString("score " + to_string(score));

		// DIBUJAR EN PANTALLA
		window.clear();
		window.draw(spriteBackground);
		window.draw(player.getSprite());
		for (size_t i = 0; i < enemies.size(); i++)
		{
			window.draw(enemies[i].getSprite());
		}
		// BALAS PLAYER
		for (size_t i = 0; i < playerBullets.size(); i++)
		{
			window.draw(playerBullets[i].getSprite());
		}
		//BALAS ENEMYS
		for (size_t i = 0; i < enemyBullets.size(); i++)
		{
			window.draw(enemyBullets[i].getSprite());
		}
		if (gameOver)
		{
			window.draw(endGame);
			window.draw(endPress);
		}
		if (tutorialClock.getElapsedTime().asSeconds() < 7)
		{
			window.draw(tutArrow);
			window.draw(tutSpace);
		}

		window.draw(guiPlayer);
		window.draw(textPlayerLives);
		window.draw(textScore);
		window.draw(textWaves);
		window.display();
	}
	return 0;
}