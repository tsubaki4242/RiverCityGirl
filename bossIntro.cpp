#include "stdafx.h"
#include "bossIntro.h"

HRESULT bossIntro::init()
{
	STREAMMANAGER->addVideo("movi/boss.wmv", "boss");
	STREAMMANAGER->playVido("boss");
	return S_OK;
}

void bossIntro::release()
{
}

void bossIntro::update()
{
	if (STREAMMANAGER->getPosition("boss") >= STREAMMANAGER->getLenthEnd("boss"))
	{

		STREAMMANAGER->closeVideo("boss");
		SCENEMANAGER->changeScene("·Îºñ");

	}
}

void bossIntro::render()
{
}
