#pragma once
#include "gameNode.h"



class manga : public gameNode
{
private:


public:
	manga() {}
	~manga() {}

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};