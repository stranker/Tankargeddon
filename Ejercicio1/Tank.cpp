#include "Tank.h"

Tank::Tank(int life, float speed)
{
	_life = life;
	_speed = speed;
	_moving = false;
	_canShoot = false;
	_reloading = false;
}

Tank::~Tank()
{
}

void Tank::setLife(int life)
{
	_life = life;
}

void Tank::setSpeed(float speed) 
{
	_speed = speed;
}

void Tank::setShootReload(float shootReload)
{
	_shootReload = shootReload;
}

int Tank::getLife()
{
	return _life;
}

float Tank::getShootReload()
{
	return _shootReload;
}

float Tank::getSpeed()
{
	return _speed;
}

bool Tank::isMoving()
{
	return _moving;
}

Clock Tank::getSpriteTimer()
{
	return _spriteTimer;
}

void Tank::setMoving(bool val)
{
	_moving = val;
}

Sprite& Tank::getSprite()
{
	return _sprite;
}

Vector2f Tank::getShootPos()
{
	return _sprite.getPosition() + Vector2f(_direction.x * (_rectSprite.width/2), _direction.y * (_rectSprite.height / 2));
}

Vector2f& Tank::getDirection()
{
	return _direction;
}

void Tank::setDirection(Vector2f direction)
{
	_direction = direction;
}

void Tank::setRectSprite(IntRect rectSprite)
{
	_rectSprite = rectSprite;
}

void Tank::setShoot(bool val)
{
	_canShoot = val;
}

void Tank::setSprite(Sprite sprite)
{
	_sprite = sprite;
}


Bullet& Tank::getBullet()
{
	return _bullet;
}

FloatRect& Tank::getCollision()
{
	return _collision;
}

IntRect Tank::getRectSprite()
{
	return _rectSprite;
}

Texture Tank::getTexture()
{
	return _texture;
}

float Tank::getRotation()
{
	return _sprite.getRotation();
}

void Tank::reload()
{
	if (!_canShoot && !_reloading)
	{
		_reloading = true;
		_shootTimer.restart();
	}
	if (_reloading)
	{
		if (_shootTimer.getElapsedTime().asSeconds() > _shootReload)
		{
			_canShoot = true;
			_reloading = false;
		}
	}
}

void Tank::initializeSprite(string filename)
{
	_texture.loadFromFile(filename);
	_sprite.setTexture(_texture);
	_sprite.setTextureRect(_rectSprite);
	_sprite.setOrigin(_rectSprite.width / 2, _rectSprite.height / 2);
	_collision = _sprite.getGlobalBounds();
}

void Tank::animateSprite()
{
	if (_spriteTimer.getElapsedTime().asSeconds() > 0.08 && isMoving())
	{
		if (_rectSprite.left == _rectSprite.width*2)
			_rectSprite.left = 0;
		else
			_rectSprite.left += _rectSprite.width;
		_sprite.setTextureRect(_rectSprite);
		_spriteTimer.restart();
	}
}

bool Tank::canShoot()
{
	return _canShoot;
}

void Tank::movement(float deltaTime)
{

}

void Tank::shoot(vector<Bullet> &bullets)
{

}

void Tank::update(float deltaTime, vector<Bullet> &bullets)
{

}

