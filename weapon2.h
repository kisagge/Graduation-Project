#pragma once
#include "item.h"
class weapon2 : public item
{
public:
	HRESULT init(int x, int y);
	void release(void);
	void update(void);
	void render(void);

	weapon2();
	~weapon2();
};

