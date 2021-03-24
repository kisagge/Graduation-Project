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
	image* _idleImage;				//���ִ� �̹���
	image* _walkImage;				//�ȴ� �̹���
	image* _attackImage;			//���� �̹���
	image* _hitImage;				//�´� �̹���
	image* _deadImage;				//������ �̹���
	RECT _moveRC;					//�̵� RC ( �ǰݰ� ���� )
	RECT _imageRC;					//�̹��� ��� RC
	MONSTATE _state;				//���� �ڼ��� ����

	int _x, _y;						//���� ��ǥ
	char name[128];					//���� �̸�

	int _att, _def;					//���� ���ݷ�, ����
	int _hp, _mp;					//���� hp, mp
	int _maxHp, _maxMp;				//���� maxHp, maxMp
	int _agi;						//ȸ����
	int _dex;						//���߷�

	float _speed;					//���� �̵� ���ǵ�
	float _angle;					//���� ����
	
	int _exp;						//���� ����ġ
	int _lv;						//���� ����

	//�̵����� ������
	int _startX, _startY;			//�̵��� �� ���� x,y
	int _endX, _endY;				//������ x,y
	int _direction;					//����
	float _stopTime;				//���� ���� ����

	//������ ī��Ʈ��
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

	//���� ���ʿ� �ִ���
	int _whatMap;

	//������ ��Ų ���� ��� ����
	vector<tagDamageSkin> _vDamageSkin;

	ENEMYLIST _enemyList;
public:
	virtual HRESULT init(void);
	virtual HRESULT init(int x, int y);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//�ټ� start
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
	//�ټ� finish
	
	//��ȣ���� ��ũ��
	void setPlayerManagerLink(playerManager* pl){ _playerManagerLink = pl; }

	//��Ʈ ����ִ� �Լ���
	virtual void setMonRect(void);
	virtual void setMonRectIdle(void);
	virtual void setMonRectWalk(void);

	//�̵����� �Լ���
	virtual void stopTimeCalculation(void);			//�����ð� ���ֱ�
	virtual void moveManagement(void);				//�̵� �����ϳ� ���ϳ�
	virtual void move(int destX, int destY, int sourX, int sourY);


	//���� ���� ( ������ ���� ���� )
	virtual void setDirection();

	//������ ������ �Լ���
	virtual void animaition();			//�ִϸ��̼� ����
	virtual void idleAni();				//���ִ� �ִϸ��̼�
	virtual void walkAni();				//�ȴ� �ִϸ��̼�
	virtual void attackAni();			//���� �ִϸ��̼�
	virtual void hitAni();				//�ǰ� �ִϸ��̼�
	virtual void deadAni();				//�״� �ִϸ��̼�
	
	//���� ��ȯ
	virtual void changeState(MONSTATE state);

	//�̹��� ��� �Լ� ( z������ �ֱ� )
	virtual void aniRender();			//�ִϸ��̼� ���� ����
	virtual void idleAniRender();		//���ִ� ���� ����
	virtual void walkAniRender();		//�ȴ� ��� ����
	virtual void attackAniRender();		//���� ��� ����
	virtual void hitAniRender();		//�ǰ� ��� ����
	virtual void deadAniRender();		//�״� ��� ����

	virtual void attackManagement();	//���ݰ���
	virtual RECT returningAttackRC(int directiokn);

	virtual void damagePushBack(int damage, playerManager* pl);
	virtual void damageRender();

	//����� ��� ����
	virtual void debugUpdate();			//����� ��� ������Ʈ ����
	virtual void debugRender();			//����� ��� ���� ����

	enemy();
	~enemy();
};

