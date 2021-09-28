#pragma once
#include "state.h"

class player;
class hitAndDownState : public state
{
private:
	float _saveZ;
	bool _onGround;
public:
	virtual state* inputHandle(player* player);
	virtual void enter(player* player);
	virtual void update(player * player);
	virtual void exit(player * player);
};

