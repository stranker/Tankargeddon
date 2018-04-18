#ifndef PLAYERTANK_H
#define PLAYERTANK_H
#include "Tank.h"

class PlayerTank : public Tank
{
public:
	PlayerTank(int life, float speed);
	~PlayerTank();
	virtual void movement(float deltaTime);
	virtual void shoot(vector<Bullet> &bullets);
	virtual void update(float deltaTime, vector<Bullet> &bullets);
	virtual void kill();
};
#endif