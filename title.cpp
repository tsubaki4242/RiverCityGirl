#include "stdafx.h"
#include "title.h"

HRESULT title::init()
{

	imglist();
	_P1X = 1700;
	_P2X = -100;
	_arrowStat = 0;
	return S_OK;
}

void title::release()
{
}

void title::update()
{
	if (_flash >= 0)
	{
		_flash -= 50;
	}
	if (_flash <= 0)
	{
		_flash = 0;
	}
	if (_P1X >= 950)
	{
		_P1X-=60;

	}
	if (_P2X <= 620)
	{
		_P2X+=60;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_arrowStat++;
		SOUNDMANAGER->play("menu_cursor");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_arrowStat++;
		SOUNDMANAGER->play("menu_cursor");
	}

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		if (_arrowStat == 0)
		{
			SOUNDMANAGER->play("menu_confirm");
			SCENEMANAGER->changeScene("세이브로드");

		}
		else
		{
			SOUNDMANAGER->play("menu_confirm");
			exit(0);
		}
	}

	if (_arrowStat >= 2)
	{
		_arrowStat = 0;
	}
	if (_arrowStat == 0)
	{
		_arrow = RectMake(250, 475, 46, 53);
	}
	if (_arrowStat == 1)
	{
		_arrow = RectMake(295, 550, 46, 53);
	}
	Twinkle();
	EFFECTMANAGER->update();
	imgFrame();
}

void title::render()
{

	_backGroundTile->render(getMemDC());
	_fire->alphaFrameRender(getMemDC(), 0, 0, 200);

	_title->render(getMemDC(),120 ,120);



	_P1->render(getMemDC(), _P1X, 120);
	_P2->render(getMemDC(), _P2X, 130);


	_river->alphaFrameRender(getMemDC(), -250, -15, 150);
	_city->alphaFrameRender(getMemDC(), 170, -45, 150);
	_girls->alphaFrameRender(getMemDC(), -430, 0, 150);
	_startImg->render(getMemDC(), _start.left, _start.top);
	_exitImg->render(getMemDC(), _exit.left, _exit.top);
	_arrowImg->render(getMemDC(), _arrow.left, _arrow.top);
	_Line->render(getMemDC());
	EFFECTMANAGER->render();
	_flashGround->alphaRender(getMemDC(), 0, 0, _flash);


}

