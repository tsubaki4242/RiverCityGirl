#include "stdafx.h"
#include "Enemy_Basic.h"

#include "Enemy_knockDown.h"
#include "Enemy_KnockDown_2.h"


#include "Enemy_Idle.h"

Enemy_State * Enemy_knockDown::input_state(Enemy_Basic * _Enemy, bool reverse, int targetX, int targetY)
{



	return nullptr;
}

void Enemy_knockDown::update(Enemy_Basic * _Enemy, int targetX, int targetY)
{
	_Enemy->setEnemyImageError_Y(0);

	ImageUpdateFunc(_Enemy);
	count++;

	
		if (_Enemy->getEnemyInfo()->CurrentframeX < 3)
		{
			if (_Enemy->getEnemyInfo()->isRight) _Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x - 3);
			else _Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x + 3);

			_Enemy->setEnemyPointZ(_Enemy->getEnemyInfo()->z - 3);
		}
		if (count < 10)
		{
			_Enemy->setEnemyPointZ(_Enemy->getEnemyInfo()->z -11);
			
		}
		else
		{
			if (_Enemy->getEnemyInfo()->z < 0)
			{
				_Enemy->setEnemyPointZ(_Enemy->getEnemyInfo()->z + 6);
			}
			else
			{
				_Enemy->setEnemyPointZ(0);
			}
		}

		
	

}

void Enemy_knockDown::release(Enemy_Basic * _Enemy)
{
}



void Enemy_knockDown::enter_this_state(Enemy_Basic * _Enemy)
{
	_Enemy->setEnemyTestText("KNOCK_DOWN_1");
	_Enemy->set_Enemy_State_Enum(KNOCK_DOWN);

	_Enemy->setEnemyImageError(0);

	

	//recoverCount = 0;
	count = 0;


	char str[128] = "Enemy_Image_KnockDown_1_";

	strcat_s(str, _Enemy->getEnemyInfo()->imageName);

	string Idle_Image = str;

	_Enemy->setEnemyImage(IMAGEMANAGER->findImage(Idle_Image));
	_Enemy->setEnemyFrameX(0);

	frameCount = 0;
	frameUpdateCount = 4;
	
}

void Enemy_knockDown::ImageUpdateFunc(Enemy_Basic * _Enemy)
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
				count = 0;
				//_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->_image->getMaxFrameX());
				
				Enemy_State* _state;

				_state = new Enemy_KnockDown_2();

				_Enemy->set_Enemy_State(_state);


			}

		}
		else
		{
			_Enemy->setEnemyFrameY(1);
			_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->CurrentframeX + 1);

			if (_Enemy->getEnemyInfo()->CurrentframeX > _Enemy->getEnemyInfo()->_image->getMaxFrameX())
			{
				count = 0;
				//_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->_image->getMaxFrameX());

				Enemy_State* _state;

				_state = new Enemy_KnockDown_2();

				_Enemy->set_Enemy_State(_state);


			}
		}
	}
}
