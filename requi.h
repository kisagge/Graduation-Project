#pragma once
#include "enemy.h"
class requi : public enemy
{
public:
	HRESULT init(int x, int y);

	void attackAniRender();

	requi();
	~requi();
};

