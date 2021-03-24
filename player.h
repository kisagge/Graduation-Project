#pragma once
#include "gameNode.h"
#include "item.h"

enum STATE
{
	MOVING,
	UNMOVING,
	ATTACK_IDLE,
	ATTACKING,
	DAMAGED,
	DRILL,
	HITHIT
};

class mapManager;
class uiManager;
class enemyManager;
class enemy;

struct tagSkill
{
	int x, y;				//��ų ������ ��ǥ
	RECT rc;				//��ų ������ ��Ʈ
	image* skillIcon;
	float skillCoolTime;
	int showX, showY;
	image* skillEffect;
	bool isGet;
	float frameCount;
	bool isPlay;
	bool isCool;			//��Ÿ���̳�
	int damage;
	int lv;
	
	float skillHowLong;
};

struct tagEffect
{
	int x, y;
	float effectCount;
	float effectElapsedTime;
	image* effectImage;
	bool effectOn;
};

class player : public gameNode
{
private:
	//��Ʈ��
	RECT _imageRc;
	RECT _moveRC;

	//�÷��̾� ���� (1)
	float _x, _y;				//�÷��̾� ��ǥ
	int _speed;					//�ø����� �̵��ӵ�
	float _angle;				//�÷��̾� ����
	int _hp, _mp;				//�÷��̾� hp, mp
	int _maxHp, _maxMp;			//�÷��̾� maxHp, maxMp

	int _imageX, _imageY;		//�̹��� ��� x,y

	STATE _state;				//�÷��̾� ����

	float _startX, _startY;		//�÷��̾� �̵� ����x,y
	float _endX, _endY;			//�÷��̾� �̵� ����x,y

	//�÷��̾� �̹��� ������ ī��Ʈ
	float _frameCount;
	float _walkFrameCount;
	float _attackFrameCount;
	float _hitFrameCount;
	float _anoDrillFrameCount = 0.0f;
	float _specialTime;			//Ư���ൿ �ð� ���
	float _attackIdleCount = 0.0f;

	int _lv;					//����
	int _lvExp, _maxLvExp;		//���� ����ġ, �ƽ�����ġ
	int _tm;					//tm
	int _tmExp, _maxTmExp;		//tm ����ġ, �ƽ� ����ġ
	bool _fightOrNot;			//�������³� �ƴϳ�

	//��ȣ���� ������
	mapManager* _mapManagerLink;
	uiManager* _uiManagerLink;
	enemyManager* _enemyManagerLink;

	//�̹�����
	image* _idle;
	image* _walk[8];
	image* _specialImg;
	image* _attackIdle[4];
	image* _attack[4];
	image* _drilling;
	image* _drill;
	image* _hitImage;

	int _direction;				//���� ( ������ ���� �ٲ� )

	image* _hpMinibar;			//�÷��̾� �ϴ� ü��ǥ�� �̴Ϲ�
	image* _mpMinibar;			//�÷��̾� �ϴ� ����ǥ�� �̴Ϲ�

	int _money;					//��

	//�÷��̾� ��������
	int _ap;				//���ݷ�
	float _ac;				//���ݼӵ�
	int _dx;				//���߷�	
	int _wt;				//����
	int _da;				//�帱 ������
	int _lk;				//ũ��Ƽ��
	int _dp;				//����
	int _hv;				//ȸ����

	char*_name = "GoldenSpoon";

	int _nowWeight;			//���� ����
	int _maxWeight;			//�ִ� ����

	int _bonusStat;			//���ʽ� ����
	int _skillPoint;		//��ų����Ʈ

	vector<item*> _inventory;	//�κ��丮
	int _maxSize = 18;			//�κ��丮 �ƽ� ������
	
	item* _helmet;			//���
	item* _shield;			//����
	item* _weapon;			//����
	item* _accessory;		//�Ǽ�����
	item* _drillItem;		//�帱

	//�帱 ���� UI
	image* _drillUi;
	image* _drillGear[3];
	image* _drillGauge;
	float _drillFrameCount = 0.0f;
	int _maxDrillGauge;
	int _curDrillGauge;
	float _drBtnDelay = 0.0f;
	float _drillingGetItemCount = 0.0f;

	//ü�� ����, �ڿ� ȸ��
	float _autoUpCount = 0.0f;

	//��ų ������
	tagSkill _skill[3];
	float _skill1FrameCount = 0.0f;
	float _skill3FrameCount = 0.0f;
	image* _skill3This;

	//Ư�� ����
	bool _isAllMiss = false;		//���� ȸ�ǳ�

