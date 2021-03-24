#include "stdafx.h"
#include "requi.h"


requi::requi()
{
}


requi::~requi()
{
}

HRESULT requi::init(int x, int y)
{
	_idleImage = IMAGEMANAGER->findImage("requiIdle");
	_walkImage = IMAGEMANAGER->findImage("requiIdle");
	_attackImage = IMAGEMANAGER->findImage("requiAttack");
	_hitImage = IMAGEMANAGER->findImage("requiHit");
	_deadImage = IMAGEMANAGER->findImage("requiDead");
	
	_x = x;
	_y = y;

	_moveRC = RectMake(_x, _y, 50, 50);

	setDirection();

	_frameY = _direction;
	_frameX = 0;

	_speed = 2.0f;

	_maxHp = 350;
	_maxMp = 0;
	_hp = _maxHp;
	_mp = _maxMp;
	_att = 100;
	_def = 25;
	_agi = 30;
	_dex = 20;

	_exp = 150;
	_lv = 7;

	_fightOrNot = false;
	_attackDelay = 3.5f;
	_state = IDLE;

	sprintf_s(name, "Requi");

	_enemyList = ENEMY_REQUI;

	return S_OK;
}

void requi::attackAniRender()
{
	if (_state == ATTACK)
	{
		if (_direction / 2 == 2)
			putZorderVec(_attackImage, _x - 30, _y, _moveRC.bottom, _frameX, _frameY);
		else if (_direction / 2 == 3)
			putZorderVec(_attackImage, _x, _y, _moveRC.bottom, _frameX, _frameY);
		else
			putZorderVec(_attackImage, _x, _y, _moveRC.bottom, _frameX, _frameY);
	}
}
