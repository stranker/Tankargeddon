#include "Bullet.h"

Bullet::Bullet()
{
	_speed = 500.0;
	_damage = 1;
	if (!_texture.loadFromFile("Bullet.png"))
		std::cout << "Falla al cargar textura bullet" << std::endl;
	else
	{
		_sprite.setTexture(_texture);
		_sprite.setOrigin(4, 2);
		_collider = _sprite.getGlobalBounds();
	}
}

Bullet::~Bullet()
{
}

void Bullet::createBullet(sf::Vector2f position, sf::Vector2f direction, float angle)
{
	_sprite.setPosition(position);
	_direction = direction;
	_sprite.setRotation(angle);
}

void Bullet::setPosition(int x, int y)
{
	_sprite.setPosition(x, y);
}

void Bullet::setDirection(sf::Vector2f direction)
{
	_direction = direction;
}

void Bullet::setRotation(float angle)
{
	_sprite.rotate(angle);
}

Sprite& Bullet::getSprite()
{
	return _sprite;
}

FloatRect Bullet::getCollider()
{
	return _collider;
}



bool Bullet::isOffScreen()
{
	return _sprite.getPosition().x < 0 || _sprite.getPosition().x > 800 || _sprite.getPosition().y < 0 || _sprite.getPosition().y > 600;
}

void Bullet::movement(float deltaTime)
{
	if (!isOffScreen())
	{
		_sprite.move(_direction * _speed * deltaTime);
	}
}

void Bullet::update(float deltaTime)
{
	movement(deltaTime);
}