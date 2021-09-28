#include "stdafx.h"

#include "Enemy_Basic.h"


#include "Enemy_KnockDown_2.h"
#include "Enemy_Wake_Up.h"



Enemy_State * Enemy_KnockDown_2::input_state(Enemy_Basic * _Enemy, bool reverse, int targetX, int targetY)
{

	if (_Enemy->getRecoveryCount() > 50)
	{
		_Enemy->setRecoveryCountZero();
		return new Enemy_Wake_Up();
	}

	return nullptr;
}

void Enemy_KnockDown_2::update(Enemy_Basic * _Enemy, int targetX, int targetY)
{
	ImageUpdateFunc(_Enemy);

	
	_Enemy->setRecoveryCount();
}

void Enemy_KnockDown_2::release(Enemy_Basic * _Enemy)
{
}

void Enemy_KnockDown_2::enter_this_state(Enemy_Basic * _Enemy)
{
	_Enemy->setEnemyTestText("KNOCK_DOWN_1");
	_Enemy->set_Enemy_State_Enum(KNOCK_DOWN_2);



	char str[128] = "Enemy_Image_KnockDown_2_";

	strcat_s(str, _Enemy->getEnemyInfo()->imageName);

	string Idle_Image = str;

	_Enemy->setEnemyImage(IMAGEMANAGER->findImage(Idle_Image));
	_Enemy->setEnemyImageError_Y(10);
	_Enemy->setEnemyImageError(10);
	_Enemy->setEnemyFrameX(0);
	frameCount = 0;
	frameUpdateCount = 20;

}

void Enemy_KnockDown_2::ImageUpdateFunc(Enemy_Basic * _Enemy)
{
	frameCount++;

	if (frameCount % frameUpdateCount == 0)
	{
		if (_Enemy->getEnemyInfo()->isRight)
		{
			_Enemy->setEnemyFrameY(0);
			_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->CurrentframeX + 1);

			if (_Enemy->getEnemyInfo()->CurrentframeX > _Enemy->getEnemyInfo()->_image->getMaxFrameX())
			{
				_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->_image->getMaxFrameX());
			}

		}
		else
		{
			_Enemy->setEnemyFrameY(1);
			_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->CurrentframeX + 1);

			if (_Enemy->getEnemyInfo()->CurrentframeX > _Enemy->getEnemyInfo()->_image->getMaxFrameX())
			{
				_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->_image->getMaxFrameX());
			}
		}
	}

	
}
