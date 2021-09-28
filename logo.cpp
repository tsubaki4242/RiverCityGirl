#include "stdafx.h"
#include "logo.h"

HRESULT logo::init()
{


	
	STREAMMANAGER->addVideo("movi/logo1.wmv", "test1");
	STREAMMANAGER->addVideo("movi/logo2.wmv", "test2");
	STREAMMANAGER->findVideo("test1")->playVideo();

	_isOnce = false;
	_isTwo = false;
	return S_OK;
}

void logo::release()
{
}

void logo::update()
{

	if (STREAMMANAGER->getPosition("test1") >= STREAMMANAGER->getLenthEnd("test1") && !_isOnce)
	{
		_isOnce = true;
		STREAMMANAGER->closeVideo("test1");
		STREAMMANAGER->findVideo("test2")->playVideo();

	}
	if (STREAMMANAGER->getPosition("test2") >= STREAMMANAGER->getLenthEnd("test2") && !_isTwo && _isOnce)
	{
		_isTwo = true;
		STREAMMANAGER->closeVideo("test2");
		SCENEMANAGER->changeScene("¿Œ∆Æ∑Œ");

	}



}

void logo::render()
{

}

