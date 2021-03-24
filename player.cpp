#include "stdafx.h"
#include "player.h"
#include "mapManager.h"
#include "uiManager.h"
#include "enemyManager.h"
#include "enemy.h"

player::player()
{
}


player::~player()
{
}

HRESULT player::init(void)
{
	return S_OK;
}

HRESULT player::init(int x, int y)
{
	_x = x;
	_y = y;

	_moveRC = RectMake(_x, _y, 48, 48);

	_speed = 5;

	_idle = IMAGEMANAGER->findImage("기본");
	_walk[0] = IMAGEMANAGER->findImage("걷기0");
	_walk[1] = IMAGEMANAGER->findImage("걷기1");
	_walk[2] = IMAGEMANAGER->findImage("걷기2");
	_walk[3] = IMAGEMANAGER->findImage("걷기3");
	_walk[4] = IMAGEMANAGER->findImage("걷기4");
	_walk[5] = IMAGEMANAGER->findImage("걷기5");
	_walk[6] = IMAGEMANAGER->findImage("걷기6");
	_walk[7] = IMAGEMANAGER->findImage("걷기7");
	_specialImg = IMAGEMANAGER->findImage("특수");

	_attackIdle[0] = IMAGEMANAGER->findImage("공격대기0");
	_attackIdle[1] = IMAGEMANAGER->findImage("공격대기1");
	_attackIdle[2] = IMAGEMANAGER->findImage("공격대기2");
	_attackIdle[3] = IMAGEMANAGER->findImage("공격대기3");

	_attack[0] = IMAGEMANAGER->findImage("공격0");
	_attack[1] = IMAGEMANAGER->findImage("공격1");
	_attack[2] = IMAGEMANAGER->findImage("공격2");
	_attack[3] = IMAGEMANAGER->findImage("공격3");

	_drill = IMAGEMANAGER->findImage("드릴");
	_drilling = IMAGEMANAGER->findImage("캐릭드릴");

	_hitImage = IMAGEMANAGER->findImage("피격");

	_angle = 0.0f;
	
	_state = UNMOVING;

	_imageX = _x;
	_imageY = _moveRC.bottom - _idle->getFrameHeight();

	_frameCount = 0.0f;
	_walkFrameCount = 0.0f;
	_attackFrameCount = 0.0f;
	_hitFrameCount = 0.0f;

	_specialTime = 3.0f;

	setDirection();

	_maxHp = 100;
	_maxMp = 100;
	_hp = _maxHp;
	_mp = _maxMp;
	_ap = 10;
	_ac = 10.0f;
	_dx = 10;
	_wt = 5;
	_da = 10;
	_lk = 10;
	_dp = 10;
	_hv = 10;

	_hpMinibar = IMAGEMANAGER->findImage("체력미니바");
	_mpMinibar = IMAGEMANAGER->findImage("마나미니바");
	
	_nowWeight = 0;
	_maxWeight = _wt * 100;

	_fightOrNot = false;

	_lv = 1;
	_lvExp = 0;
	_maxLvExp = 100;

	_tm = 1;
	_tmExp = 30;
	_maxTmExp = 100;

	_money = 10000;
	_bonusStat = 0;
	_skillPoint = 0;

	_helmet = NULL;
	_weapon = NULL;
	_shield = NULL;
	_accessory = NULL;
	_drillItem = NULL;

	_inventory.push_back(ITEMDB->findItem("무기_3"));
	_inventory.push_back(ITEMDB->findItem("방패_3"));
	_inventory.push_back(ITEMDB->findItem("모자_3"));
	_inventory.push_back(ITEMDB->findItem("드릴_3"));
	_inventory.push_back(ITEMDB->findItem("악세_3"));

	_drillUi = IMAGEMANAGER->findImage("드릴창");
	_drillGauge = IMAGEMANAGER->findImage("드릴게이지");
	_drillGear[0] = IMAGEMANAGER->findImage("드릴기어1");
	_drillGear[1] = IMAGEMANAGER->findImage("드릴기어2");
	_drillGear[2] = IMAGEMANAGER->findImage("드릴기어3");
	_maxDrillGauge = _drillGauge->getWidth();
	_curDrillGauge = 0;

	//스킬1
	_skill[0].isGet = false;
	_skill[0].frameCount = 0.0f;
	_skill[0].lv = 0;
	_skill[0].isPlay = false;
	_skill[0].skillCoolTime = 6.0f;
	_skill[0].skillIcon = IMAGEMANAGER->findImage("스킬1아이콘");
	_skill[0].skillEffect = IMAGEMANAGER->findImage("스킬1이펙트");
	_skill[0].skillHowLong = 0.0f;
	_skill[0].isCool = false;

	//스킬2
	_skill[1].isGet = false;
	_skill[1].frameCount = 0.0f;
	_skill[1].lv = 0;
	_skill[1].isPlay = false;
	_skill[1].skillCoolTime = 180.0f;
	_skill[1].skillIcon = IMAGEMANAGER->findImage("스킬2아이콘");
	_skill[1].skillEffect = IMAGEMANAGER->findImage("스킬2이펙트");
	_skill[1].skillHowLong = 0.0f;
	_skill[1].isCool = false;

	_skill[2].isGet = false;
	_skill[2].frameCount = 0.0f;
	_skill[2].lv = 0;
	_skill[2].isPlay = false;
	_skill[2].skillCoolTime = 180.0f;
	_skill[2].skillIcon = IMAGEMANAGER->findImage("스킬3아이콘");
	_skill[2].skillEffect = IMAGEMANAGER->findImage("스킬3이펙트");
	_skill[2].skillHowLong = 0.0f;
	_skill[2].isCool = false;
	_skill3This = IMAGEMANAGER->findImage("스킬3지속표시");

	_isAttackOk = false;
	_isHit = false;

	_skillMasterImage = IMAGEMANAGER->findImage("스킬마스터");

	return S_OK;
}

void player::release(void)
{
	//인벤토리 릴리즈
	for (int i = 0; i < _inventory.size(); i++)
	{
		_inventory[i]->release();
		SAFE_DELETE(_inventory[i]);
	}

	//인벤토리 클리어
	_inventory.clear();

	//장비창 릴리즈 start
	if (_weapon != NULL)
	{
		_weapon->release();
		SAFE_DELETE(_weapon);
	}

	if (_shield != NULL)
	{
		_shield->release();
		SAFE_DELETE(_shield);
	}

	if (_helmet != NULL)
	{
		_helmet->release();
		SAFE_DELETE(_helmet);
	}

	if (_accessory != NULL)
	{
		_accessory->release();
		SAFE_DELETE(_accessory);
	}

	if (_drillItem != NULL)
	{
		_drillItem->release();
		SAFE_DELETE(_drillItem);
	}
	//장비창 릴리즈 finish

	_vDamageSkin.clear();
	_vEffect.clear();
}

