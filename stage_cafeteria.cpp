#include "stdafx.h"
#include "stage_cafeteria.h"

HRESULT stage_cafeteria::init()
{
	
	// ���
	IMAGEMANAGER->addImage("cafeteria_background", "img/stage/stage10/cafeteria_background.bmp", 2862, 837, true, RGB(255, 0, 255));
	_background1 = IMAGEMANAGER->findImage("cafeteria_background");
	IMAGEMANAGER->addImage("cafeteria_background_Pixel", "img/stage/stage10/cafeteria_background_Pixel.bmp", 2862, 1065, true, RGB(255, 0, 255));
	_background2 = IMAGEMANAGER->findImage("cafeteria_background_Pixel");
	_background3 = IMAGEMANAGER->findImage("BackGround3");

	IMAGEMANAGER->addImage("cafeteria_snackmachine", "img/stage/stage10/cafeteria_snackmachine.bmp", 255, 255, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("cafeteria_table1", "img/stage/stage10/cafeteria_table1.bmp", 339, 156, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("cafeteria_table2", "img/stage/stage10/cafeteria_table2.bmp", 366, 150, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("cafeteria_table3", "img/stage/stage10/cafeteria_table3.bmp", 339, 165, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("cafeteria_table4", "img/stage/stage10/cafeteria_table4.bmp", 366, 171, true, RGB(255, 0, 255));

	// �÷��̾� �ʱ�ȭ
	DATAMANAGER->setBgmKey("River City Girls OST - 4 - Detention");
	DATAMANAGER->setStageKey("cafeteria_background_Pixel");
	
	// �� ����
	
	
	// ī�޶� ����
	stage::init();
	cameraWork();
	_door1 = RectMakeCenter(100, 770, 200, 260);
	_door1Alpha = 0;
	_door2 = RectMakeCenter(2720, 770, 200, 260);
	_door2Alpha = 0;
	_em->setting_Unit_school_girl(1880,	670);
	_em->setting_Unit_school_boy(1240, 750);
	_em->setting_Unit_school_girl(540, 670);
	return S_OK;
}

void stage_cafeteria::release()
{
}

void stage_cafeteria::update()
{
	cameraWork();
	stage::update();
	doorWork();
}

void stage_cafeteria::render()
{
	RENDERMANAGER->push_BackRenderInfo(-1000, "cafeteria_background", 0, 114, true);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		RENDERMANAGER->push_BackRenderInfo(-999, "cafeteria_background_Pixel", 0, 0, true);
	}
	////////////////////
	_player->render();

	RENDERMANAGER->push_BackRenderInfo(100, "cafeteria_snackmachine", 2306, 357, true);
	RENDERMANAGER->push_BackRenderInfo(722 + 156, "cafeteria_table1", 330, 722, true);
	RENDERMANAGER->push_BackRenderInfo(805 + 156, "cafeteria_table2", 870, 805, true);
	RENDERMANAGER->push_BackRenderInfo(790 + 156, "cafeteria_table3", 1480, 790, true);
	RENDERMANAGER->push_BackRenderInfo(715 + 156, "cafeteria_table4", 2067, 715, true);




	// �� ���� ���� �̹��� ����
	RENDERMANAGER->render(getMemDC());
	RENDERMANAGER->push_BackRenderInfo(3000, "UI_UNLOCKED_DOOR", 110, 580, false, true, _door1Alpha);
	RENDERMANAGER->push_BackRenderInfo(3000, "UI_UNLOCKED_DOOR", 2720, 580, false, true, _door2Alpha);
	_background3->render(getMemDC());

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		RECT rc = RectMake(_door1.left + RENDERMANAGER->getCameraX(), _door1.top + RENDERMANAGER->getCameraY(),
			_door1.right - _door1.left, _door1.bottom - _door1.top);
		Rectangle(getMemDC(), rc);
		rc = RectMake(_door2.left + RENDERMANAGER->getCameraX(), _door2.top + RENDERMANAGER->getCameraY(),
			_door2.right - _door2.left, _door2.bottom - _door2.top);
		Rectangle(getMemDC(), rc);
		rc = RectMake(_tagPlayer->rc.left + RENDERMANAGER->getCameraX(), _tagPlayer->rc.top + RENDERMANAGER->getCameraY(), _tagPlayer->rc.right - _tagPlayer->rc.left, _tagPlayer->rc.bottom - _tagPlayer->rc.top);
		Rectangle(getMemDC(), rc);
	}
	stage::render();
}

void stage_cafeteria::cameraWork()
{
	if (_tagPlayer->x > WINSIZEX / 2)
	{
		RENDERMANAGER->setCameraX(-(_tagPlayer->x - WINSIZEX / 2));
	}
	if (RENDERMANAGER->getCameraX() < -_background1->getWidth() + WINSIZEX)
	{
		RENDERMANAGER->setCameraX(-_background1->getWidth() + WINSIZEX);
	}
	if (_tagPlayer->y - 200 - _tagPlayer->z < _background1->getHeight() - WINSIZEY / 2 + 114)
	{
		RENDERMANAGER->setCameraY(-(_tagPlayer->y - WINSIZEY / 2 + 114 - 200 - _tagPlayer->z));
	}
	if (_tagPlayer->y - _tagPlayer->z < WINSIZEY / 2 - 114 + 200)
	{
		RENDERMANAGER->setCameraY(0);
	}
}

void stage_cafeteria::doorWork()

{
	if (IntersectRect(&_temp, &_tagPlayer->rc, &_door1))
	{
		if (_door1Alpha < 200)
			_door1Alpha += 5;
		if (KEYMANAGER->isOnceKeyDown('Y'))
		{
			DATAMANAGER->setPlayerData(1300, 620, 0, DATAMANAGER->getPlayerData().hp);
			DATAMANAGER->setCamera(0, 0);
			_fade = false;
			_targetStageKey = "1��ȦB";
		}
	}
	else if (_door1Alpha > 0)
	{
		_door1Alpha -= 5;
	}

	if (IntersectRect(&_temp, &_tagPlayer->rc, &_door2))
	{
		if (_door2Alpha < 200)
			_door2Alpha += 5;
		if (KEYMANAGER->isOnceKeyDown('Y'))
		{
			DATAMANAGER->setPlayerData(1250, 940, 0, DATAMANAGER->getPlayerData().hp);
			DATAMANAGER->setCamera(0, 0);
			_fade = false;
			_targetStageKey = "������Ʈ��";
		}
	}
	else if (_door2Alpha > 0)
	{
		_door2Alpha -= 5;
	}
}