	//ī���� ����
	bool _isCounter = false;		//ī���� ���³�
	bool _isThunder = false;
	float _thunderCount = 0.0f;

	//�������� ������
	RECT _attackRC;					//���� ���� ��Ʈ
	bool _isAttackOk;				//�� �� ���� �����ϸ� ������ ���̻� �ȵ��� �ϴ� ����
	RECT _hitRC;
	bool _isHit;

	//��� ���̳�
	int _whatMap;

	//���� ���� ��� ����
	enemy* _hitEnemy = NULL;

	image* _enemyBack = IMAGEMANAGER->findImage("��������ǥ��");
	image* _enemyBar = IMAGEMANAGER->findImage("����ü��ǥ�ù�");

	//������ ��Ų ���� ��� ����
	vector<tagDamageSkin> _vDamageSkin;

	//��ų ������ ����Ʈ
	float _skillMasterCount = 0.0f;
	image* _skillMasterImage;
	bool _isSkillMasterOn = false;

	vector<tagEffect> _vEffect;
public:
	HRESULT init(void);
	HRESULT init(int x, int y);
	void release(void);
	void update(void);
	void render(void);

	//�⺻ �ټ�
	int getX(){ return _x; }
	void setX(int x){ _x = x; }

	int getY(){ return _y; }
	void setY(int y){ _y = y; }

	int getSpeed(){ return _speed; }
	RECT getMoveRc(){ return _moveRC; }

	int getHp(){ return _hp; }
	void setHp(int hp){ _hp = hp; }
	int getMp(){ return _mp; }
	void setMp(int mp){ _mp = mp; }
	int getMaxHp(){ return _maxHp; }
	void setMaxHp(int k){ _maxHp = k; }
	int getMaxMp(){ return _maxMp; }
	void setMaxMp(int k){ _maxMp = k; }
	int getLvExp(){ return _lvExp; }			//���� ����ġ
	void setLvExp(int k){ _lvExp = k; }
	int getTmExp(){ return _tmExp; }
	void setTmExp(int k){ _tmExp = k; }
	int getMaxLvExp(){ return _maxLvExp; }		//�ƽ� ����ġ
	int getMaxTmExp(){ return _maxTmExp; }
	STATE getState(){ return _state; }
	void setState(STATE state){ _state = state; }
	int getLv(){ return _lv; }					//���� �ټ�
	void setLv(int lv){ _lv = lv; }
	int getTm(){ return _tm; }					//tm �ټ�
	void setTm(int tm){ _tm = tm; }

	int getWhatMap(){ return _whatMap; }
	//��, ���� �ټ�
	int getMoney(){ return _money; }
	void setMoney(int money){ _money = money; }
	int getWeight(){ return _nowWeight; }
	int getMaxWeight(){ return _maxWeight; }

	//���� �ټ�
	int getAp(){ return _ap; }
	void setAp(int ap){ _ap = ap; }
	float getAc(){ return _ac; }
	void setAc(float ac){ _ac = ac; }
	int getDx(){ return _dx; }
	void setDx(int dx){ _dx = dx; }
	int getWt(){ return _wt; }
	void setWt(int wt){ _wt = wt; }
	int getDa(){ return _da; }
	void setDa(int da){ _da = da; }
	int getLk(){ return _lk; }
	void setLk(int lk){ _lk = lk; }
	int getDp(){ return _dp; }
	void setDp(int dp){ _dp = dp; }
	int getHv(){ return _hv; }
	void setHv(int hv){ _hv = hv; }
	int getBonusStat(){ return _bonusStat; }
	void setBonusStat(int bs){ _bonusStat = bs; }
	int getSkillPoint(){ return _skillPoint; }
	void setSkillPoint(int sp){ _skillPoint = sp; }

	//�κ��丮 ���� �ټ�
	int getInvenMaxSize(){ return _maxSize; }
	vector<item*> getInven(){ return _inventory; }
	int getInventorySize(){ return _inventory.size(); }
	item* getInvenItem(int i){ return _inventory.at(i); }
	void eraseItem(int i){ _inventory.erase(_inventory.begin() + i); }

	//������ �ټ�
	item* getHelmet(){ return _helmet; }
	void setHelmet(item* helmet){ _helmet = helmet; }
	item* getWeapon(){ return _weapon; }
	void setWeapon(item* weapon){ _weapon = weapon; }
	item* getShield(){ return _shield; }
	void setShield(item* shield){ _shield = shield; }
	item* getAccessory(){ return _accessory; }
	void setAccessory(item* accessory){ _accessory = accessory; }
	item* getDrillItem(){ return _drillItem; }

