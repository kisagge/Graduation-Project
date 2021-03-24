#pragma once
#include "item.h"
class drill2 : public item
{
public:
	HRESULT init(int x, int y);
	void release(void);
	void update(void);
	void render(void);

	drill2();
	~drill2();
};

