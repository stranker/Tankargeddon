#ifndef ENEMYTANK_H
#define ENEMYTANK_H

#include "Tank.h"

class EnemyTank : public Tank
{
private:
	float _moveTime;
	float _stopTime;
	int _score;
	Vector2f _newDirection;
	Vector2f _newPos;
	float _angleToRotate;
	float _currentAngle;
	Clock _moveClock;
	Clock _stopClock;
public:
	EnemyTank(int life, float speed);
	~EnemyTank();
	void moveTo(Vector2f position, float deltaTime);
	void rotateTo(float angleToRotate, float deltaTime);
	virtual void shoot(vector<Bullet> &bullets);
	virtual void update(float deltaTime, vector<Bullet> &bullets);
	float calculateAngleTo(Vector2f position);
	int getScore();
};
#endif