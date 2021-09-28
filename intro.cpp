#include "stdafx.h"
#include "intro.h"

HRESULT intro::init()
{
	STREAMMANAGER->addVideo("movi/intro2.wmv", "test3");
	SOUNDMANAGER->addSound("intro", "movi/intro.mp3", true, true);
	SOUNDMANAGER->play("intro");
	STREAMMANAGER->findVideo("test3")->playVideo();
	return S_OK;
}

void intro::release()
{
}

void intro::update()
{
	if (STREAMMANAGER->getPosition("test3") >= STREAMMANAGER->getLenthEnd("test3"))
	{
		
		STREAMMANAGER->deletVideo("test3");
		SCENEMANAGER->changeScene("타이틀");

	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{

		STREAMMANAGER->deletVideo("test3");
		SCENEMANAGER->changeScene("타이틀");


	}

}

void intro::render()
{

}
