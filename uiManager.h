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

	tagBar _hpBar;						//ü�� ��
	tagBar _mpBar;						//���� ��
	tagBar _expBar;						//lv����ġ��
	tagBar _tmBar;						//tm����ġ��

	int whe;							//�� ����

	tagMenuButton _menuButton[8];		//���� �ϴ� �޴���ư 8��

	image* _menuBar;					//���� �ϴܤ� �޴���
	bool _menuBarOnOff;					//���� �ϴ� �޴��� ����orŬ����

	tagWindow _equipWindow;				//���â
	tagWindow _itemWindow;				//������â
	tagWindow _myViewWindow;			//����â
	tagWindow _skillWindow;				//��ųâ

	//���� Ȱ��ȭâ
	tagWindow* _activatedWindow;
	
	vector<tagWindow*> _vWindows;

	//���̺� ���� �Լ�
	int _myViewFrame;
	RECT _myViewChangeButton[2];

	//����
	shop* _shop;

	//���ȿø���
	RECT _statsRect[10];
	float _statBtnDelay = 0.0f;

	//��ų ������
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

	//���� ����
	void statUp(void);

	//��ų����
	void skillLvUp(void);
	void skillQuickSlotManagement(void);
	void skillQuickSlotRender(void);
	int getSkillQx(){ return _skillQx; }
	int getSkillQy(){ return _skillQy; }


	bool getEquipWindowIsOpen(){ return _equipWindow.isOpen; }
	bool getItemWindowIsOpen(){ return _itemWindow.isOpen; }
	bool getMyViewWindowIsOpen(){ return _myViewWindow.isOpen; }
	bool getSkillWindowIsOpen(){ return _skillWindow.isOpen; }

	//���� ����

	void setPlayerManagerLink(playerManager* k){ _playerManagerLink = k; }
	void setNpcManagerLink(npcManager* k){ _npcManagerLink = k; }
	void setMapManagerLink(mapManager* k){ _mapManagerLink = k; }

	void clickSound()
	{
		if (SOUNDMANAGER->isPlaySound("âŬ��1"))
		{
			SOUNDMANAGER->stop("âŬ��1");
			SOUNDMANAGER->play("âŬ��1", 0.5f);
		}
		else SOUNDMANAGER->play("âŬ��1", 0.5f);
	}

	uiManager();
	~uiManager();
};

