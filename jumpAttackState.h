#pragma once
#include "state.h"
class player;
class jumpAttackState : public state
{
private:
	//불의 전사
	bool _rightMove;				//눌렀나 확인용
	bool _leftMove;					//눌렀나 확인용	
	bool _upMove;					//눌렀나 확인용	
	bool _downMove;					//눌렀나 확인용	
	vector<int> _vLeftRight;		//2개 동시에 눌렀을 때 마지막에 누른 방향키로 진행
	vector<int> _vUpDown;			//2개 동시에 눌렀을 때 마지막에 누른 방향키로 진행
public:
	virtual state* inputHandle(player* player);
	virtual void enter(player* player);
	virtual void update(player * player);
	virtual void exit(player * player);
};

