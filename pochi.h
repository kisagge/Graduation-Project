#pragma once
#include "enemy.h"
class pochi : public enemy
{
public:
	HRESULT init(int x, int y);

	pochi();
	~pochi();
};

