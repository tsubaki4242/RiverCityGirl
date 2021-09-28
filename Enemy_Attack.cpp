#include "stdafx.h"
#include "Enemy_Attack.h"
#include "Enemy_Attack_2.h"



#include "Enemy_Move.h"

#include "Enemy_Basic.h"



Enemy_State * Enemy_Attack::input_state(Enemy_Basic * _Enemy, bool reverse, int targetX, int targetY)
{
	//if (_Enemy->getEnemyInfo()->CurrentframeX == _Enemy->getEnemyInfo()->_image->getMaxFrameX() && 
	//	!(_Enemy->getEnemyInfo()->y >= targetY - 25 && _Enemy->getEnemyInfo()->y <= targetY + 25) &&
	//	!getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) > NORMAL_ATTACK_RANGE)
		
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
				return new Enemy_Attack_2();
			}

		}		
	}


	return nullptr;
}

void Enemy_Attack::update(Enemy_Basic * _Enemy, int targetX, int targetY)
{

	ImageUpdateFunc(_Enemy);

	if (!_Enemy->getEnemyInfo()->isRight)
	{
		_Enemy->Setting_AttackRect_LeftRight(SCHOOL_GIRL,
			_Enemy->getEnemyInfo()->rc.left - 15, _Enemy->getEnemyInfo()->rc.top ,
			40, 30, 2, frameCount, frameUpdateCount);
		_Enemy->Setting_AttackRect_LeftRight(SCHOOL_BOY,
			_Enemy->getEnemyInfo()->rc.left - 20, _Enemy->getEnemyInfo()->rc.top ,
			40, 30, 3, frameCount, frameUpdateCount);
	}
	else
	{
		_Enemy->Setting_AttackRect_LeftRight(SCHOOL_GIRL,
			_Enemy->getEnemyInfo()->rc.right + 15, _Enemy->getEnemyInfo()->rc.top ,
			40, 30, 2, frameCount, frameUpdateCount);
		_Enemy->Setting_AttackRect_LeftRight(SCHOOL_BOY,
			_Enemy->getEnemyInfo()->rc.right + 20, _Enemy->getEnemyInfo()->rc.top ,
			40, 30, 3, frameCount, frameUpdateCount);
	}
}

void Enemy_Attack::release(Enemy_Basic * _Enemy)
{
}

void Enemy_Attack::render()
{
}

void Enemy_Attack::enter_this_state(Enemy_Basic * _Enemy)
{
	_Enemy->setEnemyTestText("ATTACK");
	_Enemy->set_Enemy_State_Enum(ATTACK_1);

	char str[128] = "Enemy_Image_Attack_1_";

	strcat_s(str, _Enemy->getEnemyInfo()->imageName);

	string Idle_Image = str;


	_Enemy->setEnemyImageKey(str);

	_Enemy->setEnemyImage(IMAGEMANAGER->findImage(Idle_Image));

	frameCount = 0;
	frameUpdateCount = 5;
	
	_Enemy->setEnemyFrameX(0);

	if (_Enemy->getEnemyInfo()->isRight) _Enemy->setEnemyFrameY(0);
	else _Enemy->setEnemyFrameY(1);


}

void Enemy_Attack::call_Attack_2_function(Enemy_Basic* _Enemy)
{
	Enemy_State* Attack_2;

	Attack_2 = new Enemy_Attack_2();

	_Enemy->set_Enemy_State(Attack_2);
}

void Enemy_Attack::ImageUpdateFunc(Enemy_Basic * _Enemy)
{
	frameCount++;

	if (frameCount % frameUpdateCount == 0)
	{
		if (_Enemy->getEnemyInfo()->isRight)
		{
			_Enemy->setEnemyFrameY(0);
			_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->CurrentframeX + 1);

		/*	if (_Enemy->getEnemyInfo()->CurrentframeX > _Enemy->getEnemyInfo()->_image->getMaxFrameX())
			{
				call_Attack_2_function(_Enemy);
			}*/
		}
		else
		{
			_Enemy->setEnemyFrameY(1);
			_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->CurrentframeX + 1);

			//if (_Enemy->getEnemyInfo()->CurrentframeX > _Enemy->getEnemyInfo()->_image->getMaxFrameX())
			//{
			//	call_Attack_2_function(_Enemy);
			//}
		}
	}
}
