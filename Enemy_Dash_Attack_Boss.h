#pragma once
#include "Enemy_State.h"
class Enemy_Dash_Attack_Boss :
	public Enemy_State
{
private:

	int DashAttackCount;
	int MaxDashAttackCount;

	float targetAngle;

public:

	virtual Enemy_State* input_state(Enemy_Basic* _Enemy, bool reverse, int targetX, int targetY); //������Ʈ ���¿�, �¿찪�� ����.
	virtual void update(Enemy_Basic* _Enemy, int targetX, int targetY);
	virtual void release(Enemy_Basic* _Enemy);

	virtual void enter_this_state(Enemy_Basic* _Enemy);


	void ImageUpdateFunc(Enemy_Basic* _Enemy);


};

