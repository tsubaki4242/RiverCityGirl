#pragma once
#include "state.h"
class player;
class jumpAttackState : public state
{
private:
	//���� ����
	bool _rightMove;				//������ Ȯ�ο�
	bool _leftMove;					//������ Ȯ�ο�	
	bool _upMove;					//������ Ȯ�ο�	
	bool _downMove;					//������ Ȯ�ο�	
	vector<int> _vLeftRight;		//2�� ���ÿ� ������ �� �������� ���� ����Ű�� ����
	vector<int> _vUpDown;			//2�� ���ÿ� ������ �� �������� ���� ����Ű�� ����
public:
	virtual state* inputHandle(player* player);
	virtual void enter(player* player);
	virtual void update(player * player);
	virtual void exit(player * player);
};

