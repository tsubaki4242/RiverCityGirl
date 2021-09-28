#include "stdafx.h"
#include "Enemy_Basic.h"

#include "Enemy_Idle_Boss.h"
#include "Enemy_Move_Boss.h"
#include "Enemy_Attack_1_Boss.h"
#include "Enemy_Power_Attack_Boss.h"
#include "Enemy_Jump_Attack_Ready.h"
#include "Enemy_Dash_Attack_Ready.h"

#include "Enemy_Attack_3_Boss.h"
#include "Enemy_Tount_Boss.h"

#include "Enemy_Power_Up_Boss.h"


Enemy_State * Enemy_Idle_Boss::input_state(Enemy_Basic * _Enemy, bool reverse, int targetX, int targetY)
{

	switch (_Enemy->getcurrentPhase())
	{
	case PHASE_1:

		if (_Enemy->getEnemyInfo()->Hp < _Enemy->getEnemyInfo()->maxHp * 0.7f)
		{
			_Enemy->setChangePhase(PHASE_2);

			return new Enemy_Power_Up_Boss();
		}
		break;
	case PHASE_2:



		if (_Enemy->getEnemyInfo()->Hp < _Enemy->getEnemyInfo()->maxHp * 0.35f)
		{
			_Enemy->setChangePhase(PHASE_3);
			return new Enemy_Power_Up_Boss();
		}
		break;
	}



	switch (_Enemy->getBOSS_AI_TRIGGER())
	{
	case NORMAL_ATTACK_TRIGGER_BOSS:
		return new Enemy_Move_Boss();
		break;
	case POWER_ATTACK_TRIGGER_BOSS:
		return new Enemy_Move_Boss();
		break;
	case POWER_ATTACK_2_TRIGGER_BOSS:
		return new Enemy_Move_Boss();
		break;
	case TAKKLE_TRIGGER_BOSS:
		return new Enemy_Dash_Attack_Ready();
		break;
	case METEOR_JUMP_TRIGGER_BOSS:
		return new Enemy_Jump_Attack_Ready();
		break;
	}


	return nullptr;
}

void Enemy_Idle_Boss::update(Enemy_Basic * _Enemy, int targetX, int targetY)
{
	if (_Enemy->getEnemyInfo()->x < targetX) _Enemy->setEnemyReverse(true);
	else _Enemy->setEnemyReverse(false);

	ImageUpdateFunc(_Enemy);


}

void Enemy_Idle_Boss::release(Enemy_Basic * _Enemy)
{
}

void Enemy_Idle_Boss::enter_this_state(Enemy_Basic * _Enemy)
{
	_Enemy->setEnemyTestText("IDLE");
	//_Enemy->set_Enemy_State_Enum();

	_Enemy->set_Enum_State_Boss(IDLE_BOSS);

	char str[128] = "Misuzu_IDLE";

	_Enemy->setEnemyImage(IMAGEMANAGER->findImage(str));

	frameCount = 0;
	frameUpdateCount = 5;

	_Enemy->setEnemyFrameX(0);
	_Enemy->setEnemyImageError(0);

	if (_Enemy->getEnemyInfo()->isRight) _Enemy->setEnemyFrameY(0);
	else _Enemy->setEnemyFrameY(1);
}



void Enemy_Idle_Boss::ImageUpdateFunc(Enemy_Basic * _Enemy)
{
	_Enemy->setEnemyImageError(0);

	frameCount++;

	if (frameCount % frameUpdateCount == 0)
	{
		if (_Enemy->getEnemyInfo()->isRight)
		{
			_Enemy->setEnemyFrameY(0);
			_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->CurrentframeX + 1);

			if (_Enemy->getEnemyInfo()->CurrentframeX > _Enemy->getEnemyInfo()->_image->getMaxFrameX()) _Enemy->setEnemyFrameX(0);
		}
		else
		{
			_Enemy->setEnemyFrameY(1);
			_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->CurrentframeX + 1);

			if (_Enemy->getEnemyInfo()->CurrentframeX > _Enemy->getEnemyInfo()->_image->getMaxFrameX()) _Enemy->setEnemyFrameX(0);
		}
	}
}
