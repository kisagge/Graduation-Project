#pragma once
#include "item.h"
class shield3 : public item
{
public:
	HRESULT init(int x, int y);
	void release(void);
	void update(void);
	void render(void);

	shield3();
	~shield3();
};

