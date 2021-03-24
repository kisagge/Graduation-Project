#pragma once
#include "gameNode.h"
#include "shop.h"

#define UISTARTX 10
#define UISTARTY 50

#define WINDOWINITX 300
#define WINDOWINITY 300

class playerManager;
class npcManager;
class mapManager;

struct tagBar
{
	image* gauge;
	image* maxGauge;
	image* showtext;
};

struct tagWindow
{
	int x, y;
	image* windowOpenImage;
	RECT windowOpenRect;
	image* exitImage;
	RECT exitRect;
	int exitFrame;
	bool isOpen;
};

struct tagMenuButton
{
	image* aboveButton;
	RECT aboveButtonRect;
	int aboveBX, aboveBY;
	image* belowButton;
	RECT belowButtonRect;
	int belowBX, belowBY;
	RECT menuRect;
	image* menuBg;
};

class uiManager : public gameNode
{
private:
	playerManager* _playerManagerLink;
	npcManager* _npcManagerLink;
	mapManager* _mapManagerLink;

	tagBar _hpBar;						//체력 바
	tagBar _mpBar;						//마나 바
	tagBar _expBar;						//lv경험치바
	tagBar _tmBar;						//tm경험치바

	int whe;							//걍 변수

	tagMenuButton _menuButton[8];		//우측 하단 메뉴버튼 8개

	image* _menuBar;					//우측 하단ㄷ 메뉴바
	bool _menuBarOnOff;					//우측 하단 메뉴바 오픈or클로즈

	tagWindow _equipWindow;				//장비창
	tagWindow _itemWindow;				//아이템창
	tagWindow _myViewWindow;			//스탯창
	tagWindow _skillWindow;				//스킬창

	//현재 활성화창
	tagWindow* _activatedWindow;
	
	vector<tagWindow*> _vWindows;

	//마이뷰 관련 함수
	int _myViewFrame;
	RECT _myViewChangeButton[2];

	//상점
	shop* _shop;

	//스탯올리기
	RECT _statsRect[10];
	float _statBtnDelay = 0.0f;

	//스킬 퀵슬롯
	int _skillQx, _skillQy;
	image* _skillQWindow;
	RECT _skillQRC;

	float _menuBtnDelay = 0.0f;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void fontImageRender(image* fontImage, int value, int x, int y);
	void menuMouseOver(void);
	void windowManagement(void);
	void windowRender(void);
	void moveWindow(void);

	void shopOpenOrNot(void);

	RECT getMenuRect(int i){ return _menuButton[i].menuRect; }
	vector<tagWindow*> getWindows(){ return _vWindows; }

	shop* getShop(){ return _shop; }
	void setPlayerItemLocation(void);
	void playerEquipItemRender(void);
	void playerInvenItemRender(void);

	//스탯 관련
	void statUp(void);

	//스킬관련
	void skillLvUp(void);
	void skillQuickSlotManagement(void);
	void skillQuickSlotRender(void);
	int getSkillQx(){ return _skillQx; }
	int getSkillQy(){ return _skillQy; }


	bool getEquipWindowIsOpen(){ return _equipWindow.isOpen; }
	bool getItemWindowIsOpen(){ return _itemWindow.isOpen; }
	bool getMyViewWindowIsOpen(){ return _myViewWindow.isOpen; }
	bool getSkillWindowIsOpen(){ return _skillWindow.isOpen; }

	//몬스터 관련

	void setPlayerManagerLink(playerManager* k){ _playerManagerLink = k; }
	void setNpcManagerLink(npcManager* k){ _npcManagerLink = k; }
	void setMapManagerLink(mapManager* k){ _mapManagerLink = k; }

	void clickSound()
	{
		if (SOUNDMANAGER->isPlaySound("창클릭1"))
		{
			SOUNDMANAGER->stop("창클릭1");
			SOUNDMANAGER->play("창클릭1", 0.5f);
		}
		else SOUNDMANAGER->play("창클릭1", 0.5f);
	}

	uiManager();
	~uiManager();
};

