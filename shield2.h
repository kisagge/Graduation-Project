#pragma once
#include "item.h"

class shield2 : public item
{
public:
	HRESULT init(int x, int y);
	void release(void);
	void update(void);
	void render(void);

	shield2();
	~shield2();
};

