#pragma once
#include "item.h"
class potion1 : public item
{
public:
	HRESULT init(int x, int y);
	void release(void);
	void update(void);
	void render(void);

	potion1();
	~potion1();
};

