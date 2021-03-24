#include "stdafx.h"
#include "fantaSlime.h"


fantaSlime::fantaSlime()
{
}


fantaSlime::~fantaSlime()
{
}

HRESULT fantaSlime::init(int x, int y)
{
	_idleImage = IMAGEMANAGER->addFrameImage("fantaSlimeIdle", "images/lobbyMap/monster/FantaSlimeIdle.bmp", 450, 400, 9, 8, true, RGB(255, 0, 255));
	_walkImage = IMAGEMANAGER->findImage("fantaSlimeIdle");
	_attackImage = IMAGEMANAGER->addFrameImage("fantaSlimeAttack", "images/lobbyMap/monster/FantaSlimeAttack.bmp", 495, 200, 9, 4, true, RGB(255, 0, 255));
	_hitImage = IMAGEMANAGER->addFrameImage("fantaSlimeHit", "images/lobbyMap/monster/FantaSlimeHit.bmp", 100, 200, 2, 4, true, RGB(255, 0, 255));
	_deadImage = IMAGEMANAGER->addFrameImage("fantaSlimeDead", "images/lobbyMap/monster/FantaSlimeDead.bmp", 480, 50, 6, 1, true, RGB(255, 0, 255));
	

	_x = x;
	_y = y;

	_moveRC = RectMake(_x, _y, 50, 50);

	setDirection();

	_frameY = _direction;
	_frameX = 0;

	_speed = 2.0f;

	return S_OK;
}
