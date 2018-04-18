#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <iostream>
#define M_PI  3.14159265358979323846

using namespace sf;
using namespace std;

class Bullet
{
private:
	float _speed;
	int _damage;
	Vector2f _direction;
	Texture _texture;
	Sprite _sprite;
	FloatRect _collider;
public:
	Bullet();
	~Bullet();
	void movement(float deltaTime);
	void setPosition(int x, int y);
	void update(float deltaTime);
	bool isOffScreen();
	void setDirection(Vector2f direction);
	void setRotation(float angle);
	void createBullet(Vector2f position, Vector2f direction, float angle);
	Sprite& getSprite();
	FloatRect getCollider();
};
#endif