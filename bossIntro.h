#pragma once
#include "gameNode.h"
class bossIntro :
	public gameNode
{
private:

public:
	bossIntro() {}
	~bossIntro() {}

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

