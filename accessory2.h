#pragma once
#include "item.h"
class accessory2 : public item
{
public:
	HRESULT init(int x, int y);
	void release(void);
	void update(void);
	void render(void);

	accessory2();
	~accessory2();
};

