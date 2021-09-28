#pragma once
#include "state.h"
class comboState : public state
{
private:
	bool _comboOn;
	bool _onGround;				//ó�� ���� �� isRide�� ����
public:
	virtual state* inputHandle(player* player);
	virtual void enter(player* player);
	virtual void update(player * player);
	virtual void exit(player * player);
};

