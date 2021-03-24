#pragma once
#include "gameNode.h"

#define TILEWIDTH 48
#define TILEHEIGHT 48

#define ISOSTARTX 0
#define ISOSTARTY 0

#define MOVE 0x00000000
#define UNMOVE 0x00000001

class tile : public gameNode
{
private:
	int _indexX, _indexY;
	int _screenX, _screenY;

	RECT _tile;

	int _move;
public:
	HRESULT init(void);
	HRESULT init(int indX, int indY);
	void release(void);
	void update(void);
	void render(void);

	void setMove(int k){ _move = k; }

	tile();
	~tile();
};

