#include "stdafx.h"
#include "enemy.h"
#include "playerManager.h"

enemy::enemy() : _patrolOn(false), _fightOrNot(false), _state(IDLE), _frameX(0), _frameY(0),
_angle(RND->getFromfloatTo(0, PI2)), _stopTime(RND->getFromfloatTo(2.0, 6.0)), _escapeCount(0.0f), _isTargetOn(false),
_walkFrameCount(0.0f), _attackFrameCount(0.0f), _hitFrameCount(0.0f), _deadFrameCount(0.0f), _attackDelay(5.0f)
{
}


enemy::~enemy()
{
}

HRESULT enemy::init(void)
{
	return S_OK;
}

HRESULT enemy::init(int x, int y)
{
	return S_OK;
}


void enemy::release(void)
{

}

void enemy::update(void)
{
	if (_hp <= 0)
	{
		_hp = -1;
		_state = DEAD;
	}

	if (_hp > 0)
	{
		//정지시간 빼주기
		stopTimeCalculation();

		//몬스터 렉트 잡아주기
		setMonRect();

		if (!_fightOrNot)
		{
			//이동하기 설정
			moveManagement();
		}
		else attackManagement();

		//방향 설정
		setDirection();
	}

	//애니메이션
	animaition();

	//디버그 모드 업데이트 관리
	debugUpdate();
}

void enemy::render(void)
{
	//애니메이션 렌더
	aniRender();
	damageRender();
	//디버그 모드 렌더 관리
	debugRender();
}

//렉트 잡아주기 종합
void enemy::setMonRect(void)
{
	setMonRectIdle();
	setMonRectWalk();
}

//idle 상태 렉트 잡아주기
void enemy::setMonRectIdle(void)
{
	if (_state == IDLE && _hp > 0)
	{
		_imageRC = RectMake(_x, _y, _idleImage->getFrameWidth(), _idleImage->getFrameHeight());
		_moveRC = RectMake((_imageRC.left + _imageRC.right) / 2 - 24, _imageRC.bottom - 48, 48, 48);
	}
}

//walk상태 렉트 잡아주기
void enemy::setMonRectWalk(void)
{
	if (_state == WALK && _hp > 0)
	{
		_imageRC = RectMake(_x, _y, _walkImage->getFrameWidth(), _walkImage->getFrameHeight());
		_moveRC = RectMake((_imageRC.left + _imageRC.right) / 2 - 24, _imageRC.bottom - 48, 48, 48);
	}
}

//정지시간 빼주기
void enemy::stopTimeCalculation(void)
{
	if (_state == IDLE && _hp > 0 && !_fightOrNot)
	{
		_stopTime -= TIMEMANAGER->getElapsedTime();
		if (_stopTime < 0) _stopTime = 0.0f;
	}
}

//이동하기 설정 ( 이동가능이냐 아니냐 )
void enemy::moveManagement(void)
{
	if (_fightOrNot) return;

	if (_hp > 0)
	{
		if (_stopTime <= 0 && !_patrolOn)
		{
			this->changeState(WALK);
			_patrolOn = true;
			_startX = _x;
			_startY = _y;
			_endX = RND->getFromIntTo(50, 1800);
			_endY = RND->getFromIntTo(50, 800);
		}

		if (_patrolOn)
		{
			this->move(_startX, _startY, _endX, _endY);
		}
	}
	_sensorRC = RectMake(0, 0, 0, 0);
}

