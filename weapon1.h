#pragma once
#include "item.h"

class weapon1 : public item
{
public:
	HRESULT init(int x, int y);
	void release(void);
	void update(void);
	void render(void);

	weapon1();
	~weapon1();
};

