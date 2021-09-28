#include "stdafx.h"
#include "stage_2ndFloor_HallA.h"

HRESULT stage_2ndFloor_HallA::init()
{

	// ���ȭ��
	IMAGEMANAGER->addImage("2ndFloor_HallA", "img/stage/stage3/2ndFloor_HallA.bmp", 2400, 864, true, RGB(255, 0, 255));
	_background1 = IMAGEMANAGER->findImage("2ndFloor_HallA");
	IMAGEMANAGER->addImage("2ndFloor_HallA_Pixel", "img/stage/stage3/2ndFloor_HallA_Pixel.bmp", 2400, 1092, true, RGB(255, 0, 255));
	_background2 = IMAGEMANAGER->findImage("2ndFloor_HallA_Pixel");
	_background3 = IMAGEMANAGER->findImage("BackGround3");
	
	// ��� �繰��
	IMAGEMANAGER->addImage("L3_smaller_cupboard", "img/stage/stage3/L3_smaller_cupboard.bmp", 171, 261, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("cafeteria_snackmachine", "img/stage/stage3/cafeteria_snackmachine.bmp", 255, 255, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("L3_lockers3", "img/stage/stage3/L3_lockers3.bmp", 420, 279, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("L2_pillar1", "img/stage/stage3/L2_pillar1.bmp", 207, 864, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("L2_pillar2", "img/stage/stage3/L2_pillar2.bmp", 198, 543, true, RGB(255, 0, 255));


	DATAMANAGER->setStageKey("2ndFloor_HallA_Pixel");
	DATAMANAGER->setBgmKey("River City Girls OST - 5 - Knock Out");
	stage::init();

	// �� ����
	_door1 = RectMakeCenter(1290, 600, 280, 40);
	_door1Alpha = 0;
	_door2 = RectMakeCenter(2180, 770, 200, 260);
	_door2Alpha = 0;
	// ī�޶� ����
	cameraWork();
	_em->setting_Unit_school_girl(500, 926);
	_em->setting_Unit_school_boy(500, 850);
	return S_OK;
}

void stage_2ndFloor_HallA::release()
{
}

void stage_2ndFloor_HallA::update()
{
	
	KEYANIMANAGER->update();
	// ī�޶� ó��
	cameraWork();
	stage::update();
	doorWork();
}

void stage_2ndFloor_HallA::render()
{
	RENDERMANAGER->push_BackRenderInfo(-1000, "2ndFloor_HallA", 0, 114, true);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		RENDERMANAGER->push_BackRenderInfo(-999, "2ndFloor_HallA_Pixel", 0, 0, true);
	}
	// �繰
	RENDERMANAGER->push_BackRenderInfo(390, "L3_smaller_cupboard", 325, 400, true);
	RENDERMANAGER->push_BackRenderInfo(390, "cafeteria_snackmachine", 1470, 400, true);
	RENDERMANAGER->push_BackRenderInfo(390, "L3_lockers3", 1670, 400, true);

	
	// ���
	RENDERMANAGER->push_BackRenderInfo(3000, "L2_pillar1", 489, 114, true, true, 150);
	RENDERMANAGER->push_BackRenderInfo(0, "L2_pillar2", 870, 114, true);

	_player->render();
	RENDERMANAGER->render(getMemDC());
	RENDERMANAGER->push_BackRenderInfo(3000, "UI_UNLOCKED_DOOR", 1300, 400, false, true, _door1Alpha);
	RENDERMANAGER->push_BackRenderInfo(3000, "UI_UNLOCKED_DOOR", 2200, 580, false, true, _door2Alpha);
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

void stage_2ndFloor_HallA::cameraWork()
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

void stage_2ndFloor_HallA::doorWork()
{
	if (IntersectRect(&_temp, &_tagPlayer->rc, &_door1))
	{
		if (_door1Alpha < 200)
			_door1Alpha += 5;
		if (KEYMANAGER->isOnceKeyDown('Y'))
		{
			DATAMANAGER->setPlayerData(1395, 610, 0, DATAMANAGER->getPlayerData().hp);
			DATAMANAGER->setCamera(0, 0);
			_fade = false;
			_targetStageKey = "3������";
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
			DATAMANAGER->setPlayerData(252, 768, 0, DATAMANAGER->getPlayerData().hp);
			DATAMANAGER->setCamera(0, -190);
			_fade = false;
			_targetStageKey = "2����";
		}
	}
	else if (_door2Alpha > 0)
	{
		_door2Alpha -= 5;
	}
}
