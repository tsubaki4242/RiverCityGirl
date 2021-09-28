#pragma once
#include "Enemy_State.h"

#define OBSERVE_RANGE 300
#define NORMAL_ATTACK_RANGE 100
#define DASH_ATTACK_RANGE 500
#define JUMP_ATTACK_RANGE 200

class Enemy_Move : public Enemy_State
{
private:


	bool isObserve; //Ž��������
	int RandomObserveUpdateCount; //���� ���� �������� ���� ���ֱ�
	int ObserveCount;			  //�������� ������Ʈ ī��Ʈ
	float RandomAngle; //������ �ޱ۷� �̵��ϰ� ������.





public:


	virtual Enemy_State* input_state(Enemy_Basic* _Enemy, bool reverse, int targetX, int targetY); //������Ʈ ���¿�, �¿찪�� ����.
	virtual void update(Enemy_Basic* _Enemy, int targetX, int targetY);
	virtual void release(Enemy_Basic* _Enemy);
	virtual void render();

	virtual void enter_this_state(Enemy_Basic* _Enemy);


	void ImageUpdateFunc(Enemy_Basic* _Enemy);

};