	//�������߰�
	void pushBackItem(item* k){ _inventory.push_back(k); }

	//�̸� ��
	char* getName(){ return _name; }

	void playerSetting();			//�÷��̾� ��ǥ ���
	void setMaxHpMpCaseOver();			//ü�� ������ �ִ�ġ�� �Ѿ����
	void moveManagement();				//�̵� ���� ( �̵� ����ó�� ���⿡ �� ���� )
	void setDirection();				//���� ����
	void animaition();					//�̹��� �ִϸ��̼�
	void idleAni();						//���ִ� �ִϸ��̼�
	void walkAni();						//�ȴ� �ִϸ��̼�
	void attackAni();					//���� �ִϸ��̼�
	void attackIdleAni();				//���� ��� �ִϸ��̼�
	void drillAni();					//�帱 �ִϸ��̼�
	void specialAni();					//Ư�� �ִϸ��̼�
	
	void changeState(STATE state);		//���� ��ȯ

	//���콺 ���� �Լ�
	int setMouseCursorX();				//���콺 Ŀ��x
	int setMouseCursorY();				//���콺 Ŀ��y

	//��ų �ټ�
	bool getIsAllMiss(){ return _isAllMiss; }
	tagSkill getSkill(int i){ return _skill[i]; }
	bool getSkillIsGet(int i){ return _skill[i].isGet; }
	int getSkillLv(int i){ return _skill[i].lv; }
	void setSkillLv(int i, int k){ _skill[i].lv = k; }

	//��ȣ���� ��ũ
	void setMapManagerLink(mapManager* mm){ _mapManagerLink = mm; }
	void setUiManagerLink(uiManager* ui){ _uiManagerLink = ui; }
	void setEnemyManagerLink(enemyManager* en){ _enemyManagerLink = en; }

	//�ִϸ��̼� ����
	void aniRender();				//�ִϸ��̼� ���� ����
	void walkRender();				//�ȴ� �ִϸ��̼� ����
	void idleRender();				//���ִ� �ִϸ��̼� ����
	void attackIdleRender();		//���� ��� �ִϸ��̼� ����
	void attackRender();			//���� �ִϸ��̼� ����
	void drillRender();				//�帱 �ִϸ��̼� ����
	void barRender();				//ĳ���� �� ü��, ������ ����

	//���� �������� ����
	void move(int destX, int destY, int sourX, int sourY);

	//������ ���� �Լ�
	void itemUpdate(void);
	void itemEquip(void);
	void itemSpecUp(item* sour);
	void itemSpecDown(item* sour);
	void calculateWeight(void);

	//�帱���� �Լ�
	void drillUiRender(void);
	void drillFrameUpdate(void);
	void drillGaugeManagement(void);
	void drillGetItem(void);

	//lv��, tm ��
	void lvTmUp(void);
	void autoUp(void);

	//��ų ���� �Լ���
	void skillManagement(void);				//��ü�� ��ų ����
	void skillIconRender(int i);			//��ų ������ ���
	void skillEffectRender(void);			//��ų ����Ʈ ���
	void skillFraming(void);				//��ų ����Ʈ ������ ������
	void skill1CalculateHowLong(void);		//��ų 2 ���ӽð� ���
	void checkSkillCoolTime(void);			//��ų ��Ÿ�� ���
	void usingSkill(void);					//��ų ���
	void thunderShot(void);					//��ų3 �����
	void thunderRender(int x, int y);
	void thunderThunder(void);				//�������� �����������°� ����
	void skillMasterRender();
	void setIsSkillMasterOn(bool k){ _isSkillMasterOn = k; }
	void tmLvUpEffectRender(void);
	void skillLvUpEffectRender(void);

	void effectRender(void);

	//�������� �Լ�
	void attackManagement();
	int attackDamage(int k);
	RECT getAttackRC(){ return _attackRC; }
	bool getIsAttackOk(){ return _isAttackOk; }
	RECT getHitRC(){ return _hitRC; }
	bool getIsHit(){ return _isHit; }
	void damagePushBack(int damage, enemy* destEnemy, bool isCrit);
	void damageRender();

	//ġƮŰ
	void cheatKey();

	//��Ʈ�ѷ�
	void attackControl();
	void drillControl();

	//����� ��� ����
	void debugRender();

	//���� ���ʹ� ��
	enemy* getHitEnemy(){ return _hitEnemy; }

	void hitEnemyInfoRender(HDC hdc, int x, int y);
	bool isHitOn();

	player();
	~player();
};

