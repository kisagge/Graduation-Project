#pragma once
#include "enemy.h"
class addax : public enemy
{
public:
	HRESULT init(int x, int y);

	void attackAniRender();		//°ø°Ý ¸ð¼Ç ·»´õ
	void deadAniRender();		//Á×´Â ¸ð¼Ç ·»´õ

	addax();
	~addax();
};

