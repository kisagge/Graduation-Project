#pragma once
#include "item.h"
class drill3 : public item
{
public:
	HRESULT init(int x, int y);
	void release(void);
	void update(void);
	void render(void);

	drill3();
	~drill3();
};