void enemy::move(int destX, int destY, int sourX, int sourY)
{
	if (_state != WALK) return;				//걷기 상태일땐 함수 진입을 막는다

	if (_hp <= 0)
	{
		this->changeState(DEAD);
		return;
	}

	//각도 설정
	_angle = getAngle(_x, _y, sourX, sourY);

	_escapeCount += TIMEMANAGER->getElapsedTime();

	if (_x != sourX)
	{
		_x += cosf(_angle) * _speed;
	}

	if (_y != sourY)
		_y -= sinf(_angle) * _speed;

	//끼임 체크
	if (abs(sourX - _x) <= 1 && abs(sourY - _y) <= 1)
	{
		this->changeState(IDLE);
		_patrolOn = false;
		_stopTime = RND->getFromfloatTo(2.0f, 6.0f);
		_x = sourX;
		_y = sourY;
		_escapeCount = 0.0f;
		return;
	}

	//끼임 탈출
	if (_escapeCount > 15.0f)
	{
		_x -= 1;
		_y -= 1;
		this->changeState(IDLE);
		_patrolOn = false;
		_stopTime = RND->getFromfloatTo(2.0f, 6.0f);
		_escapeCount = 0.0f;
		return;
	}
}

//방향 설정
void enemy::setDirection()
{
	if (_angle < PI_8 && _angle >= 0) _direction = 0;
	else if (_angle >= PI_8 && _angle < 3 * PI_8) _direction = 1;
	else if (_angle >= 3 * PI_8 && _angle < 5 * PI_8) _direction = 2;
	else if (_angle >= 5 * PI_8 && _angle < 7 * PI_8) _direction = 3;
	else if (_angle >= 7 * PI_8 && _angle < 9 * PI_8) _direction = 4;
	else if (_angle >= 9 * PI_8 && _angle < 11 * PI_8) _direction = 5;
	else if (_angle >= 11 * PI_8 && _angle < 13 * PI_8) _direction = 6;
	else if (_angle >= 13 * PI_8 && _angle < 15 * PI_8) _direction = 7;
	else if (_angle >= 15 * PI_8 && _angle <= 2 * PI) _direction = 0;
}

//애니메이션 종합
void enemy::animaition()
{
	idleAni();
	walkAni();
	attackAni();
	hitAni();
	deadAni();
}

//idle 상태 애니메이션
void enemy::idleAni()
{
	if (_state == IDLE& & _hp > 0)
	{
		_frameX = 0;
		_frameY = _direction;
	}
}

//걷는 애니메이션
void enemy::walkAni()
{
	if (_state == WALK && _hp > 0)
	{
		_frameY = _direction;
		if (0.15f + _walkFrameCount <= TIMEMANAGER->getWorldTime())
		{
			_walkFrameCount = TIMEMANAGER->getWorldTime();
			if (_walkImage->getFrameX() >= _walkImage->getMaxFrameX())
			{
				_frameX = 1;
				return;
			}
			_frameX++;
		}
	}
}

//공격 애니메이션
void enemy::attackAni()
{
	if (_state == ATTACK && _hp > 0)
	{
		_frameY = _direction / 2;
		if (0.15f + _attackFrameCount <= TIMEMANAGER->getWorldTime())
		{
			_attackFrameCount = TIMEMANAGER->getWorldTime();
			if (_attackImage->getFrameX() >= _attackImage->getMaxFrameX())
			{
				_frameX = 0;
				_attackDelay = 3.5f;

				int l = RND->getFromIntTo(1, 100) + _dex;
				if (l > _playerManagerLink->getPlayer()->getHv() &&
					!_playerManagerLink->getPlayer()->getIsAllMiss())
				{

					int k = RND->getFromIntTo(1, 5);
					switch (k)
					{
					case 1:
						if (SOUNDMANAGER->isPlaySound("공격소리6"))
						{
							SOUNDMANAGER->stop("공격소리6");
							SOUNDMANAGER->play("공격소리6", 0.5f);
						}
						else SOUNDMANAGER->play("공격소리6", 0.5f);
						break;
					case 2:
						if (SOUNDMANAGER->isPlaySound("공격소리7"))
						{
							SOUNDMANAGER->stop("공격소리7");
							SOUNDMANAGER->play("공격소리7", 0.5f);
						}
						else SOUNDMANAGER->play("공격소리7", 0.5f);
						break;
					case 3:
						if (SOUNDMANAGER->isPlaySound("공격소리8"))
						{
							SOUNDMANAGER->stop("공격소리8");
							SOUNDMANAGER->play("공격소리8", 0.5f);
						}
						else SOUNDMANAGER->play("공격소리8", 0.5f);
						break;
					case 4:
						if (SOUNDMANAGER->isPlaySound("공격소리9"))
						{
							SOUNDMANAGER->stop("공격소리9");
							SOUNDMANAGER->play("공격소리9", 0.5f);
						}
						else SOUNDMANAGER->play("공격소리9", 0.5f);
						break;
					case 5:
						if (SOUNDMANAGER->isPlaySound("공격소리10"))
						{
							SOUNDMANAGER->stop("공격소리10");
							SOUNDMANAGER->play("공격소리10", 0.5f);
						}
						else SOUNDMANAGER->play("공격소리10", 0.5f);
						break;
					}
					_playerManagerLink->getPlayer()->setHp(
						_playerManagerLink->getPlayer()->getHp() - _att
						+ _playerManagerLink->getPlayer()->getDp());
					damagePushBack(_att
						- _playerManagerLink->getPlayer()->getDp(), _playerManagerLink);
				}
				else
				{
					SOUNDMANAGER->play("미스", 0.5f);
					damagePushBack(0, _playerManagerLink);
				}
				_isTargetOn = false;
				return;
			}
			_frameX++;
		}
	}
}

