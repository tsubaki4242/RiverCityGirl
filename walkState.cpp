#include "stdafx.h"
#include "walkState.h"
#include "idleState.h"
#include "skillState.h"
#include "comboState.h"
#include "strongAttackState.h"
#include "jumpState.h"
#include "fallState.h"
#include "player.h"

state * walkState::inputHandle(player * player)
{
	
	if (_vLeftRight.size() == 0 && _vUpDown.size() == 0)
	{
		PLAYERDATA->speed = 0.0f;
		return new idleState;
	}
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		PLAYERDATA->speed = 0.0f;
		return new skillState;
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		PLAYERDATA->speed = 0.0f;
		return new comboState;
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		PLAYERDATA->speed = 0.0f;
		return new strongAttackState;
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		return new jumpState;
	}
	if (_onGround && !PLAYERDATA->isRide)
	{
		return new fallState;
	}
	return nullptr;
}

void walkState::enter(player * player)
{
	PLAYERDATA->image = IMAGEMANAGER->findImage("캐릭터무브");
	PLAYERDATA->frameX = 0;
	PLAYERDATA->time = 0;
	PLAYERDATA->speed = WALKSPEED;
	PLAYERDATA->imageErrorX = 0;
	PLAYERDATA->imageErrorY = 0;
	PLAYERDATA->isAttack = false;
	PLAYERDATA->stateEnum = STATE_WALK;
	_onGround = PLAYERDATA->isRide;
}

//방향키를 stay하는 동안 불값 true 떼면 false
void walkState::update(player * player)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (!_leftMove)
		{
			_leftMove = true;
			PLAYERDATA->moveCommandInput = 20;
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
			PLAYERDATA->moveCommandInput = 20;
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
			PLAYERDATA->y -= PLAYERDATA->speed*0.5f;
			break;
		case 2:
			PLAYERDATA->y += PLAYERDATA->speed*0.5f;
			break;
		default:
			break;
		}
	}
	/*if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_leftMove = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_leftMove = false;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_rightMove = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_rightMove = false;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_upMove = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		_upMove = false;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_downMove = true;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		_downMove = false;
	}*/
	/*if (_leftMove)
	{
		if (PLAYERDATA->frameY == 0)
			PLAYERDATA->FrameY(1);
		PLAYERDATA->X(PLAYERDATA->x - PLAYERDATA->speed);
	}
	if (_rightMove)
	{
		if (PLAYERDATA->frameY == 1)
			PLAYERDATA->FrameY(0);
		PLAYERDATA->X(PLAYERDATA->x + PLAYERDATA->speed);
	}
	if (_upMove)
	{
		PLAYERDATA->Y(PLAYERDATA->y - PLAYERDATA->speed*0.5);
	}
	if (_downMove)
	{
		PLAYERDATA->Y(PLAYERDATA->y + PLAYERDATA->speed*0.5);
	}*/
	if (PLAYERDATA->time % 5 == 4)
	{
		PLAYERDATA->frameX += 1;
		if (PLAYERDATA->frameX > PLAYERDATA->image->getMaxFrameX())
			PLAYERDATA->frameX = 0;
	}
}

void walkState::exit(player * player)
{

}
