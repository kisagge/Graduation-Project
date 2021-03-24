#include "stdafx.h"
#include "addax.h"


addax::addax()
{
}


addax::~addax()
{
}

HRESULT addax::init(int x, int y)
{
	_idleImage = IMAGEMANAGER->findImage("addaxIdle");
	_walkImage = IMAGEMANAGER->findImage("addaxIdle");
	_attackImage = IMAGEMANAGER->findImage("addaxAttack");
	_hitImage = IMAGEMANAGER->findImage("addaxHit");
	_deadImage = IMAGEMANAGER->findImage("addaxDead");

	_x = x;
	_y = y;

	_moveRC = RectMake(_x, _y, 50, 50);

	setDirection();

	_frameY = _direction;
	_frameX = 0;

	_speed = 2.0f;

	_maxHp = 150;
	_maxMp = 0;
	_hp = _maxHp;
	_mp = _maxMp;
	_att = 40;
	_def = 10;
	_agi = 20;
	_dex = 10;

	_exp = 100;
	_lv = 4;

	_fightOrNot = false;
	_attackDelay = 3.5f;
	_state = IDLE;

	sprintf_s(name, "Addex");

	_enemyList = ENEMY_ADDAX;

	return S_OK;
}

//°ø°Ý ¸ð¼Ç ·»´õ
void addax::attackAniRender()
{
	if (_state == ATTACK)
	{
		putZorderVec(_attackImage, _x - 40, _y - 10, _moveRC.bottom, _frameX, _frameY);
	}
}

//Á×´Â ¸ð¼Ç ·»´õ
void addax::deadAniRender()
{
	if (_hp < 0)
	{
		putZorderVec(_deadImage, _x, _y + 60, _moveRC.bottom, _frameX, 0);
	}
}
