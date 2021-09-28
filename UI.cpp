#include "stdafx.h"
#include "UI.h"


HRESULT UI::init()
{
	IMAGEMANAGER->addImage("프로그레스바", "UI/프로그레스바.bmp", 414, 94, true, RGB(23, 25, 26));
	IMAGEMANAGER->addImage("프로그레스바2", "UI/프로그레스바2.bmp", 414, 94, true, RGB(23, 25, 26));
	IMAGEMANAGER->addImage("체력", "UI/체력.bmp", 26, 24, true, RGB(23, 25, 26), true);
	IMAGEMANAGER->addImage("얼굴", "UI/프로필.bmp", 150, 169, true, RGB(23, 25, 26));

	_prograssBar = IMAGEMANAGER->findImage("프로그레스바");
	_prograssBar2 = IMAGEMANAGER->findImage("프로그레스바2");
	_face  = IMAGEMANAGER->findImage("얼굴");
	for (int i = 0; i < LIFE; i++)
	{
		_lifeImg[i] = IMAGEMANAGER->findImage("체력");
	}

	_life = LIFE;
	return S_OK;
}

void UI::release()
{
}

void UI::update()
{
	_life = DATAMANAGER->getPlayerData().hp;
}

void UI::render()
{
	_prograssBar2->render(getMemDC(), 340, 35);
	for (int i = 0; i < _life; i++)
	{
		_lifeImg[i]->render(getMemDC(), 361 + i * 15, 36);
	}
	_prograssBar->render(getMemDC(), 340, 35);


	_face->render(getMemDC(), 200, 0);

}
