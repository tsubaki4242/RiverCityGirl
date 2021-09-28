#pragma once
#include "state.h"
class dashAttackState : public state
{
private:
	bool _onGround;					//처음 들어올 때 isRide를 저장

public:
	virtual state* inputHandle(player* player);
	virtual void enter(player* player);
	virtual void update(player * player);
	virtual void exit(player * player);
};

