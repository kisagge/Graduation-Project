#pragma once
#include "item.h"

class shield1 : public item
{
public:
	HRESULT init(int x, int y);
	void release(void);
	void update(void);
	void render(void);

	shield1();
	~shield1();
};

