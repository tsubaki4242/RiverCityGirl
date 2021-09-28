#include "stdafx.h"
#include "stage_1stFloor_room.h"

HRESULT stage_1stFloor_room::init()
{
	// ���
	IMAGEMANAGER->addImage("L1_ed_bg", "img/stage/stage7/L1_ed_bg.bmp", 2112, 864, true, RGB(255, 0, 255));
	_background1 = IMAGEMANAGER->findImage("L1_ed_bg");
	IMAGEMANAGER->addImage("L1_ed_bg_Pixel", "img/stage/stage7/L1_ed_bg_Pixel.bmp", 2112, 1092, true, RGB(255, 0, 255));
	_background2 = IMAGEMANAGER->findImage("L1_ed_bg_Pixel");
	_background3 = IMAGEMANAGER->findImage("BackGround3");

	// �繰

	IMAGEMANAGER->addImage("L3_teacher_desk1", "img/stage/stage7/L3_teacher_desk1.bmp", 423, 168, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("L1_projection_screen", "img/stage/stage7/L1_projection_screen.bmp", 675, 477, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("L3_children_desks", "img/stage/stage7/L3_children_desks.bmp", 1752, 126, true, RGB(255, 0, 255));


	// �÷��̾� �ʱ�ȭ
	DATAMANAGER->setBgmKey("River City Girls OST - 6 - Lunch Money");
	DATAMANAGER->setStageKey("L1_ed_bg_Pixel");
	stage::init();

	// �� ����
	_door1 = RectMakeCenter(200, 770, 200, 260);
	_door1Alpha = 0;
	_door2 = RectMakeCenter(1880, 770, 200, 260);
	_door2Alpha = 0;
	cameraWork();
	_em->setting_Unit_school_girl(1056 - 200, 750);
	_em->setting_Unit_school_girl(1056 + 200, 600);
	_em->setting_Unit_school_boy(1056, 700);
	return S_OK;
}

void stage_1stFloor_room::release()
{
}

void stage_1stFloor_room::update()
{

	KEYANIMANAGER->update();
	// ī�޶� ó��
	cameraWork();
	stage::update();
	doorWork();
}

void stage_1stFloor_room::render()
{
	RENDERMANAGER->push_BackRenderInfo(-1000, "L1_ed_bg", 0, 114, true);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		RENDERMANAGER->push_BackRenderInfo(-999, "L1_ed_bg_Pixel", 0, 0, true);
	}
	////////////////////
	_player->render();


	RENDERMANAGER->push_BackRenderInfo(525 + 182, "L3_teacher_desk1", 843, 580, true);
	RENDERMANAGER->push_BackRenderInfo(3000, "L3_children_desks", 180, 854, true);
	RENDERMANAGER->push_BackRenderInfo(-999, "L1_projection_screen", 700, 114, true);

	
	RENDERMANAGER->push_BackRenderInfo(3000, "UI_UNLOCKED_DOOR", 210, 580, false, true, _door1Alpha);
	RENDERMANAGER->push_BackRenderInfo(3000, "UI_UNLOCKED_DOOR", 1900, 580, false, true, _door2Alpha);

	// �� ���� ���� �̹��� ����
	RENDERMANAGER->render(getMemDC());
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

void stage_1stFloor_room::cameraWork()
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

void stage_1stFloor_room::doorWork()
{
	if (IntersectRect(&_temp, &_tagPlayer->rc, &_door1))
	{
		if (_door1Alpha < 200)
			_door1Alpha += 5;
		if (KEYMANAGER->isOnceKeyDown('Y'))
		{
			DATAMANAGER->setPlayerData(2138, 785, 0, DATAMANAGER->getPlayerData().hp);
			DATAMANAGER->setCamera(0, -189);
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
			DATAMANAGER->setPlayerData(280, 755, 0, DATAMANAGER->getPlayerData().hp);
			DATAMANAGER->setCamera(0, -190);
			_fade = false;
			_targetStageKey = "1��ȦA";
		}
	}
	else if (_door2Alpha > 0)
	{
		_door2Alpha -= 5;
	}
}

