#include "stdafx.h"
#include "pochi.h"


pochi::pochi()
{
}


pochi::~pochi()
{
}

HRESULT pochi::init(int x, int y)
{
	_idleImage = IMAGEMANAGER->findImage("pochiIdle");
	_walkImage = IMAGEMANAGER->findImage("pochiIdle");
	_attackImage = IMAGEMANAGER->findImage("pochiAttack");
	_hitImage = IMAGEMANAGER->findImage("pochiHit");
	_deadImage = IMAGEMANAGER->findImage("pochiDead");

	_x = x;
	_y = y;

	_moveRC = RectMake(_x, _y, 50, 50);

	setDirection();

	_frameY = _direction;
	_frameX = 0;

	_speed = 2.0f;

	_maxHp = 30;
	_maxMp = 0;
	_hp = _maxHp;
	_mp = _maxMp;
	_att = 25;
	_def = 5;
	_agi = 10;
	_dex = 0;

	_exp = 10;

	_fightOrNot = false;
	_attackDelay = 3.5f;
	_state = IDLE;

	_lv = 1;

	sprintf_s(name, "Pochi");

	_enemyList = ENEMY_POCHI;

	return S_OK;
}