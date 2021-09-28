#pragma once
#include "gameNode.h"
#include "logo.h"
#include "intro.h"
#include "title.h"
#include "saveLode.h"
#include "manga.h"
#include "loading.h"
#include "bossIntro.h"
class playGround : public gameNode
{
private:
	bool _isOnce;

public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	
};

