#pragma once
#include "item.h"
class accessory3 : public item
{
public:
	HRESULT init(int x, int y);
	void release(void);
	void update(void);
	void render(void);

	accessory3();
	~accessory3();
};

