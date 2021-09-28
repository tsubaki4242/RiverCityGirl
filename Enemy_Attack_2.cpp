#include "stdafx.h"
#include "Enemy_Attack_2.h"

#include "Enemy_Basic.h"
#include "Enemy_Idle.h"
#include "Enemy_Attack_3.h"

#include "Enemy_Move.h"


Enemy_State * Enemy_Attack_2::input_state(Enemy_Basic * _Enemy, bool reverse, int targetX, int targetY)
{
	if (_Enemy->getEnemyInfo()->CurrentframeX == _Enemy->getEnemyInfo()->_image->getMaxFrameX())
	{
		if (_Enemy->getEnemyInfo()->y < targetY - 25 || _Enemy->getEnemyInfo()->y > targetY + 25)
		{
			_Enemy->setEnemyAiTrigger(OBSERVE_STATE_TRIGGER);
			_Enemy->setEnemyRandomCountReset_more();
			return new Enemy_Move();
		}
		else
		{
			if (getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) > NORMAL_ATTACK_RANGE)
			{
				_Enemy->setEnemyAiTrigger(OBSERVE_STATE_TRIGGER);
				_Enemy->setEnemyRandomCountReset_more();
				return new Enemy_Move();
			}
			else
			{
				
				return new Enemy_Attack_3();
			}

		}
	}
	return nullptr;
}

void Enemy_Attack_2::update(Enemy_Basic * _Enemy, int targetX, int targetY)
{
	
	ImageUpdateFunc(_Enemy);

	if (!_Enemy->getEnemyInfo()->isRight)
	{
		_Enemy->Setting_AttackRect_LeftRight(SCHOOL_GIRL,
			_Enemy->getEnemyInfo()->rc.left - 15, _Enemy->getEnemyInfo()->rc.top ,
			40, 30, 3,frameCount,frameUpdateCount);
		_Enemy->Setting_AttackRect_LeftRight(SCHOOL_BOY,
			_Enemy->getEnemyInfo()->rc.left - 2, _Enemy->getEnemyInfo()->rc.top ,
			40, 30, 3, frameCount, frameUpdateCount);
	}
	else
	{
		_Enemy->Setting_AttackRect_LeftRight(SCHOOL_GIRL,
			_Enemy->getEnemyInfo()->rc.right + 15, _Enemy->getEnemyInfo()->rc.top ,
			40, 30, 3, frameCount, frameUpdateCount);
		_Enemy->Setting_AttackRect_LeftRight(SCHOOL_BOY,
			_Enemy->getEnemyInfo()->rc.right + 20, _Enemy->getEnemyInfo()->rc.top ,
			40, 30, 3, frameCount, frameUpdateCount);
	}
}

void Enemy_Attack_2::release(Enemy_Basic * _Enemy)
{
}

void Enemy_Attack_2::render()
{
}

void Enemy_Attack_2::enter_this_state(Enemy_Basic * _Enemy)
{
	_Enemy->setEnemyTestText("ATTACK_2");
	_Enemy->set_Enemy_State_Enum(ATTACK_1);



	char str[128] = "Enemy_Image_Attack_2_";

	strcat_s(str, _Enemy->getEnemyInfo()->imageName);


	_Enemy->setEnemyImageKey(str);


	string Idle_Image = str;

	_Enemy->setEnemyImage(IMAGEMANAGER->findImage(Idle_Image));

	frameCount = 0;
	frameUpdateCount = 5;
	
	_Enemy->setEnemyFrameX(0);

	if (_Enemy->getEnemyInfo()->isRight) _Enemy->setEnemyFrameY(0);
	else _Enemy->setEnemyFrameY(1);
}

void Enemy_Attack_2::call_Attack_3_function(Enemy_Basic * _Enemy)
{
	Enemy_State* Attack_3;

	Attack_3 = new Enemy_Attack_3();

	_Enemy->set_Enemy_State(Attack_3);
}

void Enemy_Attack_2::ImageUpdateFunc(Enemy_Basic * _Enemy)
{
	frameCount++;

	if (frameCount % frameUpdateCount == 0)
	{
		if (_Enemy->getEnemyInfo()->isRight)
		{
			_Enemy->setEnemyFrameY(0);
			_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->CurrentframeX + 1);

		}
		else
		{
			_Enemy->setEnemyFrameY(1);
			_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->CurrentframeX + 1);

		}
	}
}
