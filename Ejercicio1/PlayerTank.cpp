#include "PlayerTank.h"

PlayerTank::PlayerTank(int life, float speed) : Tank(life, speed)
{
	setShootReload(1.2);
	setRectSprite(IntRect(0, 0, 68, 56));
	initializeSprite("PlayerTank.png");
}

PlayerTank::~PlayerTank()
{
}

void PlayerTank::movement(float deltaTime)
{
	if (Keyboard::isKeyPressed(Keyboard::Left))
		getSprite().rotate(-70 * deltaTime);
	else if (Keyboard::isKeyPressed(Keyboard::Right))
		getSprite().rotate(70 * deltaTime);

	// CALCULO DIRECCION
	float x = cos(getSprite().getRotation()*(M_PI / 180));
	float y = sin(getSprite().getRotation()*(M_PI / 180));
	setDirection(Vector2f(x, y));

	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		getSprite().move(getDirection() * getSpeed() * deltaTime);
		setMoving(true);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		getSprite().move(-getDirection()* getSpeed() * deltaTime);
		setMoving(true);
	}
	else
	{
		getSprite().move(0, 0);
		setMoving(false);
	}
	// CAMBIAR SPRITE
	animateSprite();
}

void PlayerTank::shoot(vector<Bullet> &playerBullets)
{

	if (Keyboard::isKeyPressed(Keyboard::Key::Space) && canShoot())
	{
		SoundBuffer buffer;
		buffer.loadFromFile("Shoot.wav");
		Sound shoot;
		shoot.setBuffer(buffer);
		shoot.play();
		setShoot(false);
		getBullet().createBullet(getShootPos(), getDirection(), getRotation());
		playerBullets.push_back(Bullet(getBullet()));
	}
}

void PlayerTank::update(float deltaTime, vector<Bullet> &playerBullets)
{
	movement(deltaTime);
	shoot(playerBullets);
	if (!canShoot())
		reload();
}

void PlayerTank::kill()
{
}
