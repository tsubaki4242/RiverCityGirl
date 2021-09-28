#include "stdafx.h"
#include "runState.h"
#include "idleState.h"
#include "skillState.h"
#include "jumpState.h"
#include "dashAttackState.h"
#include "strongAttackState.h"
#include "fallState.h"
#include "player.h"

state * runState::inputHandle(player * player)
{
	if (!_leftMove && !_rightMove && !_upMove && !_downMove)
	{
		PLAYERDATA->speed = 4.0f;
		return new idleState;
	}
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		PLAYERDATA->speed = 0.0f;
		return new skillState;
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		return new jumpState;
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		return new dashAttackState;
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		PLAYERDATA->speed = 0.0f;
		return new strongAttackState;
	}
	if (_onGround && !PLAYERDATA->isRide)
	{
		return new fallState;
	}
	return nullptr;
}

void runState::enter(player * player)
{
	PLAYERDATA->image = IMAGEMANAGER->findImage("캐릭터달리기");
	PLAYERDATA->frameX = 0;
	PLAYERDATA->time = 0;
	PLAYERDATA->speed = DASHSPEED;
	PLAYERDATA->imageErrorX = 0;
	PLAYERDATA->imageErrorY = 0;
	PLAYERDATA->isAttack = false;
	PLAYERDATA->stateEnum = STATE_RUN;
	_onGround = PLAYERDATA->isRide;
}

void runState::update(player * player)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (!_leftMove)
		{
			_leftMove = true;
			_vLeftRight.push_back(1);
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		for (int i = 0; i < _vLeftRight.size();)
		{
			if (_vLeftRight[i] == 1)
			{
				_leftMove = false;
				_vLeftRight.erase(_vLeftRight.begin() + i);
			}
			else
				i++;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (!_rightMove)
		{
			_rightMove = true;
			_vLeftRight.push_back(2);
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		for (int i = 0; i < _vLeftRight.size();)
		{
			if (_vLeftRight[i] == 2)
			{
				_rightMove = false;
				_vLeftRight.erase(_vLeftRight.begin() + i);
			}
			else
				i++;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (!_upMove)
		{
			_upMove = true;
			_vUpDown.push_back(1);
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		for (int i = 0; i < _vUpDown.size();)
		{
			if (_vUpDown[i] == 1)
			{
				_upMove = false;
				_vUpDown.erase(_vUpDown.begin() + i);
			}
			else
				i++;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (!_downMove)
		{
			_downMove = true;
			_vUpDown.push_back(2);
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		for (int i = 0; i < _vUpDown.size();)
		{
			if (_vUpDown[i] == 2)
			{
				_downMove = false;
				_vUpDown.erase(_vUpDown.begin() + i);
			}
			else
				i++;
		}
	}
	if (_vLeftRight.size() > 0)
	{
		int temp = _vLeftRight.size() - 1;
		switch (_vLeftRight[temp])
		{
		case 1:
			if (PLAYERDATA->frameY == 0)
				PLAYERDATA->frameY = 1;
			PLAYERDATA->x -= PLAYERDATA->speed;
			break;
		case 2:
			if (PLAYERDATA->frameY == 1)
				PLAYERDATA->frameY = 0;
			PLAYERDATA->x += PLAYERDATA->speed;
			break;
		default:
			break;
		}
	}
	if (_vUpDown.size() > 0)
	{
		int temp = _vUpDown.size() - 1;
		switch (_vUpDown[temp])
		{
		case 1:
			PLAYERDATA->y -= PLAYERDATA->speed * 0.5f;
			break;
		case 2:
			PLAYERDATA->y += PLAYERDATA->speed * 0.5f;
			break;
		default:
			break;
		}
	}
	if (PLAYERDATA->time % 3 == 2)
	{
		PLAYERDATA->frameX += 1;
		if (PLAYERDATA->frameX > PLAYERDATA->image->getMaxFrameX())
			PLAYERDATA->frameX = 0;
	}
}

void runState::exit(player * player)
{
}