//피격 애니메이션
void enemy::hitAni()
{
	if (_state == HIT && _hp > 0)
	{
		_frameY = _direction / 2;
		if (0.1f + _hitFrameCount <= TIMEMANAGER->getWorldTime())
		{
			_hitFrameCount = TIMEMANAGER->getWorldTime();
			if (_hitImage->getFrameX() >= _hitImage->getMaxFrameX())
			{
				_frameX = 0;
				_hitImage->setFrameX(_frameX);
				_state = IDLE;
				return;
			}
			_frameX++;
		}
	}
}

//죽는 애니메이션
void enemy::deadAni()
{
	if (_state == DEAD)
	{
		if (!SOUNDMANAGER->isPlaySound("몬스터죽음"))
		{
			SOUNDMANAGER->play("몬스터죽음", 0.5f);
		}
		_frameY = 0;
		if (0.15f + _deadFrameCount <= TIMEMANAGER->getWorldTime())
		{
			_deadFrameCount = TIMEMANAGER->getWorldTime();
			if (_deadImage->getFrameX() >= _deadImage->getMaxFrameX())
			{
				_isDead = true;
				_playerManagerLink->getPlayer()->setLvExp(
					_playerManagerLink->getPlayer()->getLvExp() + _exp);
				_playerManagerLink->getPlayer()->setTmExp(
					_playerManagerLink->getPlayer()->getTmExp() + _exp);
				_deadImage->setFrameX(0);
				return;
			}
			_frameX++;
		}
	}
}

//상태 변환
void enemy::changeState(MONSTATE state)
{
	switch (state)
	{
	case IDLE:
		break;
	case WALK:
		_walkFrameCount = TIMEMANAGER->getWorldTime();
		break;
	case ATTACK:
		_attackFrameCount = TIMEMANAGER->getWorldTime();
		break;
	case HIT:
		break;
	case DEAD:
		_deadFrameCount = TIMEMANAGER->getWorldTime();
		break;
	}

	_state = state;
}

//애니메이션 렌더 ( z오더 넣기 )
void enemy::aniRender()
{
	deadAniRender();				//죽는 애니메이션 렌더
	if (_hp > 0)
	{
		idleAniRender();				//서있는 애니메이션 렌더
		walkAniRender();				//걷는 애니메이션 렌더
		attackAniRender();				//공격 애니메이션 렌더
	}
}

//서있는 애니메이션 렌더
void enemy::idleAniRender()
{
	if (_state == IDLE)
	{
		putZorderVec(_idleImage, _x, _y, _moveRC.bottom, _frameX, _frameY);
	}
}

