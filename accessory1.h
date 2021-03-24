#pragma once
#include "item.h"

class accessory1 : public item
{
public:
	HRESULT init(int x, int y);
	void release(void);
	void update(void);
	void render(void);

	accessory1();
	~accessory1();
};

