#pragma once
#include "gameNode.h"
class stage1_3rdFloor :
	public gameNode
{
private:
	// �̹���
	image _background1;
	// �ȼ�
	image _background2;
	// ���� �ڽ�
	image _background3;
public:
	stage1_3rdFloor() {}
	~stage1_3rdFloor() {}

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void pixelCollision();
};