void title::imglist()
{
	SOUNDMANAGER->addSound("menu_cursor", "sound/menu_cursor.wav", false, false);
	SOUNDMANAGER->addSound("menu_confirm", "sound/menu_confirm.wav", false, false);
	//====================================================
	IMAGEMANAGER->addImage("타이틀배경", "UI/titleBackGround.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("타이틀플래쉬", "UI/플레쉬.bmp", 1500, 900, true, RGB(255, 0, 255),true);
	IMAGEMANAGER->addImage("테두리", "UI/title1.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("타이틀", "UI/logo.bmp", 571, 326, true, RGB(23, 23, 23));
	IMAGEMANAGER->addImage("리버", "UI/title_1.bmp", 356, 132, true, RGB(255, 48, 90),true);
	IMAGEMANAGER->addImage("시티", "UI/title_2.bmp", 259, 161, true, RGB(255, 48, 90), true);
	IMAGEMANAGER->addImage("걸즈", "UI/title_3.bmp", 563, 231, true, RGB(255, 48, 90), true);
	IMAGEMANAGER->addImage("단발머리", "UI/title2.bmp", 429, 750, true, RGB(23, 23, 23), true);
	IMAGEMANAGER->addImage("쿄코", "UI/title3.bmp", 497, 760, true, RGB(23, 23, 23), true);
	//======================================================
	IMAGEMANAGER->addImage("시작", "UI/게임시작.bmp", 249, 80, true, RGB(255, 48, 90), true);
	IMAGEMANAGER->addImage("나가기", "UI/나가기.bmp", 249, 80, true, RGB(255, 48, 90), true);
	IMAGEMANAGER->addImage("화살", "UI/화살표.bmp", 46, 53, true, RGB(255, 48, 90), true);

	IMAGEMANAGER->addFrameImage("리버프레임", "UI/리버.bmp", 6408, 396, 6, 1, true, RGB(255, 48, 90), true);
	IMAGEMANAGER->addFrameImage("시티프레임", "UI/시티.bmp", 4662, 483, 6, 1, true, RGB(255, 48, 90), true);
	IMAGEMANAGER->addFrameImage("걸즈프레임", "UI/걸즈2.bmp", 10134, 693,6, 1, true, RGB(255, 48, 90), true);
	EFFECTMANAGER->addEffect("반짝", "UI/반짝.bmp", 620, 113, 124, 113, 1, 0.3f, 2, 255, 0, 255);
	EFFECTMANAGER->addEffect("반짝1", "UI/반짝2.bmp", 440, 80, 88, 80, 1, 0.3f, 2, 255, 0, 255);
	EFFECTMANAGER->addEffect("반짝2", "UI/반짝3.bmp", 265, 49, 53, 49, 1, 0.3f, 2, 255, 0, 255);


	IMAGEMANAGER->addFrameImage("화염1", "UI/1.bmp", 15000, 900, 10, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("화염2", "UI/2.bmp", 15000, 900, 10, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("화염3", "UI/3.bmp", 15000, 900, 10, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("화염4", "UI/4.bmp", 15000, 900, 10, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("화염5", "UI/5.bmp", 15000, 900, 10, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("화염6", "UI/6.bmp", 15000, 900, 10, 1, true, RGB(255, 0, 255), true);

	_flashGround = IMAGEMANAGER->findImage("타이틀플래쉬");
	_backGroundTile = IMAGEMANAGER->findImage("타이틀배경");
	_Line = IMAGEMANAGER->findImage("테두리");
	_fire = IMAGEMANAGER->findImage("화염1");
	_title = IMAGEMANAGER->findImage("타이틀");
	_river = IMAGEMANAGER->findImage("리버프레임");
	_city = IMAGEMANAGER->findImage("시티프레임");
	_girls = IMAGEMANAGER->findImage("걸즈프레임");
	_P1 = IMAGEMANAGER->findImage("쿄코");
	_P2 = IMAGEMANAGER->findImage("단발머리");


	_fireAni = FIRE_1;
	_flash = 255;
	_start = RectMake(300,450,249,80);
	_exit = RectMake(320, 530, 249, 80);
	_arrow = RectMake(250, 540, 46, 53);
	_startImg = IMAGEMANAGER->findImage("시작");
	_exitImg = IMAGEMANAGER->findImage("나가기");
	_arrowImg = IMAGEMANAGER->findImage("화살");

}

void title::Twinkle()
{
	int R = rand() % 800;
	if (R == 1)
	{
		EFFECTMANAGER->play("반짝", 150, 300);	
	}
	if (R == 20)
	{

	EFFECTMANAGER->play("반짝1", 300, 130);
	}
	if (R == 30)
	{
	EFFECTMANAGER->play("반짝", 250, 400);
	}
	if (R == 40)
	{
	EFFECTMANAGER->play("반짝2", 500, 130);
	}
	if (R == 50)
	{
	EFFECTMANAGER->play("반짝1", 370, 380);

	}
	if (R == 60)
	{
		EFFECTMANAGER->play("반짝2", 370, 250);
	}
	if (R == 70)
	{
		EFFECTMANAGER->play("반짝1", 500, 260);
	}
	if (R == 80)
	{
		EFFECTMANAGER->play("반짝1", 500, 400);
	}
	if (R == 90)
	{
		EFFECTMANAGER->play("반짝2", 450, 300);
	}
	if (R == 100)
	{
		EFFECTMANAGER->play("반짝", 480, 150);
	}
	if (R == 110)
	{
		EFFECTMANAGER->play("반짝2", 550, 150);
	}
	if (R == 170)
	{
		EFFECTMANAGER->play("반짝", 600, 200);
	}
	if (R == 120)
	{
	EFFECTMANAGER->play("반짝1", 630, 150);
	}
	if (R == 130)
	{

	EFFECTMANAGER->play("반짝2", 700, 300);
	}
	if (R == 140)
	{
	EFFECTMANAGER->play("반짝2", 600, 300);
	}
	if (R == 150)
	{
	EFFECTMANAGER->play("반짝", 550, 350);
	}
	if (R == 160)
	{
	EFFECTMANAGER->play("반짝", 650, 400);
	}







}

void title::imgFrame()
{
	_count++;
	if (_count % 1 == 0)
	{
		_river->setFrameY(0);
		_river->setFrameX(_index2);
		_city->setFrameY(0);
		_city->setFrameX(_index2);
		_girls->setFrameY(0);
		_girls->setFrameX(_index2);
		if (_index2 <= 6 && _index2 >= 0)
		{
			_index2++;
		}

	}
	if (_count % 3 == 0)
	{
		if (_fireAni == FIRE_1)
		{
			_fire = IMAGEMANAGER->findImage("화염1");
			_fire->setFrameY(0);
			_fire->setFrameX(_index);
			_index++;

			if (_index >= 10)
			{
				_fireAni = FIRE_2;
				_index = 0;
			}
		}
		if (_fireAni == FIRE_2)
		{
			_fire = IMAGEMANAGER->findImage("화염2");
			_fire->setFrameY(0);
			_fire->setFrameX(_index);
			_index++;

			if (_index >= 10)
			{
				_fireAni = FIRE_3;
				_index = 0;
			}
		}
		if (_fireAni == FIRE_3)
		{
			_fire = IMAGEMANAGER->findImage("화염3");
			_fire->setFrameY(0);
			_fire->setFrameX(_index);
			_index++;

			if (_index >= 10)
			{
				_fireAni = FIRE_4;
				_index = 0;
			}
		}
		if (_fireAni == FIRE_4)
		{
			_fire = IMAGEMANAGER->findImage("화염4");
			_fire->setFrameY(0);
			_fire->setFrameX(_index);
			_index++;

			if (_index >= 10)
			{
				_fireAni = FIRE_5;
				_index = 0;
			}
		}
		if (_fireAni == FIRE_5)
		{
			_fire = IMAGEMANAGER->findImage("화염5");
			_fire->setFrameY(0);
			_fire->setFrameX(_index);
			_index++;

			if (_index >= 10)
			{
				_fireAni = FIRE_6;
				_index = 0;
			}
		}
		if (_fireAni == FIRE_6)
		{
			_fire = IMAGEMANAGER->findImage("화염6");
			_fire->setFrameY(0);
			_fire->setFrameX(_index);
			_index++;

			if (_index >= 10)
			{
				_fireAni = FIRE_1;
				_index = 0;
			}
		}
		_count = 0;
	}
}
