#include "stdafx.h"
#include "stage_2ndFloor_room.h"

HRESULT stage_2ndFloor_room::init()
{
	// ���
	IMAGEMANAGER->addImage("L1_chemistry_bg", "img/stage/stage4/L1_chemistry_bg.bmp", 2112, 864, true, RGB(255, 0, 255));
	_background1 = IMAGEMANAGER->findImage("L1_chemistry_bg");
	IMAGEMANAGER->addImage("L1_chemistry_bg_Pixel", "img/stage/stage4/L1_chemistry_bg_Pixel.bmp", 2112, 1092, true, RGB(255, 0, 255));

	_background2 = IMAGEMANAGER->findImage("L1_chemistry_bg_Pixel");

	_background3 = IMAGEMANAGER->findImage("BackGround3");

	// �繰
	IMAGEMANAGER->addImage("L3_children_desksA", "img/stage/stage4/L3_children_desksA.bmp", 396, 141, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("L3_children_desksB", "img/stage/stage4/L3_children_desksB.bmp", 381, 141, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("L3_children_desksC", "img/stage/stage4/L3_children_desksC.bmp", 378, 141, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("L3_children_desksD", "img/stage/stage4/L3_children_desksD.bmp", 399, 141, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("L3_teacher_desk", "img/stage/stage4/L3_teacher_desk.bmp", 411, 162, true, RGB(255, 0, 255));

	
	DATAMANAGER->setBgmKey("River City Girls OST - 6 - Lunch Money");
	DATAMANAGER->setStageKey("L1_chemistry_bg_Pixel");
	// �÷��̾� �ʱ�ȭ
	stage::init();

	// �� ����
	_door1 = RectMakeCenter(200, 770, 200, 260);
	_door1Alpha = 0;
	_door2 = RectMakeCenter(1880, 770, 200, 260);
	_door2Alpha = 0;

	// ī�޶� ����
	cameraWork();
	_em->setting_Unit_school_boy(500, 850);
	_em->setting_Unit_school_boy(1500, 850);


	return S_OK;
}

void stage_2ndFloor_room::release()
{
}

void stage_2ndFloor_room::update()
{
	KEYANIMANAGER->update();
	// ī�޶� ó��
	cameraWork();
	stage::update();
	doorWork();
}

void stage_2ndFloor_room::render()
{
	RENDERMANAGER->push_BackRenderInfo(-1000, "L1_chemistry_bg", 0, 114, true);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		RENDERMANAGER->push_BackRenderInfo(-999, "L1_chemistry_bg_Pixel", 0, 0, true);
	}
	////////////////////
	_player->render();

	RENDERMANAGER->push_BackRenderInfo(525 + 162, "L3_teacher_desk", 858, 525, true);

	RENDERMANAGER->push_BackRenderInfo(838 + 141, "L3_children_desksA", 180, 838, true);
	RENDERMANAGER->push_BackRenderInfo(838 + 141, "L3_children_desksB", 564, 838, true);
	RENDERMANAGER->push_BackRenderInfo(838 + 141, "L3_children_desksC", 1168, 838, true);
	RENDERMANAGER->push_BackRenderInfo(838 + 141, "L3_children_desksD", 1534, 838, true);

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

void stage_2ndFloor_room::cameraWork()

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

void stage_2ndFloor_room::doorWork()
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
			_targetStageKey = "2��ȦA";
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
			_targetStageKey = "2��ȦB";
		}
	}
	else if (_door2Alpha > 0)
	{
		_door2Alpha -= 5;
	}
}
