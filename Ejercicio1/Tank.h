#ifndef TANK_H
#define TANK_H
#include "Bullet.h"

class Tank
{
private:
	int _life;
	float _speed;
	bool _moving;
	bool _canShoot;
	bool _reloading;
	float _shootReload;
	Bullet _bullet;
	Clock _shootTimer;
	Clock _spriteTimer;
	Vector2f _direction;
	Texture _texture;
	Sprite _sprite;
	IntRect _rectSprite;
	FloatRect _collision;
public:
	Tank(int life, float speed);
	~Tank();
	void setLife(int life);
	void setSpeed(float speed);
	void setShootReload(float shootReload);
	void setRectSprite(IntRect rectSprite);
	void setShoot(bool val);
	void setSprite(Sprite sprite);
	Bullet& getBullet();
	int getLife();
	float getShootReload();
	float getSpeed();
	bool isMoving();
	Clock getSpriteTimer();
	void setMoving(bool val);
	void initializeSprite(string file);
	void animateSprite();
	Sprite& getSprite();
	FloatRect& getCollision();
	IntRect getRectSprite();
	Texture getTexture();
	Vector2f getShootPos();
	Vector2f& getDirection();
	void setDirection(Vector2f direction);
	bool canShoot();
	float getRotation();
	void reload();
	virtual void movement(float deltaTime);
	virtual void shoot(vector<Bullet> &bullets);
	virtual void update(float deltaTime, vector<Bullet> &bullets);
};
#endif