#include "stdafx.h"
#include "UI.h"


HRESULT UI::init()
{
	IMAGEMANAGER->addImage("���α׷�����", "UI/���α׷�����.bmp", 414, 94, true, RGB(23, 25, 26));
	IMAGEMANAGER->addImage("���α׷�����2", "UI/���α׷�����2.bmp", 414, 94, true, RGB(23, 25, 26));
	IMAGEMANAGER->addImage("ü��", "UI/ü��.bmp", 26, 24, true, RGB(23, 25, 26), true);
	IMAGEMANAGER->addImage("��", "UI/������.bmp", 150, 169, true, RGB(23, 25, 26));

	_prograssBar = IMAGEMANAGER->findImage("���α׷�����");
	_prograssBar2 = IMAGEMANAGER->findImage("���α׷�����2");
	_face  = IMAGEMANAGER->findImage("��");
	for (int i = 0; i < LIFE; i++)
	{
		_lifeImg[i] = IMAGEMANAGER->findImage("ü��");
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