void player::update(void)
{
	//체력 마나 맥스이상일때 맥스로 설정
	setMaxHpMpCaseOver();

	//마우스 클릭 이동
	moveManagement();
	this->move(_startX, _startY, _endX, _endY);
	
	//방향 설정
	setDirection();

	//프레임 돌리는 함수
	animaition();

	if (KEYMANAGER->isOnceKeyDown('4'))
	{
		if (_state == UNMOVING)
		{
			this->changeState(ATTACK_IDLE);
		}
		else if (_state == ATTACK_IDLE)
		{
			_state = UNMOVING;
		}
	}

	//공격 키
	attackControl();
	//드릴 키
	drillControl();

	//플레이어
	playerSetting();

	//아이템 관련 함수
	itemUpdate();
	itemEquip();
	calculateWeight();

	//드릴 관련 함수
	drillFrameUpdate();
	drillGaugeManagement();
	
	//레벨 tm 업
	lvTmUp();

	//자동 회복
	autoUp();

	//스킬 관련 함수
	skillManagement();
	skillFraming();
	skill1CalculateHowLong();
	usingSkill();
	checkSkillCoolTime();
	thunderShot();

	//공격 관리
	attackManagement();

	//치트키
	cheatKey();

	_whatMap = _mapManagerLink->getWhatMap();
}

void player::render(void)
{
	//애니메이션 렌더
	aniRender();
	
	//체력 이미지 렌더
	barRender();

	//스킬 관련 렌더
	skillEffectRender();
	thunderThunder();
	
	damageRender();
	effectRender();

	char str[128];
	sprintf(str, "%s", _name);
	fontRender("NtreevSoft", str, 20, 1, _x, _y + 50, RGB(0, 0, 0));

	//디버그 모드 렌더
	debugRender();
}

void player::playerSetting()
{
	//플레이어 좌표 업데이트
	_imageX = _x;
	_imageY = _moveRC.bottom - _idle->getFrameHeight();
	_moveRC = RectMake(_x, _y, 48, 48);

	//무게 설정
	_maxWeight = _wt * 100;
}

void player::setMaxHpMpCaseOver()
{
	if (_hp > _maxHp) _hp = _maxHp;
	if (_mp > _maxMp) _mp = _maxMp;
}

void player::moveManagement()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//우측 하단 UI 메뉴 클릭했을때 예외처리
		for (int i = 0; i < 8; i++)
		{
			if (PtInRect(&_uiManagerLink->getMenuRect(i), _ptMouse))
				return;
		}

		//창들 클릭했을때 예외처리
		for (int i = 0; i < _uiManagerLink->getWindows().size(); i++)
		{
			if (PtInRect(&_uiManagerLink->getWindows()[i]->windowOpenRect, _ptMouse)
				|| PtInRect(&_uiManagerLink->getWindows()[i]->exitRect, _ptMouse))
			{
				if (_uiManagerLink->getWindows()[i]->isOpen)
					return;
			}
		}

		//상점 클릭했을 때 예외처리
		if (_uiManagerLink->getShop()->getShopOn() &&
			PtInRect(&_uiManagerLink->getShop()->getShopRC(), _ptMouse)) return;

		//이동으로 변환
		this->changeState(MOVING);
		_startX = _x;
		_startY = _y;
		_endX = _ptMouse.x + setMouseCursorX();
		_endY = _ptMouse.y + setMouseCursorY();
	}
}

//방향 설정 ( 각도에 따라 설정됨 )
void player::setDirection()
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

//애니메이션 종합 관리
void player::animaition()
{
	walkAni();
	attackAni();
	attackIdleAni();
	drillAni();

	//특수행동
	specialAni();
}

void player::idleAni()
{

}

//걷는 애니메이션
void player::walkAni()
{
	if (_state == MOVING)
	{
		if (0.2f + _walkFrameCount <= TIMEMANAGER->getWorldTime())
		{
			_walkFrameCount = TIMEMANAGER->getWorldTime();
			if (_walk[_direction]->getFrameX() >= _walk[_direction]->getMaxFrameX())
			{
				_walk[_direction]->setFrameX(0);
				return;
			}
			_walk[_direction]->setFrameX(_walk[_direction]->getFrameX() + 1);
		}
	}
}

//공격 애니메이션
void player::attackAni()
{
	if (_state == ATTACKING)
	{
		if (2.5 / _ac + _attackFrameCount <= TIMEMANAGER->getWorldTime())
		{
			_attackFrameCount = TIMEMANAGER->getWorldTime();
			if (_attack[_direction / 2]->getFrameX() >= _attack[_direction / 2]->getMaxFrameX())
			{
				_attack[_direction / 2]->setFrameX(0);
				_state = UNMOVING;
				if (_skill[0].isPlay) _skill[0].isPlay = false;
				return;
			}
			_attack[_direction / 2]->setFrameX(_attack[_direction / 2]->getFrameX() + 1);

			if (_attack[_direction / 2]->getFrameX() == 5)
			{
				
			}
		}
	}
}

//드릴 플레이어 애니메이션
void player::drillAni()
{
	if (_state == DRILL)
	{
		if (0.15f + _anoDrillFrameCount <= TIMEMANAGER->getWorldTime())
		{
			_anoDrillFrameCount = TIMEMANAGER->getWorldTime();
			if (_drilling->getFrameX() >= _drilling->getMaxFrameX())
			{
				_drilling->setFrameX(0);
				return;
			}
			_drilling->setFrameX(_drilling->getFrameX() + 1);
		}
	}
}

//스페셜 동작
void player::specialAni()
{
	if (_state != UNMOVING)
	{
		_specialTime = 3.0f;
		return;
	}

	_specialTime -= TIMEMANAGER->getElapsedTime();
	if (_specialTime <= 0)
	{
		if (0.1f + _frameCount <= TIMEMANAGER->getWorldTime())
		{
			_frameCount = TIMEMANAGER->getWorldTime();
			if (_specialImg->getFrameX() >= _specialImg->getMaxFrameX())
			{
				_specialImg->setFrameX(0);
				_specialTime = 3.0f;
				_angle = 5 * PI_4;
				return;
			}
			_specialImg->setFrameX(_specialImg->getFrameX() + 1);
		}
	}
}

//공격 대기 애니메이션
void player::attackIdleAni()
{
	if (_state == ATTACK_IDLE)
	{
		if (0.15f + _attackIdleCount <= TIMEMANAGER->getWorldTime())
		{
			_attackIdleCount = TIMEMANAGER->getWorldTime();
			if (_attackIdle[_direction / 2]->getFrameX() >= _attackIdle[_direction / 2]->getMaxFrameX())
			{
				_attackIdle[_direction / 2]->setFrameX(0);
				return;
			}
			_attackIdle[_direction / 2]->setFrameX(_attackIdle[_direction / 2]->getFrameX() + 1);
		}
	}
}

void player::changeState(STATE state)
{
	switch (state)
	{
	case UNMOVING:
		break;
	case MOVING:
		_walkFrameCount = 0.0f;
		break;
	case ATTACK_IDLE:
		_attackIdleCount = 0.0f;
		break;
	case ATTACKING:
		_attackFrameCount = 0.0f;
		break;
	case DAMAGED:
		break;
	case DRILL:
		_anoDrillFrameCount = 0.0f;
		_drillFrameCount = 0.0f;
		break;
	}

	_state = state;
}

//마우스 커서 X
int player::setMouseCursorX()
{
	if (_x < WINSIZEX / 2) return 0;
	else if (_x + WINSIZEX / 2 > _mapManagerLink->getMap(0)->getBg()->getWidth())
		return _mapManagerLink->getMap(0)->getBg()->getWidth() - WINSIZEX;
	else return _x - WINSIZEX / 2;
}