//걷는 애니메이션 렌더
void enemy::walkAniRender()
{
	if (_state == WALK)
	{
		putZorderVec(_walkImage, _x, _y, _moveRC.bottom, _frameX, _frameY);
	}
}

//공격 애니메이션 렌더
void enemy::attackAniRender()
{
	if (_state == ATTACK)
	{
		putZorderVec(_attackImage, _x, _y, _moveRC.bottom, _frameX, _frameY);
	}
}

//피격 애니메이션 렌더
void enemy::hitAniRender()
{
	if (_state == HIT)
	{
		putZorderVec(_attackImage, _x, _y, _moveRC.bottom, _frameX, _frameY);
	}
}

//죽는 애니메이션 렌더
void enemy::deadAniRender()
{
	if (_state == DEAD)
	{
		putZorderVec(_deadImage, _x, _y, _moveRC.bottom, _frameX, 0);
	}
}

//디버그 모드 업데이트 관리
void enemy::debugUpdate()
{
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		this->changeState(ATTACK);
		_frameX = 0;
	}
}

//디버그 모드 렌더 관리
void enemy::debugRender()
{
	if (KEYMANAGER->isToggleKey(VK_F1))
	{

		RectangleMake(getMemDC(), _moveRC.left, _moveRC.top,
			_moveRC.right - _moveRC.left, _moveRC.bottom - _moveRC.top);
		Rectangle(getMemDC(), _sensorRC.left, _sensorRC.top, _sensorRC.right, _sensorRC.bottom);
	
		char str[128];
		sprintf(str, "%d", _state);
		fontRender("나눔고딕", str, 20, 1, _x, _moveRC.bottom, RGB(0, 0, 0));
		sprintf(str, "%2.2f", _stopTime);
		fontRender("나눔고딕", str, 20, 1, _x, _moveRC.bottom + 20, RGB(0, 0, 0));
		sprintf(str, "%d", _fightOrNot);
		fontRender("나눔고딕", str, 20, 1, _x, _moveRC.bottom + 40, RGB(0, 0, 0));
		sprintf(str, "%2.2f", _attackDelay);
		fontRender("나눔고딕", str, 20, 1, _x, _moveRC.bottom + 60, RGB(0, 0, 0));
		sprintf(str, "%d", _whatMap);
		fontRender("나눔고딕", str, 20, 1, _x, _moveRC.bottom + 80, RGB(0, 0, 0));
	}
}

//공격 관리
void enemy::attackManagement()
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

	_sensorRC = RectMakeCenter((_moveRC.right + _moveRC.left) / 2, (_moveRC.bottom + _moveRC.top) / 2, 200, 200);
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

	_moveRC = RectMake((_imageRC.left + _imageRC.right) / 2 - 24, _imageRC.bottom - 48, 48, 48);
}

RECT enemy::returningAttackRC(int directiokn)
{
	return RectMake(0, 0, 0, 0);
}


void enemy::damagePushBack(int damage, playerManager* pl)
{
	tagDamageSkin temp;
	temp.skinImage = IMAGEMANAGER->findImage("폰트6");
	temp.x = pl->getPlayer()->getX() + 20;
	temp.y = pl->getPlayer()->getY() - 50;
	temp.alpha = 255;
	if (damage < 0)
	{
		damage = 0;
	}
	temp.damage = damage;
	_vDamageSkin.push_back(temp);
}

void enemy::damageRender()
{
	if (_vDamageSkin.size() == 0) return;

	for (int i = 0; i < _vDamageSkin.size(); i++)
	{
		_vDamageSkin[i].damageRender(getMemDC());
		_vDamageSkin[i].alpha -= 10;
		_vDamageSkin[i].y--;
		
		if (_vDamageSkin[i].alpha <= 0)
		{
			_vDamageSkin.erase(_vDamageSkin.begin() + i);
			return;
		}
	}
}