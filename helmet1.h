#pragma once
#include "item.h"
class helmet1 : public item
{
public:
	HRESULT init(int x, int y);
	void release(void);
	void update(void);
	void render(void);

	helmet1();
	~helmet1();
};

