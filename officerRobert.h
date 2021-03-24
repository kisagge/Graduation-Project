#pragma once
#include "npcClass.h"
class officerRobert : public npcClass
{
public:
	HRESULT init(void);
	void update(void);

	officerRobert();
	~officerRobert();
};