//마우스 커서 Y
int player::setMouseCursorY()
{
	if (_y < WINSIZEY / 2) return 0;
	else if (_y + WINSIZEY / 2 > _mapManagerLink->getMap(0)->getBg()->getHeight())
		return _mapManagerLink->getMap(0)->getBg()->getHeight() - WINSIZEY;
	else return _y - WINSIZEY / 2;
}

//애니메이션 렌더
void player::aniRender()
{
	walkRender();
	idleRender();
	attackIdleRender();
	attackRender();
	drillRender();
}

//걷는 애니메이션 렌더
void player::walkRender()
{
	if (_state == MOVING)
	{
		putZorderVec(_walk[_direction], _imageX, _imageY, _moveRC.bottom, _walk[_direction]->getFrameX(), _walk[_direction]->getFrameY());
	}
}

//서있는 애니메이션 렌더
void player::idleRender()
{
	if (_state == UNMOVING)
	{
		if (_specialTime > 0)
			putZorderVec(_idle, _imageX, _imageY, _moveRC.bottom, _direction, _idle->getFrameY());
		else
			putZorderVec(_specialImg, _imageX - 20 - _specialImg->getFrameX(), _imageY,
			_moveRC.top, _specialImg->getFrameX(), _specialImg->getFrameY());
	}
}

//공격 대기 애니메이션 렌더
void player::attackIdleRender()
{
	if (_state == ATTACK_IDLE)
	{
		putZorderVec(_attackIdle[_direction / 2], _imageX, _imageY, _moveRC.bottom, _attackIdle[_direction / 2]->getFrameX(), _attackIdle[_direction / 2]->getFrameY());
	}
}

//공격 애니메이션 렌더
void player::attackRender()
{
	if (_state == ATTACKING)
	{
		if (_direction / 2 == 1 || _direction / 2 == 2)
			putZorderVec(_attack[_direction / 2], _imageX - 15, _imageY, _moveRC.bottom, _attack[_direction / 2]->getFrameX(), _attack[_direction / 2]->getFrameY());
		else
			putZorderVec(_attack[_direction / 2], _imageX, _imageY, _moveRC.bottom, _attack[_direction / 2]->getFrameX(), _attack[_direction / 2]->getFrameY());
	}
}

//드릴 애니메이션 렌더
void player::drillRender()
{
	if (_state == DRILL)
	{
		putZorderVec(_drilling, _imageX, _imageY, _moveRC.bottom, _drilling->getFrameX(), _drilling->getFrameY());
		putZorderVec(_drill, _imageX + 10, _imageY + 43 + 3 * sinf(TIMEMANAGER->getWorldTime() * 50), _moveRC.bottom + 1);
		drillUiRender();
	}
}

//캐릭터 밑 체력, 마나바 렌더
void player::barRender()
{
	//체력 마나 캐릭터 밑에 바
	_hpMinibar->render(getMemDC(), _x, _y + 50, 0, 0, _hpMinibar->getWidth() * _hp / _maxHp, _hpMinibar->getHeight());
	_mpMinibar->render(getMemDC(), _x, _y + 58, 0, 0, _mpMinibar->getWidth() * _mp / _maxMp, _mpMinibar->getHeight());
}

//이동
void player::move(int destX, int destY, int sourX, int sourY)
{
	if (_state != MOVING) return;
	
	if (_skill[0].isPlay) return;

	_angle = getAngle(_x, _y, sourX, sourY);

	if (_x != sourX)
		_x += cosf(_angle) * _speed;

	if (_y != sourY)
		_y -= sinf(_angle) * _speed;

	if (destX <= sourX && destY <= sourY)
		if (_x >= sourX && _y >= sourY) _state = UNMOVING;

	if (destX <= sourX && destY >= sourY)
		if (_x >= sourX && _y <= sourY) _state = UNMOVING;

	if (destX >= sourX && destY >= sourY)
		if (_x <= sourX && _y <= sourY) _state = UNMOVING;

	if (destX >= sourX && destY <= sourY)
		if (_x <= sourX && _y >= sourY) _state = UNMOVING;
}

//아이템 업데이트
void player::itemUpdate(void)
{
	if (_helmet != NULL) _helmet->update();
	if (_weapon != NULL) _weapon->update();
	if (_shield != NULL) _shield->update();
	if (_accessory != NULL) _accessory->update();
	if (_drillItem != NULL) _drillItem->update();

	//아이템 업데이트
	for (int i = 0; i < _inventory.size(); i++)
	{
		_inventory[i]->update();
	}
}

