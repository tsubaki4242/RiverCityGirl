#pragma once
#include "stdafx.h"

class Enemy_Basic;

class Enemy_State
{
protected:

	const char* Enemy_State_Text;//������



	int frameCount;
	int frameUpdateCount;


	int Check_range;//�ش� ���� �ȿ� ������, �ش� �ൿ�� �ϰ� �ϴ°�?

	image* _image;



public:

	virtual Enemy_State* input_state(Enemy_Basic* _Enemy, bool reverse, int targetX,int targetY)=0; //������Ʈ ���¿�, �¿찪�� ����.
	virtual void update(Enemy_Basic* _Enemy ,int targetX, int targetY)=0; //������Ʈ �Լ�.  �ַ� ������ �̹��� ����or���� ��Ʈ ���� ���� ����ҵ�
	virtual void release(Enemy_Basic* _Enemy)=0; //���߿� �����ҵ�


	virtual void enter_this_state(Enemy_Basic* _Enemy)=0;//�ʱ�ȭ ���ִ� �Լ�.



};

