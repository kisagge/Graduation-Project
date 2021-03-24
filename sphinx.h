#pragma once
#include "enemy.h"

class playerManager;

class sphinx : public enemy
{
public:
	HRESULT init(int x, int y);
	
	void setMonRectIdle(void);
	void setMonRectWalk(void);

	void attackManagement();

	sphinx();
	~sphinx();
};

