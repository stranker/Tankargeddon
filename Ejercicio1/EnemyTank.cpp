#include "EnemyTank.h"

Vector2f newDirection(float angle)
{
	float x = cos(angle * (M_PI / 180));
	float y = sin(angle * (M_PI / 180));
	return Vector2f(x, y);
}

Vector2f newPos()
{
	float x = rand() % 800;
	float y = rand() % 600;
	return Vector2f(x, y);
}

Vector2f normalize(Vector2f vector)
{
	return vector / (sqrt(pow(vector.x, 2) + pow(vector.y, 2)));
}

float EnemyTank::calculateAngleTo(Vector2f position)
{
	float y = normalize(position - getSprite().getPosition()).y;
	return getSprite().getRotation() + asin(y) * 180 / M_PI;
}

int EnemyTank::getScore()
{
	return _score;
}

EnemyTank::EnemyTank(int life, float speed) : Tank(life, speed)
{
	setShootReload(4 + rand()%6);
	setRectSprite(IntRect(0, 0, 68, 56));
	initializeSprite("EnemyTank.png");
	_score = 50;
	_moveTime = 4;
	_stopTime = 5;
	_newPos = newPos();
	getSprite().setRotation(rand() % 360);
	_angleToRotate = calculateAngleTo(_newPos);
}

EnemyTank::~EnemyTank()
{
}

void EnemyTank::moveTo(Vector2f position, float deltaTime)
{
	getSprite().move(normalize(position - getSprite().getPosition()) * getSpeed() * deltaTime);
}

// REVISAR NO ROTA BIEN
void EnemyTank::rotateTo(float angleToRotate, float deltaTime)
{
	if (!isMoving())
	{
		if (_angleToRotate < 0)
		{
			if (getSprite().getRotation() < 360 + _angleToRotate)
				getSprite().rotate(-30 * deltaTime);
			else
			{
				setMoving(true);
				_moveClock.restart();
			}
		}
		else
			if (getSprite().getRotation() < _angleToRotate)
				getSprite().rotate(30 * deltaTime);
			else
			{
				setMoving(true);
				_moveClock.restart();
			}
	}
}

// REVISAR
void EnemyTank::shoot(vector<Bullet>& bullets)
{
	setDirection(normalize(_newPos));
	getBullet().createBullet(getShootPos(), getDirection(), acos(getDirection().x) * 180 / M_PI);
	bullets.push_back(Bullet(getBullet()));
	setShoot(false);
}

void EnemyTank::update(float deltaTime, vector<Bullet>& bullets)
{

	if (_moveClock.getElapsedTime().asSeconds() > _moveTime && isMoving()) // Se mueve y corta el tiempo
	{
		setMoving(false);
		_currentAngle = getSprite().getRotation();
		_newPos = newPos();
		_angleToRotate = calculateAngleTo(_newPos);
	}
	if (isMoving())
	{
		moveTo(_newPos, deltaTime);
		animateSprite();
	}
	else
	{
		rotateTo(_angleToRotate, deltaTime);
	}
	if (canShoot())
		shoot(bullets);
	else
		reload();
}