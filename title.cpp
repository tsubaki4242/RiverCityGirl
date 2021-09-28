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
			SCENEMANAGER->changeScene("¼¼ÀÌºê·Îµå");

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
	IMAGEMANAGER->addImage("Å¸ÀÌÆ²¹è°æ", "UI/titleBackGround.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Å¸ÀÌÆ²ÇÃ·¡½¬", "UI/ÇÃ·¹½¬.bmp", 1500, 900, true, RGB(255, 0, 255),true);
	IMAGEMANAGER->addImage("Å×µÎ¸®", "UI/title1.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Å¸ÀÌÆ²", "UI/logo.bmp", 571, 326, true, RGB(23, 23, 23));
	IMAGEMANAGER->addImage("¸®¹ö", "UI/title_1.bmp", 356, 132, true, RGB(255, 48, 90),true);
	IMAGEMANAGER->addImage("½ÃÆ¼", "UI/title_2.bmp", 259, 161, true, RGB(255, 48, 90), true);
	IMAGEMANAGER->addImage("°ÉÁî", "UI/title_3.bmp", 563, 231, true, RGB(255, 48, 90), true);
	IMAGEMANAGER->addImage("´Ü¹ß¸Ó¸®", "UI/title2.bmp", 429, 750, true, RGB(23, 23, 23), true);
	IMAGEMANAGER->addImage("ÄìÄÚ", "UI/title3.bmp", 497, 760, true, RGB(23, 23, 23), true);
	//======================================================
	IMAGEMANAGER->addImage("½ÃÀÛ", "UI/°ÔÀÓ½ÃÀÛ.bmp", 249, 80, true, RGB(255, 48, 90), true);
	IMAGEMANAGER->addImage("³ª°¡±â", "UI/³ª°¡±â.bmp", 249, 80, true, RGB(255, 48, 90), true);
	IMAGEMANAGER->addImage("È­»ì", "UI/È­»ìÇ¥.bmp", 46, 53, true, RGB(255, 48, 90), true);

	IMAGEMANAGER->addFrameImage("¸®¹öÇÁ·¹ÀÓ", "UI/¸®¹ö.bmp", 6408, 396, 6, 1, true, RGB(255, 48, 90), true);
	IMAGEMANAGER->addFrameImage("½ÃÆ¼ÇÁ·¹ÀÓ", "UI/½ÃÆ¼.bmp", 4662, 483, 6, 1, true, RGB(255, 48, 90), true);
	IMAGEMANAGER->addFrameImage("°ÉÁîÇÁ·¹ÀÓ", "UI/°ÉÁî2.bmp", 10134, 693,6, 1, true, RGB(255, 48, 90), true);
	EFFECTMANAGER->addEffect("¹ÝÂ¦", "UI/¹ÝÂ¦.bmp", 620, 113, 124, 113, 1, 0.3f, 2, 255, 0, 255);
	EFFECTMANAGER->addEffect("¹ÝÂ¦1", "UI/¹ÝÂ¦2.bmp", 440, 80, 88, 80, 1, 0.3f, 2, 255, 0, 255);
	EFFECTMANAGER->addEffect("¹ÝÂ¦2", "UI/¹ÝÂ¦3.bmp", 265, 49, 53, 49, 1, 0.3f, 2, 255, 0, 255);


	IMAGEMANAGER->addFrameImage("È­¿°1", "UI/1.bmp", 15000, 900, 10, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("È­¿°2", "UI/2.bmp", 15000, 900, 10, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("È­¿°3", "UI/3.bmp", 15000, 900, 10, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("È­¿°4", "UI/4.bmp", 15000, 900, 10, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("È­¿°5", "UI/5.bmp", 15000, 900, 10, 1, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("È­¿°6", "UI/6.bmp", 15000, 900, 10, 1, true, RGB(255, 0, 255), true);

	_flashGround = IMAGEMANAGER->findImage("Å¸ÀÌÆ²ÇÃ·¡½¬");
	_backGroundTile = IMAGEMANAGER->findImage("Å¸ÀÌÆ²¹è°æ");
	_Line = IMAGEMANAGER->findImage("Å×µÎ¸®");
	_fire = IMAGEMANAGER->findImage("È­¿°1");
	_title = IMAGEMANAGER->findImage("Å¸ÀÌÆ²");
	_river = IMAGEMANAGER->findImage("¸®¹öÇÁ·¹ÀÓ");
	_city = IMAGEMANAGER->findImage("½ÃÆ¼ÇÁ·¹ÀÓ");
	_girls = IMAGEMANAGER->findImage("°ÉÁîÇÁ·¹ÀÓ");
	_P1 = IMAGEMANAGER->findImage("ÄìÄÚ");
	_P2 = IMAGEMANAGER->findImage("´Ü¹ß¸Ó¸®");


	_fireAni = FIRE_1;
	_flash = 255;
	_start = RectMake(300,450,249,80);
	_exit = RectMake(320, 530, 249, 80);
	_arrow = RectMake(250, 540, 46, 53);
	_startImg = IMAGEMANAGER->findImage("½ÃÀÛ");
	_exitImg = IMAGEMANAGER->findImage("³ª°¡±â");
	_arrowImg = IMAGEMANAGER->findImage("È­»ì");

}

void title::Twinkle()
{
	int R = rand() % 800;
	if (R == 1)
	{
		EFFECTMANAGER->play("¹ÝÂ¦", 150, 300);	
	}
	if (R == 20)
	{

	EFFECTMANAGER->play("¹ÝÂ¦1", 300, 130);
	}
	if (R == 30)
	{
	EFFECTMANAGER->play("¹ÝÂ¦", 250, 400);
	}
	if (R == 40)
	{
	EFFECTMANAGER->play("¹ÝÂ¦2", 500, 130);
	}
	if (R == 50)
	{
	EFFECTMANAGER->play("¹ÝÂ¦1", 370, 380);

	}
	if (R == 60)
	{
		EFFECTMANAGER->play("¹ÝÂ¦2", 370, 250);
	}
	if (R == 70)
	{
		EFFECTMANAGER->play("¹ÝÂ¦1", 500, 260);
	}
	if (R == 80)
	{
		EFFECTMANAGER->play("¹ÝÂ¦1", 500, 400);
	}
	if (R == 90)
	{
		EFFECTMANAGER->play("¹ÝÂ¦2", 450, 300);
	}
	if (R == 100)
	{
		EFFECTMANAGER->play("¹ÝÂ¦", 480, 150);
	}
	if (R == 110)
	{
		EFFECTMANAGER->play("¹ÝÂ¦2", 550, 150);
	}
	if (R == 170)
	{
		EFFECTMANAGER->play("¹ÝÂ¦", 600, 200);
	}
	if (R == 120)
	{
	EFFECTMANAGER->play("¹ÝÂ¦1", 630, 150);
	}
	if (R == 130)
	{

	EFFECTMANAGER->play("¹ÝÂ¦2", 700, 300);
	}
	if (R == 140)
	{
	EFFECTMANAGER->play("¹ÝÂ¦2", 600, 300);
	}
	if (R == 150)
	{
	EFFECTMANAGER->play("¹ÝÂ¦", 550, 350);
	}
	if (R == 160)
	{
	EFFECTMANAGER->play("¹ÝÂ¦", 650, 400);
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
			_fire = IMAGEMANAGER->findImage("È­¿°1");
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
			_fire = IMAGEMANAGER->findImage("È­¿°2");
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
			_fire = IMAGEMANAGER->findImage("È­¿°3");
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
			_fire = IMAGEMANAGER->findImage("È­¿°4");
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
			_fire = IMAGEMANAGER->findImage("È­¿°5");
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
			_fire = IMAGEMANAGER->findImage("È­¿°6");
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
