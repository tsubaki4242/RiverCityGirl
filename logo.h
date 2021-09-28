#pragma once
#include "gameNode.h"
#include "video.h"


class logo :	public gameNode
{
private:
	video* _stream;


	bool _isOnce;
	bool _isTwo;

public:
	logo() {}
	~logo() {}

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

