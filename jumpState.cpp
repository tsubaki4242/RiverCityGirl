#include "stdafx.h"
#include "jumpState.h"
#include "jumpAttackState.h"
#include "jumpStrongAttackState.h"
#include "player.h"
#include "idleState.h"
#include "walkState.h"
#include "runState.h"

state * jumpState::inputHandle(player * player)
{
	if (PLAYERDATA->isRide)
	{
		if (_vLeftRight.size() == 0 && _vUpDown.size() == 0)
		{
			PLAYERDATA->jumpPower = 0.f;
			PLAYERDATA->speed = 0.f;
			return new idleState;
		}
		else if (PLAYERDATA->speed == DASHSPEED)
		{
			PLAYERDATA->jumpPower = 0.f;
			return new runState;
		}
		else
		{
			PLAYERDATA->jumpPower = 0.f;
			return new walkState;
		}
	}
	else if (PLAYERDATA->z < 0.f)
	{
		PLAYERDATA->z = 0.f;
		if (_vLeftRight.size() == 0 && _vUpDown.size() == 0)
		{
			PLAYERDATA->jumpPower = 0.f;
			PLAYERDATA->speed = 0.f;
			return new idleState;
		}
		else if (PLAYERDATA->speed == DASHSPEED)
		{
			PLAYERDATA->jumpPower = 0.f;
			return new runState;
		}
		else
		{
			PLAYERDATA->jumpPower = 0.f;
			return new walkState;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		return new jumpAttackState;
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		return new jumpStrongAttackState;
	}
	

	return nullptr;
}

void jumpState::enter(player * player)
{
	PLAYERDATA->image = IMAGEMANAGER->findImage("캐릭터점프");
	PLAYERDATA->frameX = 0;
	PLAYERDATA->time = 0;
	PLAYERDATA->jumpPower = 17.0f;
	PLAYERDATA->imageErrorX = 0;
	PLAYERDATA->imageErrorY = 0;
	PLAYERDATA->isRide = false;
	PLAYERDATA->isAttack = false;
	PLAYERDATA->stateEnum = STATE_JUMP;
}

void jumpState::update(player * player)
{
	PLAYERDATA->z += PLAYERDATA->jumpPower;
	PLAYERDATA->jumpPower -= PLAYERDATA->gravity;

	if (PLAYERDATA->jumpPower < -3.f)
		PLAYERDATA->frameX = 2;
	else if (PLAYERDATA->jumpPower < 1)
		PLAYERDATA->frameX = 1;
	else
		PLAYERDATA->frameX = 0;
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
}

void jumpState::exit(player * player)
{
}