//아이템 장착
void player::itemEquip(void)
{
	if (_uiManagerLink->getEquipWindowIsOpen())
	{
		//무기
		if (_weapon != NULL)
		{
			if (PtInRect(&_weapon->getIconRC(), _ptMouse)
				&& KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
			{
				itemSpecDown(_weapon);
				_inventory.push_back(_weapon);
				_weapon = NULL;
			}
		}

		//방패
		if (_shield != NULL)
		{
			if (PtInRect(&_shield->getIconRC(), _ptMouse)
				&& KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
			{
				itemSpecDown(_shield);
				_inventory.push_back(_shield);
				_shield = NULL;
			}
		}

		//헬멧
		if (_helmet != NULL)
		{
			if (PtInRect(&_helmet->getIconRC(), _ptMouse)
				&& KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
			{
				itemSpecDown(_helmet);
				_inventory.push_back(_helmet);
				_helmet = NULL;
			}
		}

		//악세서리
		if (_accessory != NULL)
		{
			if (PtInRect(&_accessory->getIconRC(), _ptMouse)
				&& KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
			{
				itemSpecDown(_accessory);
				_inventory.push_back(_accessory);
				_accessory = NULL;
			}
		}

		//드릴
		if (_drillItem != NULL)
		{
			if (PtInRect(&_drillItem->getIconRC(), _ptMouse)
				&& KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
			{
				itemSpecDown(_drillItem);
				_inventory.push_back(_drillItem);
				_drillItem = NULL;
			}
		}
	}

	if (_uiManagerLink->getItemWindowIsOpen())
	{
		//인벤에서 장착할때
		for (int i = 0; i < _inventory.size(); i++)
		{
			if (PtInRect(&_inventory[i]->getIconRC(), _ptMouse)
				&& KEYMANAGER->isOnceKeyDown(VK_RBUTTON) && _inventory[i]->getRequiredLv() <= _lv)
			{
				switch (_inventory[i]->getItemKind())
				{
				case ITEM_WEAPON:
					if (_weapon == NULL)
					{
						_weapon = _inventory[i];
						itemSpecUp(_weapon);
						_inventory.erase(_inventory.begin() + i);
					}
					else
					{
						itemSpecDown(_weapon);
						_inventory.push_back(_weapon);
						_weapon = NULL;
						_weapon = _inventory[i];
						itemSpecUp(_weapon);
						_inventory.erase(_inventory.begin() + i);
					}
					break;
				case ITEM_SHIELD:
					if (_shield == NULL)
					{
						_shield = _inventory[i];
						itemSpecUp(_shield);
						_inventory.erase(_inventory.begin() + i);
					}
					else
					{
						itemSpecDown(_shield);
						_inventory.push_back(_shield);
						_shield = NULL;
						_shield = _inventory[i];
						itemSpecUp(_shield);
						_inventory.erase(_inventory.begin() + i);
					}
					break;
				case ITEM_HAT:
					if (_helmet == NULL)
					{
						_helmet = _inventory[i];
						itemSpecUp(_helmet);
						_inventory.erase(_inventory.begin() + i);
					}
					else
					{
						itemSpecDown(_helmet);
						_inventory.push_back(_helmet);
						_helmet = NULL;
						_helmet = _inventory[i];
						itemSpecUp(_helmet);
						_inventory.erase(_inventory.begin() + i);
					}
					break;
				case ITEM_ACCESSORY:
					if (_accessory == NULL)
					{
						_accessory = _inventory[i];
						itemSpecUp(_accessory);
						_inventory.erase(_inventory.begin() + i);
					}
					else
					{
						itemSpecDown(_accessory);
						_inventory.push_back(_accessory);
						_accessory = NULL;
						_accessory = _inventory[i];
						itemSpecUp(_accessory);
						_inventory.erase(_inventory.begin() + i);
					}
					break;
				case ITEM_DRILL:
					if (_drillItem == NULL)
					{
						_drillItem = _inventory[i];
						itemSpecUp(_drillItem);
						_inventory.erase(_inventory.begin() + i);
					}
					else
					{
						itemSpecDown(_drillItem);
						_inventory.push_back(_drillItem);
						_drillItem = NULL;
						_drillItem = _inventory[i];
						itemSpecUp(_drillItem);
						_inventory.erase(_inventory.begin() + i);
					}
					break;
				case ITEM_SPEND:
					if (_inventory[i]->getItemlist() == ITEM_SPEND_1)
					{
						if (_hp >= _maxHp) break;
						else
						{
							_hp += _inventory[i]->getHpUp();
							_inventory.erase(_inventory.begin() + i);
							break;
						}
					}

					if (_inventory[i]->getItemlist() == ITEM_SPEND_2)
					{
						if (_mp >= _maxMp) break;
						else
						{
							_mp += _inventory[i]->getMpUp();
							_inventory.erase(_inventory.begin() + i);
							break;
						}
					}
					break;
				case ITEM_SKILLCARD:
					if (_inventory[i]->getItemlist() == ITEM_SKILLCARD_1
						&& !_skill[0].isGet)
					{
						_skill[0].isGet = true;
						_skill[0].lv = 1;
						_inventory.erase(_inventory.begin() + i);
						break;
					}

					if (_inventory[i]->getItemlist() == ITEM_SKILLCARD_2
						&& !_skill[1].isGet)
					{
						_skill[1].isGet = true;
						_skill[1].lv = 1;
						_inventory.erase(_inventory.begin() + i);
						break;
					}

					if (_inventory[i]->getItemlist() == ITEM_SKILLCARD_3
						&& !_skill[2].isGet)
					{
						_skill[2].isGet = true;
						_skill[2].lv = 1;
						_inventory.erase(_inventory.begin() + i);
						break;
					}
				}
			}
		}
	}
}

//아이템 스펙업
void player::itemSpecUp(item* sour)
{
	_ap += sour->getApUp();
	_ac += sour->getAcUp();
	_dx += sour->getDxUp();
	_maxHp += sour->getHpUp();
	_maxMp += sour->getMpUp();
	_wt += sour->getWtUp();
	_da += sour->getDaUp();
	_lk += sour->getLkUp();
	_dp += sour->getDpUp();
	_hv += sour->getHvUp();
}

//아이템 스펙 다운
void player::itemSpecDown(item* sour)
{
	_ap -= sour->getApUp();
	_ac -= sour->getAcUp();
	_dx -= sour->getDxUp();
	_maxHp -= sour->getHpUp();
	_maxMp -= sour->getMpUp();
	_wt -= sour->getWtUp();
	_da -= sour->getDaUp();
	_lk -= sour->getLkUp();
	_dp -= sour->getDpUp();
	_hv -= sour->getHvUp();
}

//무게 계산
void player::calculateWeight(void)
{
	int k = 0;
	
	for (int i = 0; i < _inventory.size(); i++)
	{
		k += _inventory[i]->getWeight();
	}

	if (_weapon != NULL)
		k += _weapon->getWeight();

	if (_shield != NULL)
		k += _shield->getWeight();

	if (_helmet != NULL)
		k += _helmet->getWeight();

	if (_accessory != NULL)
		k += _accessory->getWeight();

	if (_drillItem != NULL)
		k += _drillItem->getWeight();

	_nowWeight = k;
}

//드릴 ui렌더
void player::drillUiRender(void)
{
	_drillGear[0]->frameRender(getMemDC(), _x - 54, _moveRC.bottom + 3, _drillGear[0]->getFrameX(),
		_drillGear[0]->getFrameY());
	_drillGear[1]->frameRender(getMemDC(), _x - 43, _moveRC.bottom + 27, _drillGear[1]->getFrameX(),
		_drillGear[1]->getFrameY());
	_drillGear[2]->frameRender(getMemDC(), _x - 43, _moveRC.bottom - 19, _drillGear[2]->getFrameX(),
		_drillGear[2]->getFrameY());

	_drillUi->render(getMemDC(), _x - 45, _moveRC.bottom - 25);
	_drillGauge->render(getMemDC(), _x - 45 + 23, _moveRC.bottom - 25 + 50, 0, 0, _curDrillGauge, _drillGauge->getHeight());
}

//드릴 ui 프레임 업데이트
void player::drillFrameUpdate(void)
{
	if (0.1f + _drillFrameCount <= TIMEMANAGER->getWorldTime())
	{
		_drillFrameCount = TIMEMANAGER->getWorldTime();
		if (_drillGear[0]->getFrameX() >= _drillGear[0]->getMaxFrameX())
		{
			_drillGear[0]->setFrameX(0);
			_drillGear[1]->setFrameX(0);
			_drillGear[2]->setFrameX(0);
			return;
		}
		_drillGear[0]->setFrameX(_drillGear[0]->getFrameX() + 1);
		_drillGear[1]->setFrameX(_drillGear[1]->getFrameX() + 1);
		_drillGear[2]->setFrameX(_drillGear[2]->getFrameX() + 1);
	}
}

//드릴 게이지 관리
void player::drillGaugeManagement(void)
{
	if (_state != DRILL)
	{
		_drillingGetItemCount = 0;
		_curDrillGauge = 0;
		return;
	}

	_drBtnDelay -= TIMEMANAGER->getElapsedTime();
	if (_drBtnDelay < 0) _drBtnDelay = 0.0f;

	if (KEYMANAGER->isStayKeyDown(VK_SPACE) && _drBtnDelay == 0)
	{
		switch (_whatMap)
		{
		case 0:
			if (!SOUNDMANAGER->isPlaySound("드릴_모래"))
			{
				SOUNDMANAGER->play("드릴_모래", 0.5f);
			}
			break;
		case 1:
			if (!SOUNDMANAGER->isPlaySound("드릴_잔디"))
			{
				SOUNDMANAGER->play("드릴_잔디", 0.5f);
			}
			break;
		case 2:
			if (!SOUNDMANAGER->isPlaySound("드릴_돌"))
			{
				SOUNDMANAGER->play("드릴_돌", 0.5f);
			}
			break;
		default:
			break;
		}
		_drBtnDelay = 0.00f;
		_curDrillGauge += 1;
		_drillingGetItemCount += 0.25f;
		if (_drillingGetItemCount >= 60)
		{
			_drillingGetItemCount = 0;
			_curDrillGauge = 0;
			drillGetItem();
			_state = UNMOVING;
			_tmExp += (int)(_maxTmExp / (float)100);

			SOUNDMANAGER->stop("드릴_모래");
			SOUNDMANAGER->stop("드릴_잔디");
			SOUNDMANAGER->stop("드릴_돌");
			return;
		}
		if (_curDrillGauge > _maxDrillGauge) _curDrillGauge = _maxDrillGauge;
	}
	else
	{
		_curDrillGauge -= 0.3f;
		_drillingGetItemCount -= 0.25f;
		if (_drillingGetItemCount <= 0) _drillingGetItemCount = 0;

		if (_curDrillGauge < 0) _curDrillGauge = 0;

		SOUNDMANAGER->stop("드릴_모래");
		SOUNDMANAGER->stop("드릴_잔디");
		SOUNDMANAGER->stop("드릴_돌");
	}
}

//드릴링으로 아이템 얻기
void player::drillGetItem(void)
{
	float k = RND->getFromfloatTo(0, 1) * 100;

	if (k <= _da)
	{
		if (_inventory.size() < _maxSize)
		{
			if (k < _da / 10)
				_inventory.push_back(ITEMDB->returnItemUsingEnum(ITEM_WEAPON_3));
			else if (k < _da * 2 / 10)
				_inventory.push_back(ITEMDB->returnItemUsingEnum(ITEM_HAT_3));
			else if (k < _da * 3 / 10)
				_inventory.push_back(ITEMDB->returnItemUsingEnum(ITEM_SHIELD_3));
			else if (k < _da * 4 / 10)
				_inventory.push_back(ITEMDB->returnItemUsingEnum(ITEM_DRILL_3));
			else if (k < _da * 5 / 10)
				_inventory.push_back(ITEMDB->returnItemUsingEnum(ITEM_ACCESSORY_3));
			else if (k < _da * 6 / 10)
				_inventory.push_back(ITEMDB->returnItemUsingEnum(ITEM_WEAPON_1));
			else if (k < _da * 7 / 10)
				_inventory.push_back(ITEMDB->returnItemUsingEnum(ITEM_HAT_1));
			else if (k < _da * 8 / 10)
				_inventory.push_back(ITEMDB->returnItemUsingEnum(ITEM_SHIELD_1));
			else if (k < _da * 9 / 10)
				_inventory.push_back(ITEMDB->returnItemUsingEnum(ITEM_DRILL_1));
			else if (k < _da)
				_inventory.push_back(ITEMDB->returnItemUsingEnum(ITEM_ACCESSORY_1));
		}
	}
	else return;

	return;
}

//레벨 tm 업
void player::lvTmUp(void)
{
	if (_lvExp >= _maxLvExp)
	{
		_lv++;
		_lvExp -= _maxLvExp;
		_maxLvExp *= 1.2;
		_bonusStat += 4;
		_ap += 3;
		_ac += 1;
		_dx += 2;
		_maxMp += 50;
		_mp = _maxMp;
		_wt += 1;
		_da += 1;
		_lk += 2;
		_maxHp += 50;
		_hp = _maxHp;
		_dp += 3;
		_hv += 2;
		SOUNDMANAGER->play("레벨업", 0.7f);
	}

	if (_tmExp >= _maxTmExp)
	{
		_tm++;
		_tmExp -= _maxTmExp;
		_maxTmExp *= 1.2f;
		_skillPoint++;
		this->tmLvUpEffectRender();
		SOUNDMANAGER->play("레벨업", 0.7f);
	}
}

//자동 hp mp 회복
void player::autoUp(void)
{
	_autoUpCount += TIMEMANAGER->getElapsedTime();

	if (_autoUpCount > 5)
	{
		_hp += _maxHp / 50;
		_mp += _maxMp / 50;;
		if (_hp > _maxHp) _hp = _maxHp;
		if (_mp > _maxMp) _mp = _maxMp;

		_autoUpCount = 0;
	}
}

//전체적 스킬 관리
void player::skillManagement(void)
{
	//스킬1
	if (_skill[0].isGet)
	{
		_skill[0].x = _uiManagerLink->getSkillQx() + 3;
		_skill[0].y = _uiManagerLink->getSkillQy() + 3;
	}

	//스킬2
	if (_skill[1].isGet)
	{
		_skill[1].x = _uiManagerLink->getSkillQx() + 35;
		_skill[1].y = _uiManagerLink->getSkillQy() + 3;

		if (_skill[1].isPlay) _isAllMiss = true;
		else _isAllMiss = false;
	}

	//스킬3
	if (_skill[2].isGet)
	{
		_skill[2].x = _uiManagerLink->getSkillQx() + 67;
		_skill[2].y = _uiManagerLink->getSkillQy() + 3;

		if (_skill[2].isPlay) _isCounter = true;
		else _isCounter = true;
	}
}

//스킬 아이콘 출력
void player::skillIconRender(int i)
{
	if (_skill[i].isGet)
	{
		if (i == 0)
		{
			_skill[i].skillIcon->render(getCameraDC(), _skill[i].x, _skill[i].y,
				0, 0, _skill[i].skillIcon->getWidth(), _skill[i].skillIcon->getHeight() * _skill[i].skillCoolTime / 6);
		}
		else if (i == 1 || i == 2)
		{
			_skill[i].skillIcon->render(getCameraDC(), _skill[i].x, _skill[i].y,
				0, 0, _skill[i].skillIcon->getWidth(), _skill[i].skillIcon->getHeight() * _skill[i].skillCoolTime / 180);
		}
	}
}

//스킬 이펙트 출력
void player::skillEffectRender(void)
{
	if (_skill[0].isGet)
	{
		if (_skill[0].isPlay)
		{
			_state = ATTACKING;
			if (_attack[_direction / 2]->getFrameX() >= 4)
			{
				switch (_direction / 2)
				{
				case 0:
					_skill[0].skillEffect->frameRender(getMemDC(), _x + 20, _y - 90, _skill[0].skillEffect->getFrameX(),
						_skill[0].skillEffect->getFrameY());
					break;
				case 1:
					_skill[0].skillEffect->frameRender(getMemDC(), _x - 100, _y - 90, _skill[0].skillEffect->getFrameX(),
						_skill[0].skillEffect->getFrameY());
					break;
				case 2:
					_skill[0].skillEffect->frameRender(getMemDC(), _x - 100, _y + 10, _skill[0].skillEffect->getFrameX(),
						_skill[0].skillEffect->getFrameY());
					break;
				case 3:
					_skill[0].skillEffect->frameRender(getMemDC(), _x + 20, _y + 10, _skill[0].skillEffect->getFrameX(),
						_skill[0].skillEffect->getFrameY());
					break;
				}
			}
		}
	}

	if (_skill[1].isGet)
	{
		if (_skill[1].isPlay)
		{
			_skill[1].skillEffect->frameRender(getMemDC(), _x, _y - _skill[1].skillEffect->getFrameHeight() - 30,
				_skill[1].skillEffect->getFrameX(), _skill[1].skillEffect->getFrameY());
		}
	}

	if (_skill[2].isGet)
	{
		if (_skill[2].isPlay)
		{
			_skill3This->frameRender(getMemDC(), _x + 10, _y - _skill3This->getHeight() - 40, _skill3This->getFrameX(),
				_skill3This->getFrameY());
		}
	}
}

//스킬 이펙트 프레임 돌리기
void player::skillFraming(void)
{
	//스킬1
	if (_skill[0].isPlay)
	{
		if (0.05f + _skill[0].frameCount <= TIMEMANAGER->getWorldTime())
		{
			_skill[0].frameCount = TIMEMANAGER->getWorldTime();
			if (_skill[0].skillEffect->getFrameX() >= _skill[0].skillEffect->getMaxFrameX())
			{
				_skill[0].skillEffect->setFrameX(0);
				return;
			}
			_skill[0].skillEffect->setFrameX(_skill[0].skillEffect->getFrameX() + 1);
		}


	}

	//스킬 2
	if (_skill[1].isPlay)
	{
		if (0.08f + _skill[1].frameCount <= TIMEMANAGER->getWorldTime())
		{
			_skill[1].frameCount = TIMEMANAGER->getWorldTime();
			if (_skill[1].skillEffect->getFrameX() >= _skill[1].skillEffect->getMaxFrameX())
			{
				_skill[1].skillEffect->setFrameX(0);
			}
			_skill[1].skillEffect->setFrameX(_skill[1].skillEffect->getFrameX() + 1);
		}
	}

	//스킬3
	if (_skill[2].isPlay)
	{
		if (0.08f + _skill3FrameCount <= TIMEMANAGER->getWorldTime())
		{
			_skill3FrameCount = TIMEMANAGER->getWorldTime();
			if (_skill3This->getFrameX() >= _skill3This->getMaxFrameX())
			{
				_skill3This->setFrameX(0);
			}
			_skill3This->setFrameX(_skill3This->getFrameX() + 1);
		}
	}
}

//스킬 2 지속시간 계산
void player::skill1CalculateHowLong(void)
{
	//스킬2
	if (_skill[1].isGet)
	{
		if (_skill[1].isPlay)
		{
			_skill[1].skillHowLong += 0.1f;

			if (_skill[1].skillHowLong > 60 + 30 * _skill[1].lv)
			{
				_skill[1].skillEffect->setFrameX(0);
				_skill[1].isPlay = false;
				_skill[1].skillHowLong = 0.0f;
			}
		}
	}

	//스킬3
	if (_skill[2].isGet)
	{
		if (_skill[2].isPlay)
		{
			_skill[2].skillHowLong += 0.1f;

			if (_skill[2].skillHowLong > 60 + 30 * _skill[2].lv)
			{
				//여기에 프레임셋(0)추가
				_skill[2].isPlay = false;
				_skill[2].skillHowLong = 0.0f;
				_thunderCount = 0;
				_isThunder = false;
			}
		}
	}
}

//스킬 쿨타임 계산
void player::checkSkillCoolTime(void)
{
	//스킬 1 쿨타임
	if (_skill[0].isCool)
	{
		_skill[0].skillCoolTime += 0.1f;

		if (_skill[0].skillCoolTime >= 6)
		{
			_skill[0].isCool = false;
			_skill[0].skillCoolTime = 6.0f;
		}
	}

	//스킬2 쿨타임
	if (_skill[1].isCool)
	{
		_skill[1].skillCoolTime += 0.1f;
		
		if (_skill[1].skillCoolTime >= 180)
		{
			_skill[1].isCool = false;
			_skill[1].skillCoolTime = 180.0f;
		}
	}

	//스킬3 쿨타임
	if (_skill[2].isCool)
	{
		_skill[2].skillCoolTime += 0.1f;

		if (_skill[2].skillCoolTime >= 180)
		{
			_skill[2].isCool = false;
			_skill[2].skillCoolTime = 180.0f;
		}
	}
}

//스킬 사용
void player::usingSkill(void)
{
	//스킬 1 사용
	if (KEYMANAGER->isStayKeyDown('1') && _skill[0].isGet
		&& !_skill[0].isCool && _mp >= _skill[0].lv * 15)
	{
		_skill[0].isPlay = true;
		_skill[0].isCool = true;
		_skill[0].skillCoolTime = 0.0f;
		_skill[0].skillHowLong = 0.0f;
		_mp -= _skill[0].lv * 15;
	}

	//스킬 2 사용
	if (KEYMANAGER->isStayKeyDown('2') && _skill[1].isGet
		&& !_skill[1].isCool && _mp >= _skill[1].lv * 30)
	{
		_skill[1].isPlay = true;
		_skill[1].isCool = true;
		_skill[1].skillCoolTime = 0.0f;
		_skill[1].skillHowLong = 0.0f;
		_mp -= _skill[1].lv * 30;

		SOUNDMANAGER->play("스킬2사용", 0.6f);
	}

	//스킬 3 사용
	if (KEYMANAGER->isStayKeyDown('3') && _skill[2].isGet
		&& !_skill[2].isCool && _mp >= _skill[2].lv * 40)
	{
		_skill[2].isPlay = true;
		_skill[2].isCool = true;
		_skill[2].skillCoolTime = 0.0f;
		_skill[2].skillHowLong = 0.0f;
		_mp -= _skill[2].lv * 40;
	}
}

void player::thunderShot(void)
{
	if (_skill[2].isPlay)
	{
		if (!_isThunder)
			_thunderCount += TIMEMANAGER->getElapsedTime();
		
		if (_thunderCount >= 5)
		{
			_isThunder = true;
		}
	}
}

void player::thunderRender(int x, int y)
{
	if (_isThunder)
	{
		if (0.05 + _skill[2].frameCount <= TIMEMANAGER->getWorldTime())
		{
			_skill[2].frameCount = TIMEMANAGER->getWorldTime();
			if (_skill[2].skillEffect->getFrameX() >= _skill[2].skillEffect->getMaxFrameX())
			{
				_skill[2].skillEffect->setFrameX(0);
				_isThunder = false;
				_thunderCount = 0;
			}
			_skill[2].skillEffect->setFrameX(_skill[2].skillEffect->getFrameX() + 1);
		}

		_skill[2].skillEffect->frameRender(getMemDC(), x, y + 20, _skill[2].skillEffect->getFrameX(), _skill[2].skillEffect->getFrameY());
	}
}

//몬스터한테 벼락떨어지는거 렌더
void player::thunderThunder(void)
{
	if (_isThunder)
	{
		RECT temp;
		RECT thunderRC = RectMake(_x - 100, _y - 100, 200, 200);
		for (int i = 0; i < _enemyManagerLink->getEnemyVec(_mapManagerLink->getWhatMap()).size(); i++)
		{
			if (IntersectRect(&temp, &thunderRC, &_enemyManagerLink->getEnemyVec(_mapManagerLink->getWhatMap())[i]->getMoveRC()))
			{
				thunderRender((_enemyManagerLink->getEnemyVec(_mapManagerLink->getWhatMap())[i]->getMoveRC().right + _enemyManagerLink->getEnemyVec(_mapManagerLink->getWhatMap())[i]->getMoveRC().left) / 2 - _skill[2].skillEffect->getFrameWidth() / 2,
					(_enemyManagerLink->getEnemyVec(_mapManagerLink->getWhatMap())[i]->getMoveRC().bottom + _enemyManagerLink->getEnemyVec(_mapManagerLink->getWhatMap())[i]->getMoveRC().top) / 2 - 60);

				if (_skill[2].skillEffect->getFrameX() == _skill[2].skillEffect->getMaxFrameX())
				{
					_enemyManagerLink->getEnemyVec(_mapManagerLink->getWhatMap())[i]->setHp(
						_enemyManagerLink->getEnemyVec(_mapManagerLink->getWhatMap())[i]->getHp() - _skill[2].lv * 30
						+ _enemyManagerLink->getEnemyVec(_mapManagerLink->getWhatMap())[i]->getDef());
					_hitEnemy = _enemyManagerLink->getEnemyVec(_mapManagerLink->getWhatMap())[i];
					_hitEnemy->setIsFightOrNot(true);
					damagePushBack(_skill[2].lv * 30
						- _enemyManagerLink->getEnemyVec(_mapManagerLink->getWhatMap())[i]->getDef(), _hitEnemy, false);
					if (SOUNDMANAGER->isPlaySound("천둥소리"))
					{
						SOUNDMANAGER->stop("천둥소리");
						SOUNDMANAGER->play("천둥소리", 0.5f);
					}
					else SOUNDMANAGER->play("천둥소리", 0.5f);
					_skill[2].skillEffect->setFrameX(0);
					_thunderCount = 0;
					_isThunder = false;
					return;
				}
			}
		}
	}
}

void player::skillMasterRender()
{
	
	tagEffect skillMaster;
	skillMaster.effectCount = 0.0f;
	skillMaster.effectElapsedTime = 0.1f;
	skillMaster.x = _x - 30;
	skillMaster.y = _y - 110;
	skillMaster.effectImage = IMAGEMANAGER->findImage("스킬마스터");
	skillMaster.effectOn = true;
	_vEffect.push_back(skillMaster);
}

void player::tmLvUpEffectRender(void)
{
	tagEffect tmLvUpEffect;
	tmLvUpEffect.effectCount = 0.0f;
	tmLvUpEffect.effectElapsedTime = 0.1f;
	tmLvUpEffect.x = _x - 20;
	tmLvUpEffect.y = _y - 110;
	tmLvUpEffect.effectImage = IMAGEMANAGER->findImage("tm레벨업");
	tmLvUpEffect.effectOn = true;
	_vEffect.push_back(tmLvUpEffect);
}

void player::skillLvUpEffectRender(void)
{
	tagEffect tmLvUpEffect;
	tmLvUpEffect.effectCount = 0.0f;
	tmLvUpEffect.effectElapsedTime = 0.1f;
	tmLvUpEffect.x = _x - 20;
	tmLvUpEffect.y = _y - 110;
	tmLvUpEffect.effectImage = IMAGEMANAGER->findImage("스킬레벨업");
	tmLvUpEffect.effectOn = true;
	_vEffect.push_back(tmLvUpEffect);
}

void player::effectRender(void)
{
	for (int i = 0; i < _vEffect.size(); i++)
	{
		if (_vEffect[i].effectOn)
		{
			if (_vEffect[i].effectElapsedTime + _vEffect[i].effectCount
				<= TIMEMANAGER->getWorldTime())
			{
				_vEffect[i].effectCount = TIMEMANAGER->getWorldTime();
				if (_vEffect[i].effectImage->getFrameX() >= _vEffect[i].effectImage->getMaxFrameX())
				{
					_vEffect[i].effectOn = false;
					_vEffect[i].effectImage->setFrameX(0);
					return;
				}
				_vEffect[i].effectImage->setFrameX(_vEffect[i].effectImage->getFrameX() + 1);
			}

			_vEffect[i].effectImage->frameRender(getMemDC(), _vEffect[i].x, _vEffect[i].y,
				_vEffect[i].effectImage->getFrameX(), _vEffect[i].effectImage->getFrameY());
		}
		else
		{
			_vEffect.erase(_vEffect.begin() + i);
			return;
		}
	}
}

//공격 관리
void player::attackManagement()
{
	if (_state != ATTACKING) _attackRC = RectMake(0, 0, 0, 0);

	if (_state == ATTACKING)
	{
		if (_attack[_direction / 2]->getFrameX() == 5)
		{
			if (_weapon == NULL || _weapon->getItemlist() == ITEM_WEAPON_1)
			{
				SOUNDMANAGER->play("무기1소리", 0.5f);
			}
			else if (_weapon->getItemlist() == ITEM_WEAPON_2)
			{
				SOUNDMANAGER->play("무기2소리", 0.5f);
			}
			else SOUNDMANAGER->play("무기3소리", 0.5f);
			_attack[_direction / 2]->setFrameX(_attack[_direction / 2]->getFrameX() + 1);
			_isAttackOk = true;
		}
		else if (_attack[_direction / 2]->getFrameX() == _attack[_direction / 2]->getMaxFrameX())
			_isAttackOk = false;
		

		if (_isAttackOk)
		{
			switch (_direction / 2)
			{
			case 0:
				_attackRC = RectMake(_x + 73, _y - 48, 45, 45);
				_angle = PI_4;
				break;
			case 1:
				_attackRC = RectMake(_x - 43, _y - 48, 45, 45);
				_angle = PI_4 * 3;
				break;
			case 2:
				_attackRC = RectMake(_x - 45, _y + 57, 45, 45);
				_angle = PI_4 * 5;
				break;
			case 3:
				_attackRC = RectMake(_x + 75, _y + 57, 45, 45);
				_angle = PI_4 * 7;
				break;
			}
		}
		else _attackRC = RectMake(-1, -1, 0, 0);

		RECT temp;

		for (int i = 0; i < _enemyManagerLink->getEnemyVec(_mapManagerLink->getWhatMap()).size(); i++)
		{
			if (IntersectRect(&temp, &_enemyManagerLink->getEnemyVec(_mapManagerLink->getWhatMap())[i]->getMoveRC(), &_attackRC) && _isAttackOk
				&& _enemyManagerLink->getEnemyVec(_mapManagerLink->getWhatMap())[i]->getHp() > 0)
			{
				_hitEnemy = _enemyManagerLink->getEnemyVec(_mapManagerLink->getWhatMap())[i];

				if (isHitOn())
				{
					int k = RND->getFromIntTo(1, 100);
					if (k < _lk / 2)
					{
						damagePushBack(attackDamage(k) - _enemyManagerLink->getEnemyVec(_mapManagerLink->getWhatMap())[i]->getDef(), _hitEnemy, true);
					}
					else damagePushBack(attackDamage(k) - _enemyManagerLink->getEnemyVec(_mapManagerLink->getWhatMap())[i]->getDef(), _hitEnemy, false);
				
					_enemyManagerLink->getEnemyVec(_mapManagerLink->getWhatMap())[i]->setHp(
						_enemyManagerLink->getEnemyVec(_mapManagerLink->getWhatMap())[i]->getHp() - attackDamage(k) +
						_enemyManagerLink->getEnemyVec(_mapManagerLink->getWhatMap())[i]->getDef());
					if (!_enemyManagerLink->getEnemyVec(_mapManagerLink->getWhatMap())[i]->getIsFightOrNot())
						_enemyManagerLink->getEnemyVec(_mapManagerLink->getWhatMap())[i]->setIsFightOrNot(true);
				
					if (_skill[0].isPlay)
					{
						SOUNDMANAGER->play("스킬1사용", 0.5f);
					}
					else
					{
						int k = RND->getFromIntTo(1, 5);
						switch (k)
						{
						case 1:
							if (SOUNDMANAGER->isPlaySound("공격소리1"))
							{
								SOUNDMANAGER->stop("공격소리1");
								SOUNDMANAGER->play("공격소리1", 0.5f);
							}
							else SOUNDMANAGER->play("공격소리1", 0.5f);
							break;
						case 2:
							if (SOUNDMANAGER->isPlaySound("공격소리2"))
							{
								SOUNDMANAGER->stop("공격소리2");
								SOUNDMANAGER->play("공격소리2", 0.5f);
							}
							else SOUNDMANAGER->play("공격소리2", 0.5f);
							break;
						case 3:
							if (SOUNDMANAGER->isPlaySound("공격소리3"))
							{
								SOUNDMANAGER->stop("공격소리3");
								SOUNDMANAGER->play("공격소리3", 0.5f);
							}
							else SOUNDMANAGER->play("공격소리3", 0.5f);
							break;
						case 4:
							if (SOUNDMANAGER->isPlaySound("공격소리4"))
							{
								SOUNDMANAGER->stop("공격소리4");
								SOUNDMANAGER->play("공격소리4", 0.5f);
							}
							else SOUNDMANAGER->play("공격소리4", 0.5f);
							break;
						case 5:
							if (SOUNDMANAGER->isPlaySound("공격소리5"))
							{
								SOUNDMANAGER->stop("공격소리5");
								SOUNDMANAGER->play("공격소리5", 0.5f);
							}
							else SOUNDMANAGER->play("공격소리5", 0.5f);
							break;
						}
					}
				}
				else
				{
					SOUNDMANAGER->play("미스", 0.5f);
					damagePushBack(0, _hitEnemy, 0);
				}
				_attack[_direction / 2]->setFrameX(6);
				_isAttackOk = false;
			}
		}
	}
}

int player::attackDamage(int k)
{
	if (_isAttackOk)
	{
		if (_skill[0].isPlay)
		{
			if (k < _lk / 2)
			{
				if (SOUNDMANAGER->isPlaySound("치명타"))
				{
					SOUNDMANAGER->stop("치명타");
					SOUNDMANAGER->play("치명타");
				}
				else SOUNDMANAGER->play("치명타");
				return (int)(4.5 * (float)_ap + _skill[0].lv * 10);
			}
			else return 3 * _ap + _skill[0].lv * 10;
		}
		else
		{
			if (k < _lk / 2)
			{
				if (SOUNDMANAGER->isPlaySound("치명타"))
				{
					SOUNDMANAGER->stop("치명타");
					SOUNDMANAGER->play("치명타");
				}
				else SOUNDMANAGER->play("치명타");
				return (int)(1.5 * (float)_ap);
			}
			else return _ap;
		}
	}
	else return 0;
}

void player::damagePushBack(int damage, enemy* destEnemy, bool isCrit)
{
	tagDamageSkin temp;
	if (isCrit)
		temp.skinImage = IMAGEMANAGER->findImage("폰트7");
	else temp.skinImage = IMAGEMANAGER->findImage("폰트5");
	temp.x = destEnemy->getMoveRC().left + destEnemy->getMoveRC().right;
	temp.x /= 2;
	temp.y = destEnemy->getY();
	temp.alpha = 255;
	temp.isCritical = isCrit;
	if (damage < 0) damage = 0;
	temp.damage = damage;
	_vDamageSkin.push_back(temp);
}

void player::damageRender()
{
	if (_vDamageSkin.size() == 0) return;

	for (int i = 0; i < _vDamageSkin.size(); i++)
	{
		if (!_vDamageSkin[i].isCritical)
		{
			_vDamageSkin[i].damageRender(getMemDC());
			_vDamageSkin[i].alpha -= 10;
			_vDamageSkin[i].y--;

		}
		else
		{
			IMAGEMANAGER->findImage("치명타뒷배경")->alphaRender(getMemDC(),
				_vDamageSkin[i].x - 28, _vDamageSkin[i].y - 17, _vDamageSkin[i].alpha);
			_vDamageSkin[i].damageRender(getMemDC());
			_vDamageSkin[i].alpha -= 5;
			_vDamageSkin[i].y--;
		}

		if (_vDamageSkin[i].alpha <= 0)
		{
			_vDamageSkin.erase(_vDamageSkin.begin() + i);
			return;
		}
	}
}

//치트키
void player::cheatKey()
{
	//경험치 증가
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_lvExp += (int)(_maxLvExp / (float)5);
		_tmExp += (int)(_maxTmExp / (float)5);
		_money += 5000;
	}
}

//공격 키 누르면 공격함
void player::attackControl()
{
	if (KEYMANAGER->isOnceKeyDown('Z') && (_state == UNMOVING || _state == MOVING))
	{
		_attack[0]->setFrameX(0);
		_attack[1]->setFrameX(0);
		_attack[2]->setFrameX(0);
		_attack[3]->setFrameX(0);
		_attackRC = RectMake(0, 0, 0, 0);
		this->changeState(ATTACKING);
	}
}

//드릴 키 누르면 드릴링함
void player::drillControl()
{
	if (KEYMANAGER->isOnceKeyDown('D') && _state == UNMOVING)
	{
		this->changeState(DRILL);
	}
}

//디버그 모드 렌더
void player::debugRender()
{
	if (KEYMANAGER->isToggleKey(VK_F2))
	{
		char str[128];
		sprintf(str, "%d", _direction);
		fontRender("NtreevSoft", str, 20, 1, _x, _y + 70, RGB(0, 0, 0));
		sprintf(str, "%2.2f", _thunderCount);
		fontRender("NtreevSoft", str, 20, 1, _x, _y + 90, RGB(0, 0, 0));
		sprintf(str, "%d", _whatMap);
		fontRender("NtreevSoft", str, 20, 1, _x, _y + 110, RGB(0, 0, 0));

		Rectangle(getMemDC(), _moveRC.left, _moveRC.top, _moveRC.right, _moveRC.bottom);

		RectangleMake(getMemDC(), _attackRC.left, _attackRC.top, 35, 35);
	}
}

void player::hitEnemyInfoRender(HDC hdc, int x, int y)
{
	if (_hitEnemy == NULL) return;

	if (_hitEnemy->getWhatMap() != _whatMap)
	{
		_hitEnemy = NULL;
		return;
	}

	if (_hitEnemy->getHp() <= 0)
	{
		_hitEnemy = NULL;
		return;
	}

	_enemyBack->render(hdc, x, y);
	_enemyBar->render(hdc, x + 8, y + 39, 0, 0, _hitEnemy->getHp() / (float)_hitEnemy->getMaxHp() * _enemyBar->getWidth(), _enemyBar->getHeight());

	int k = _lv - _hitEnemy->getLv();

	if (255 - abs(k) * 55 < 0 && k < 0) k = -255;
	else if (255 - abs(k) * 55 < 0 && k > 0) k = 255;

	COLORREF s;
	if (k < 0)
		s = RGB(255, 255 + k * 55, 0);
	else if (k > 0)
		s = RGB(255 - k * 55, 255, 0);
	else s = RGB(255, 255, 255);

	fontCameraRender("NtreevSoft", _hitEnemy->getName(), 15, 1, x + 60, y + 13, s);
	char str[128];
	sprintf_s(str, "LV : %d", _hitEnemy->getLv());
	fontCameraRender("NtreevSoft", str, 15, 1, x + 120, y + 13, s);
}

bool player::isHitOn()
{
	if (_hitEnemy == NULL) return false;

	int k = RND->getFromIntTo(1, 100);

	if (k < 100 + _dx - _hitEnemy->getAgi()) return true;

	return false;
}
