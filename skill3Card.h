#pragma once
#include "item.h"
class skill3Card : public item
{
public:
	HRESULT init(int x, int y);
	void release(void);
	void update(void);
	void render(void);

	skill3Card();
	~skill3Card();
};

