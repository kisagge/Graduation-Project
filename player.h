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
	int x, y;				//스킬 아이콘 좌표
	RECT rc;				//스킬 아이콘 렉트
	image* skillIcon;
	float skillCoolTime;
	int showX, showY;
	image* skillEffect;
	bool isGet;
	float frameCount;
	bool isPlay;
	bool isCool;			//쿨타임이냐
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
	//렉트들
	RECT _imageRc;
	RECT _moveRC;

	//플레이어 정보 (1)
	float _x, _y;				//플레이어 좌표
	int _speed;					//플리에어 이동속도
	float _angle;				//플레이어 각도
	int _hp, _mp;				//플레이어 hp, mp
	int _maxHp, _maxMp;			//플레이어 maxHp, maxMp

	int _imageX, _imageY;		//이미지 출력 x,y

	STATE _state;				//플레이어 상태

	float _startX, _startY;		//플레이어 이동 시작x,y
	float _endX, _endY;			//플레이어 이동 도착x,y

	//플레이어 이미지 프레임 카운트
	float _frameCount;
	float _walkFrameCount;
	float _attackFrameCount;
	float _hitFrameCount;
	float _anoDrillFrameCount = 0.0f;
	float _specialTime;			//특수행동 시간 계산
	float _attackIdleCount = 0.0f;

	int _lv;					//레벨
	int _lvExp, _maxLvExp;		//레벨 경험치, 맥스경험치
	int _tm;					//tm
	int _tmExp, _maxTmExp;		//tm 경험치, 맥스 경험치
	bool _fightOrNot;			//전투상태냐 아니냐

	//상호참조 변수들
	mapManager* _mapManagerLink;
	uiManager* _uiManagerLink;
	enemyManager* _enemyManagerLink;

	//이미지들
	image* _idle;
	image* _walk[8];
	image* _specialImg;
	image* _attackIdle[4];
	image* _attack[4];
	image* _drilling;
	image* _drill;
	image* _hitImage;

	int _direction;				//방향 ( 각도에 따라 바뀜 )

	image* _hpMinibar;			//플레이어 하단 체력표시 미니바
	image* _mpMinibar;			//플레이어 하단 마나표시 미니바

	int _money;					//돈

	//플레이어 고유스탯
	int _ap;				//공격력
	float _ac;				//공격속도
	int _dx;				//명중률	
	int _wt;				//무게
	int _da;				//드릴 성공률
	int _lk;				//크리티컬
	int _dp;				//방어력
	int _hv;				//회피율

	char*_name = "GoldenSpoon";

	int _nowWeight;			//현재 무게
	int _maxWeight;			//최대 무게

	int _bonusStat;			//보너스 스탯
	int _skillPoint;		//스킬포인트

	vector<item*> _inventory;	//인벤토리
	int _maxSize = 18;			//인벤토리 맥스 사이즈
	
	item* _helmet;			//헬멧
	item* _shield;			//방패
	item* _weapon;			//무기
	item* _accessory;		//악세서리
	item* _drillItem;		//드릴

	//드릴 관련 UI
	image* _drillUi;
	image* _drillGear[3];
	image* _drillGauge;
	float _drillFrameCount = 0.0f;
	int _maxDrillGauge;
	int _curDrillGauge;
	float _drBtnDelay = 0.0f;
	float _drillingGetItemCount = 0.0f;

	//체력 마나, 자연 회복
	float _autoUpCount = 0.0f;

	//스킬 아이콘
	tagSkill _skill[3];
	float _skill1FrameCount = 0.0f;
	float _skill3FrameCount = 0.0f;
	image* _skill3This;

	//특수 버프
	bool _isAllMiss = false;		//완전 회피냐

	//카운터 버프
	bool _isCounter = false;		//카운터 상태냐
	bool _isThunder = false;
	float _thunderCount = 0.0f;

	//전투관련 변수들
	RECT _attackRC;					//공격 가격 렉트
	bool _isAttackOk;				//한 번 가격 성공하면 데미지 더이상 안들어가게 하는 변수
	RECT _hitRC;
	bool _isHit;

	//어디 맵이냐
	int _whatMap;

	//때린 몬스터 잠시 저장
	enemy* _hitEnemy = NULL;

	image* _enemyBack = IMAGEMANAGER->findImage("몬스터정보표시");
	image* _enemyBar = IMAGEMANAGER->findImage("몬스터체력표시바");

	//데미지 스킨 정보 담는 벡터
	vector<tagDamageSkin> _vDamageSkin;

	//스킬 마스터 이펙트
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

	//기본 겟셋
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
	int getLvExp(){ return _lvExp; }			//현재 경험치
	void setLvExp(int k){ _lvExp = k; }
	int getTmExp(){ return _tmExp; }
	void setTmExp(int k){ _tmExp = k; }
	int getMaxLvExp(){ return _maxLvExp; }		//맥스 경험치
	int getMaxTmExp(){ return _maxTmExp; }
	STATE getState(){ return _state; }
	void setState(STATE state){ _state = state; }
	int getLv(){ return _lv; }					//레벨 겟셋
	void setLv(int lv){ _lv = lv; }
	int getTm(){ return _tm; }					//tm 겟셋
	void setTm(int tm){ _tm = tm; }

	int getWhatMap(){ return _whatMap; }
	//돈, 무게 겟셋
	int getMoney(){ return _money; }
	void setMoney(int money){ _money = money; }
	int getWeight(){ return _nowWeight; }
	int getMaxWeight(){ return _maxWeight; }

	//스탯 겟셋
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

	//인벤토리 관련 겟셋
	int getInvenMaxSize(){ return _maxSize; }
	vector<item*> getInven(){ return _inventory; }
	int getInventorySize(){ return _inventory.size(); }
	item* getInvenItem(int i){ return _inventory.at(i); }
	void eraseItem(int i){ _inventory.erase(_inventory.begin() + i); }

	//아이템 겟셋
	item* getHelmet(){ return _helmet; }
	void setHelmet(item* helmet){ _helmet = helmet; }
	item* getWeapon(){ return _weapon; }
	void setWeapon(item* weapon){ _weapon = weapon; }
	item* getShield(){ return _shield; }
	void setShield(item* shield){ _shield = shield; }
	item* getAccessory(){ return _accessory; }
	void setAccessory(item* accessory){ _accessory = accessory; }
	item* getDrillItem(){ return _drillItem; }

	//아이템추가
	void pushBackItem(item* k){ _inventory.push_back(k); }

	//이름 겟
	char* getName(){ return _name; }

	void playerSetting();			//플레이어 좌표 잡기
	void setMaxHpMpCaseOver();			//체력 마나가 최대치를 넘어갔을때
	void moveManagement();				//이동 관리 ( 이동 예외처리 여기에 다 있음 )
	void setDirection();				//방향 설정
	void animaition();					//이미지 애니메이션
	void idleAni();						//서있는 애니메이션
	void walkAni();						//걷는 애니메이션
	void attackAni();					//공격 애니메이션
	void attackIdleAni();				//공격 대기 애니메이션
	void drillAni();					//드릴 애니메이션
	void specialAni();					//특수 애니메이션
	
	void changeState(STATE state);		//상태 변환

	//마우스 관련 함수
	int setMouseCursorX();				//마우스 커서x
	int setMouseCursorY();				//마우스 커서y

	//스킬 겟셋
	bool getIsAllMiss(){ return _isAllMiss; }
	tagSkill getSkill(int i){ return _skill[i]; }
	bool getSkillIsGet(int i){ return _skill[i].isGet; }
	int getSkillLv(int i){ return _skill[i].lv; }
	void setSkillLv(int i, int k){ _skill[i].lv = k; }

	//상호참조 링크
	void setMapManagerLink(mapManager* mm){ _mapManagerLink = mm; }
	void setUiManagerLink(uiManager* ui){ _uiManagerLink = ui; }
	void setEnemyManagerLink(enemyManager* en){ _enemyManagerLink = en; }

	//애니메이션 렌더
	void aniRender();				//애니메이션 종합 렌더
	void walkRender();				//걷는 애니메이션 렌더
	void idleRender();				//서있는 애니메이션 렌더
	void attackIdleRender();		//공격 대기 애니메이션 렌더
	void attackRender();			//공격 애니메이션 렌더
	void drillRender();				//드릴 애니메이션 렌더
	void barRender();				//캐릭터 밑 체력, 마나바 렌더

	//찍은 방향으로 무브
	void move(int destX, int destY, int sourX, int sourY);

	//아이템 관련 함수
	void itemUpdate(void);
	void itemEquip(void);
	void itemSpecUp(item* sour);
	void itemSpecDown(item* sour);
	void calculateWeight(void);

	//드릴관련 함수
	void drillUiRender(void);
	void drillFrameUpdate(void);
	void drillGaugeManagement(void);
	void drillGetItem(void);

	//lv업, tm 업
	void lvTmUp(void);
	void autoUp(void);

	//스킬 관련 함수들
	void skillManagement(void);				//전체적 스킬 관리
	void skillIconRender(int i);			//스킬 아이콘 출력
	void skillEffectRender(void);			//스킬 이펙트 출력
	void skillFraming(void);				//스킬 이펙트 프레임 돌리기
	void skill1CalculateHowLong(void);		//스킬 2 지속시간 계산
	void checkSkillCoolTime(void);			//스킬 쿨타임 계산
	void usingSkill(void);					//스킬 사용
	void thunderShot(void);					//스킬3 사용잼
	void thunderRender(int x, int y);
	void thunderThunder(void);				//몬스터한테 벼락떨어지는거 렌더
	void skillMasterRender();
	void setIsSkillMasterOn(bool k){ _isSkillMasterOn = k; }
	void tmLvUpEffectRender(void);
	void skillLvUpEffectRender(void);

	void effectRender(void);

	//전투관련 함수
	void attackManagement();
	int attackDamage(int k);
	RECT getAttackRC(){ return _attackRC; }
	bool getIsAttackOk(){ return _isAttackOk; }
	RECT getHitRC(){ return _hitRC; }
	bool getIsHit(){ return _isHit; }
	void damagePushBack(int damage, enemy* destEnemy, bool isCrit);
	void damageRender();

	//치트키
	void cheatKey();

	//컨트롤러
	void attackControl();
	void drillControl();

	//디버그 모드 렌더
	void debugRender();

	//때린 에너미 겟
	enemy* getHitEnemy(){ return _hitEnemy; }

	void hitEnemyInfoRender(HDC hdc, int x, int y);
	bool isHitOn();

	player();
	~player();
};

