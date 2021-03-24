#include "stdafx.h"
#include "sphinx.h"
#include "playerManager.h"

sphinx::sphinx()
{
}


sphinx::~sphinx()
{
}

HRESULT sphinx::init(int x, int y)
{
	_idleImage = IMAGEMANAGER->findImage("sphinxIdle");
	_walkImage = IMAGEMANAGER->findImage("sphinxWalk");
	_attackImage = IMAGEMANAGER->findImage("sphinxAttack");
	_hitImage = IMAGEMANAGER->findImage("sphinxHit");
	_deadImage = IMAGEMANAGER->findImage("sphinxDead");

	_x = x;
	_y = y;

	_moveRC = RectMake(_x, _y, 50, 50);
	
	setDirection();

	_frameY = _direction;
	_frameX = 0;

	_speed = 1.3f;

	_maxHp = 1500;
	_maxMp = 0;
	_hp = _maxHp;
	_mp = _maxMp;
	_att = 200;
	_def = 60;
	_agi = 55;
	_dex = 40;

	_exp = 1500;
	_lv = 10;

	_fightOrNot = false;
	_attackDelay = 3.5f;
	_state = IDLE;

	sprintf_s(name, "Sphinx");

	_enemyList = ENEMY_SPHINX;

	return S_OK;
}

void sphinx::setMonRectIdle(void)
{
	if (_state == IDLE)
	{
		_imageRC = RectMake(_x, _y, _idleImage->getFrameWidth(), _idleImage->getFrameHeight());
		_moveRC = RectMake((_imageRC.left + _imageRC.right) / 2 - 48, _imageRC.bottom - 144, 96, 96);
	}
}

void sphinx::setMonRectWalk(void)
{
	if (_state == WALK)
	{
		_imageRC = RectMake(_x, _y, _walkImage->getFrameWidth(), _walkImage->getFrameHeight());
		_moveRC = RectMake((_imageRC.left + _imageRC.right) / 2 - 48, _imageRC.bottom - 144, 96, 96);
	}
}

//공격 관리
void sphinx::attackManagement()
{
	_attackDelay -= TIMEMANAGER->getElapsedTime();

	if (_attackDelay < 0) _attackDelay = 0;

	//어그로가 끌린 상태에서 플레이어와 다른맵에 있다면 어그로가 풀린다.
	if (_whatMap != _playerManagerLink->getPlayer()->getWhatMap())
	{
		_fightOrNot = false;
		_attackDelay = 5.0f;
		return;
	}

	_sensorRC = RectMakeCenter((_moveRC.right + _moveRC.left) / 2, (_moveRC.bottom + _moveRC.top) / 2, 400, 400);
	RECT temp;
	if (IntersectRect(&temp, &_sensorRC, &_playerManagerLink->getPlayer()->getMoveRc()))
	{
		if (_attackDelay == 0)
		{
			_isTargetOn = true;

			if (_isTargetOn)
			{
				_angle = getAngle((_moveRC.right + _moveRC.left) / 2, (_moveRC.bottom + _moveRC.top) / 2
					, (_playerManagerLink->getPlayer()->getMoveRc().right + _playerManagerLink->getPlayer()->getMoveRc().left) / 2
					, (_playerManagerLink->getPlayer()->getMoveRc().bottom + _playerManagerLink->getPlayer()->getMoveRc().top) / 2);
				setDirection();
				_state = ATTACK;
			}
		}
		else
		{
			if (!_isTargetOn)
			{
				_angle = getAngle((_moveRC.right + _moveRC.left) / 2, (_moveRC.bottom + _moveRC.top) / 2
					, (_playerManagerLink->getPlayer()->getMoveRc().right + _playerManagerLink->getPlayer()->getMoveRc().left) / 2
					, (_playerManagerLink->getPlayer()->getMoveRc().bottom + _playerManagerLink->getPlayer()->getMoveRc().top) / 2);
				setDirection();
				_state = IDLE;
			}
		}
	}
	else
	{
		if (!_isTargetOn)
		{
			_state = WALK;
			this->move(_x, _y, _playerManagerLink->getPlayer()->getX(), _playerManagerLink->getPlayer()->getY());
		}
	}

	_moveRC = RectMake((_imageRC.left + _imageRC.right) / 2 - 48, _imageRC.bottom - 144, 96, 96);
}
