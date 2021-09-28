#pragma once
#include "gameNode.h"
#include "video.h"


class intro : public gameNode
{
private:


public:
	intro() {}
	~intro() {}

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

