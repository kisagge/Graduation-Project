#pragma once
#include "enemy.h"
class addax : public enemy
{
public:
	HRESULT init(int x, int y);

	void attackAniRender();		//���� ��� ����
	void deadAniRender();		//�״� ��� ����

	addax();
	~addax();
};

