#pragma once
#include "item.h"
class skill1Card : public item
{
public:
	HRESULT init(int x, int y);
	void release(void);
	void update(void);
	void render(void);

	skill1Card();
	~skill1Card();
};

