#include "stdafx.h"

#include "Enemy_Basic.h"


#include "Enemy_JumpAttack.h"
#include "Enemy_Idle.h"



Enemy_State * Enemy_JumpAttack::input_state(Enemy_Basic * _Enemy, bool reverse, int targetX, int targetY)
{

	if (_Enemy->getEnemyInfo()->y - _Enemy->getEnemyInfo()->z < _Enemy->getEnemyInfo()->y)
	{
		_Enemy->setEnemyGravity(0);
		_Enemy->setEnemyJumpSpeed(0);

		_Enemy->setEnemyPointZ(0);
		_Enemy->setEnemyRandomCountReset();

		_Enemy->setEnemyAiTrigger(OBSERVE_STATE_TRIGGER);

		return new Enemy_Idle();
	}

	return nullptr;
}

void Enemy_JumpAttack::update(Enemy_Basic * _Enemy, int targetX, int targetY)
{

	//_Enemy->setEnemyPointY(_Enemy->getEnemyInfo()->y
	//	- _Enemy->getEnemyInfo()->JumpPower + _Enemy->getEnemyInfo()->gravity);

	_Enemy->setEnemyGravity(_Enemy->getEnemyInfo()->gravity + GRAVITY_POWER);
	_Enemy->setEnemyPointZ(_Enemy->getEnemyInfo()->z + _Enemy->getEnemyInfo()->gravity - _Enemy->getEnemyInfo()->JumpPower);


	if (_Enemy->getEnemyInfo()->isRight) _Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x + MOVESPEED_LEFT_RIGHT * 0.5f);	
	else _Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x - MOVESPEED_LEFT_RIGHT * 0.5f);
	
	


	ImageUpdateFunc(_Enemy);

	if (!_Enemy->getEnemyInfo()->isRight)
	{
		_Enemy->Setting_AttackRect_LeftRight(SCHOOL_GIRL,
			_Enemy->getEnemyInfo()->rc.left - 15, _Enemy->getEnemyInfo()->rc.top,
			40, 30, 4, frameCount, frameUpdateCount);
		_Enemy->Setting_AttackRect_LeftRight(SCHOOL_BOY,
			_Enemy->getEnemyInfo()->rc.left - 20, _Enemy->getEnemyInfo()->rc.top,
			40, 30, 4, frameCount, frameUpdateCount);
	}
	else
	{
		_Enemy->Setting_AttackRect_LeftRight(SCHOOL_GIRL,
			_Enemy->getEnemyInfo()->rc.right + 15, _Enemy->getEnemyInfo()->rc.top,
			40, 30, 4, frameCount, frameUpdateCount);
		_Enemy->Setting_AttackRect_LeftRight(SCHOOL_BOY,
			_Enemy->getEnemyInfo()->rc.right + 20, _Enemy->getEnemyInfo()->rc.top,
			40, 30, 4, frameCount, frameUpdateCount);
	}

}

void Enemy_JumpAttack::release(Enemy_Basic * _Enemy)
{
}

void Enemy_JumpAttack::enter_this_state(Enemy_Basic * _Enemy)
{
	//Enemy_Image_Dash_Attack_School_Girl

	_Enemy->setEnemyTestText("Jump_ATTACK");
	_Enemy->set_Enemy_State_Enum(ATTACK_1);



	char str[128] = "Enemy_Image_Jump_Attack_";

	strcat_s(str, _Enemy->getEnemyInfo()->imageName);

	string Idle_Image = str;

	_Enemy->setEnemyImage(IMAGEMANAGER->findImage(Idle_Image));

	frameCount = 0;
	frameUpdateCount = 5;
	
	_Enemy->setEnemyFrameX(0);

	if (_Enemy->getEnemyInfo()->isRight) _Enemy->setEnemyFrameY(0);
	else _Enemy->setEnemyFrameY(1);
}

void Enemy_JumpAttack::call_Idle_function(Enemy_Basic * _Enemy)
{
}

void Enemy_JumpAttack::ImageUpdateFunc(Enemy_Basic * _Enemy)
{
	frameCount++;

	if (frameCount % frameUpdateCount == 0)
	{
		if (_Enemy->getEnemyInfo()->isRight)
		{
			_Enemy->setEnemyFrameY(0);
			_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->CurrentframeX + 1);

			if (_Enemy->getEnemyInfo()->CurrentframeX > _Enemy->getEnemyInfo()->_image->getMaxFrameX()) _Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->_image->getMaxFrameX());
		}
		else
		{
			_Enemy->setEnemyFrameY(1);
			_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->CurrentframeX + 1);

			if (_Enemy->getEnemyInfo()->CurrentframeX > _Enemy->getEnemyInfo()->_image->getMaxFrameX()) _Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->_image->getMaxFrameX());
		}
	}

}
