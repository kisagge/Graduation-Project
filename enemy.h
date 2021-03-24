#pragma once
#include "gameNode.h"

enum MONSTATE
{
	IDLE,
	WALK,
	ATTACK,
	HIT,
	DEAD
};

class playerManager;

class enemy : public gameNode
{
protected:
	image* _idleImage;				//서있는 이미지
	image* _walkImage;				//걷는 이미지
	image* _attackImage;			//공격 이미지
	image* _hitImage;				//맞는 이미지
	image* _deadImage;				//죽을때 이미지
	RECT _moveRC;					//이동 RC ( 피격과 관련 )
	RECT _imageRC;					//이미지 출력 RC
	MONSTATE _state;				//몬스터 자세한 상태

	int _x, _y;						//몬스터 좌표
	char name[128];					//몬스터 이름

	int _att, _def;					//몬스터 공격력, 방어력
	int _hp, _mp;					//몬스터 hp, mp
	int _maxHp, _maxMp;				//몬스터 maxHp, maxMp
	int _agi;						//회피율
	int _dex;						//명중률

	float _speed;					//몬스터 이동 스피드
	float _angle;					//몬스터 각도
	
	int _exp;						//몬스터 경험치
	int _lv;						//몬스터 레벨

	//이동관련 변수들
	int _startX, _startY;			//이동할 때 시작 x,y
	int _endX, _endY;				//도착할 x,y
	int _direction;					//방향
	float _stopTime;				//끼임 방지 변수

	//프레임 카운트들
	float _walkFrameCount;
	float _attackFrameCount;
	float _hitFrameCount;
	float _deadFrameCount;
	int _frameX, _frameY;

	bool _fightOrNot;
	bool _patrolOn;
	float _escapeCount;

	playerManager* _playerManagerLink;

	bool _isTargetOn;
	RECT _sensorRC;
	float _attackDelay;
	RECT _attackRC;

	bool _isDead = false;

	//지금 어디맵에 있는지
	int _whatMap;

	//데미지 스킨 정보 담는 벡터
	vector<tagDamageSkin> _vDamageSkin;

	ENEMYLIST _enemyList;
public:
	virtual HRESULT init(void);
	virtual HRESULT init(int x, int y);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//겟셋 start
	int getX(){ return _x; }
	int getY(){ return _y; }

	int getAtt(){ return _att; }
	void setAtt(int att){ _att = att; }
	
	int getDef(){ return _def; }
	void setDef(int def){ _def = def; }

	int getAgi(){ return _agi; }

	int getDex(){ return _dex; }

	int getHp(){ return _hp; }
	void setHp(int hp){ _hp = hp; }

	int getMp(){ return _mp; }
	void setMp(int mp){ _mp = mp; }

	int getMaxHp(){ return _maxHp; }

	int getMaxMp(){ return _maxMp; }

	int getExp(){ return _exp; }
	int getLv(){ return _lv; }
	RECT getMoveRC(){ return _moveRC; }
	RECT getImageRC(){ return _imageRC; }
	MONSTATE  getState(){ return _state; }
	void setState(MONSTATE st){ _state = st; }
	bool getIsDead(){ return _isDead; }
	bool getIsFightOrNot(){ return _fightOrNot; }
	void setIsFightOrNot(bool k){ _fightOrNot = k; }
	char* getName(){ return name; }
	ENEMYLIST getEnemyList(){ return _enemyList; }

	int getWhatMap(){ return _whatMap; }
	void setWhatMap(int k){ _whatMap = k; }
	//겟셋 finish
	
	//상호참조 링크들
	void setPlayerManagerLink(playerManager* pl){ _playerManagerLink = pl; }

	//렉트 잡아주는 함수들
	virtual void setMonRect(void);
	virtual void setMonRectIdle(void);
	virtual void setMonRectWalk(void);

	//이동관련 함수들
	virtual void stopTimeCalculation(void);			//정지시간 빼주기
	virtual void moveManagement(void);				//이동 가능하냐 안하냐
	virtual void move(int destX, int destY, int sourX, int sourY);


	//방향 설정 ( 각도에 따라 설정 )
	virtual void setDirection();

	//프레임 돌리는 함수들
	virtual void animaition();			//애니메이션 종합
	virtual void idleAni();				//서있는 애니메이션
	virtual void walkAni();				//걷는 애니메이션
	virtual void attackAni();			//공격 애니메이션
	virtual void hitAni();				//피격 애니메이션
	virtual void deadAni();				//죽는 애니메이션
	
	//상태 변환
	virtual void changeState(MONSTATE state);

	//이미지 출력 함수 ( z오더에 넣기 )
	virtual void aniRender();			//애니메이션 종합 렌더
	virtual void idleAniRender();		//서있는 상태 렌더
	virtual void walkAniRender();		//걷는 모션 렌더
	virtual void attackAniRender();		//공격 모션 렌더
	virtual void hitAniRender();		//피격 모션 렌더
	virtual void deadAniRender();		//죽는 모션 렌더

	virtual void attackManagement();	//공격관리
	virtual RECT returningAttackRC(int directiokn);

	virtual void damagePushBack(int damage, playerManager* pl);
	virtual void damageRender();

	//디버그 모드 관리
	virtual void debugUpdate();			//디버그 모드 업데이트 관리
	virtual void debugRender();			//디버그 모드 렌더 관리

	enemy();
	~enemy();
};

