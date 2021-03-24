#pragma once
#include "gameNode.h"
class npcClass : public gameNode
{
protected:
	RECT _rc;
	image* _img;
	int _x, _y;
	char name[128];

	float _frameWorldCount;
	float _frameWaitTime;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	virtual void alphaRen(void);

	int getX(){ return _x; }
	void setX(int x){ _x = x; }

	int getY(){ return _y; }
	void setY(int y){ _y = y; }

	RECT getRc(){ return _rc; }

	image* getImage(){ return _img; }

	char* getName(){ return name; }

	npcClass();
	~npcClass();
};

