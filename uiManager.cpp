#include "stdafx.h"
#include "uiManager.h"
#include "playerManager.h"
#include "npcManager.h"
#include "mapManager.h"
uiManager::uiManager()
{
}


uiManager::~uiManager()
{
}

HRESULT uiManager::init(void)
{
	_hpBar.gauge = IMAGEMANAGER->addImage("체력바", "images/character/hpBar.bmp", 278, 20);
	_hpBar.maxGauge = IMAGEMANAGER->addImage("맥스체력바", "images/character/hpBarUi.bmp", 282, 28, true, RGB(255, 0, 255));
	_hpBar.showtext = IMAGEMANAGER->addImage("체력글씨", "images/character/hpBarChar.bmp", 36, 16, true, RGB(255, 0, 255));

	_mpBar.gauge = IMAGEMANAGER->addImage("마나바", "images/character/mpBar.bmp", 278, 20);
	_mpBar.maxGauge = IMAGEMANAGER->addImage("맥스마나바", "images/character/mpBarUi.bmp", 282, 28, true, RGB(255, 0, 255));
	_mpBar.showtext = IMAGEMANAGER->addImage("마나글씨", "images/character/mpBarChar.bmp", 36, 16, true, RGB(255, 0, 255));
	
	_expBar.gauge = IMAGEMANAGER->addImage("레벨경험치바", "images/ui/lvExpBar.bmp", 396, 11);
	_expBar.maxGauge = IMAGEMANAGER->addImage("경험치테두리", "images/ui/maxExpBar.bmp", 398, 16, true, RGB(255, 0, 255));
	_expBar.showtext = IMAGEMANAGER->addImage("레벨텍스트", "images/ui/lvText.bmp", 34, 24, true, RGB(255, 0, 255));

	_tmBar.gauge = IMAGEMANAGER->addImage("tm경험치바", "images/ui/tmExpBar.bmp", 396, 5);
	_tmBar.showtext = IMAGEMANAGER->addImage("tm텍스트", "images/ui/tmText.bmp", 34, 18, true, RGB(255, 0, 255));

	_menuBar = IMAGEMANAGER->findImage("메뉴바");

	IMAGEMANAGER->addImage("tmBar2", "images/ui/tmBar2.bmp", 121, 7);

	_menuButton[0].aboveButton = IMAGEMANAGER->findImage("스킬윗버튼");
	_menuButton[0].aboveBX = WINSIZEX - _menuBar->getWidth() + 5;
	_menuButton[0].aboveBY = WINSIZEY - _menuButton[0].aboveButton->getHeight() - 3;
	_menuButton[0].aboveButtonRect = RectMake(_menuButton[0].aboveBX, _menuButton[0].aboveBY,
		_menuButton[0].aboveButton->getWidth(), _menuButton[0].aboveButton->getHeight());
	_menuButton[0].belowButton = IMAGEMANAGER->findImage("스킬아이콘");
	_menuButton[0].belowBX = _menuButton[0].aboveBX;
	_menuButton[0].belowBY = _menuButton[0].aboveButtonRect.bottom;
	_menuButton[0].belowButtonRect = RectMake(_menuButton[0].belowBX, _menuButton[0].belowBY,
		_menuButton[0].belowButton->getWidth(), _menuButton[0].belowButton->getHeight());
	_menuButton[0].menuBg = IMAGEMANAGER->findImage("메뉴버튼배경");

	_menuButton[1].aboveButton = IMAGEMANAGER->findImage("카드윗버튼");
	_menuButton[1].aboveBX = WINSIZEX - _menuBar->getWidth() + 42 * 1+ 5;
	_menuButton[1].aboveBY = WINSIZEY - _menuButton[1].aboveButton->getHeight() - 3;
	_menuButton[1].aboveButtonRect = RectMake(_menuButton[1].aboveBX, _menuButton[1].aboveBY,
		_menuButton[1].aboveButton->getWidth(), _menuButton[1].aboveButton->getHeight());
	_menuButton[1].belowButton = IMAGEMANAGER->findImage("카드아이콘");
	_menuButton[1].belowBX = _menuButton[1].aboveBX;
	_menuButton[1].belowBY = _menuButton[1].aboveButtonRect.bottom;
	_menuButton[1].belowButtonRect = RectMake(_menuButton[1].belowBX, _menuButton[1].belowBY,
		_menuButton[1].belowButton->getWidth(), _menuButton[1].belowButton->getHeight());
	_menuButton[1].menuBg = IMAGEMANAGER->findImage("메뉴버튼배경");

	_menuButton[2].aboveButton = IMAGEMANAGER->findImage("아이템윗버튼");
	_menuButton[2].aboveBX = WINSIZEX - _menuBar->getWidth() + 42 * 2 + 5;
	_menuButton[2].aboveBY = WINSIZEY - _menuButton[2].aboveButton->getHeight() - 3;
	_menuButton[2].aboveButtonRect = RectMake(_menuButton[2].aboveBX, _menuButton[2].aboveBY,
		_menuButton[2].aboveButton->getWidth(), _menuButton[2].aboveButton->getHeight());
	_menuButton[2].belowButton = IMAGEMANAGER->findImage("아이템아이콘");
	_menuButton[2].belowBX = _menuButton[2].aboveBX;
	_menuButton[2].belowBY = _menuButton[2].aboveButtonRect.bottom;
	_menuButton[2].belowButtonRect = RectMake(_menuButton[2].belowBX, _menuButton[2].belowBY,
		_menuButton[2].belowButton->getWidth(), _menuButton[2].belowButton->getHeight());
	_menuButton[2].menuBg = IMAGEMANAGER->findImage("메뉴버튼배경");

	_menuButton[3].aboveButton = IMAGEMANAGER->findImage("장비윗버튼");
	_menuButton[3].aboveBX = WINSIZEX - _menuBar->getWidth() + 42 * 3 + 5;
	_menuButton[3].aboveBY = WINSIZEY - _menuButton[3].aboveButton->getHeight() - 3;
	_menuButton[3].aboveButtonRect = RectMake(_menuButton[3].aboveBX, _menuButton[3].aboveBY,
		_menuButton[3].aboveButton->getWidth(), _menuButton[3].aboveButton->getHeight());
	_menuButton[3].belowButton = IMAGEMANAGER->findImage("장비아이콘");
	_menuButton[3].belowBX = _menuButton[3].aboveBX;
	_menuButton[3].belowBY = _menuButton[3].aboveButtonRect.bottom;
	_menuButton[3].belowButtonRect = RectMake(_menuButton[3].belowBX, _menuButton[3].belowBY,
		_menuButton[3].belowButton->getWidth(), _menuButton[3].belowButton->getHeight());
	_menuButton[3].menuBg = IMAGEMANAGER->findImage("메뉴버튼배경");

	_menuButton[4].aboveButton = IMAGEMANAGER->findImage("정보윗버튼");
	_menuButton[4].aboveBX = WINSIZEX - _menuBar->getWidth() + 42 * 4 + 5;
	_menuButton[4].aboveBY = WINSIZEY - _menuButton[4].aboveButton->getHeight() - 3;
	_menuButton[4].aboveButtonRect = RectMake(_menuButton[4].aboveBX, _menuButton[4].aboveBY,
		_menuButton[4].aboveButton->getWidth(), _menuButton[4].aboveButton->getHeight());
	_menuButton[4].belowButton = IMAGEMANAGER->findImage("정보아이콘");
	_menuButton[4].belowBX = _menuButton[4].aboveBX;
	_menuButton[4].belowBY = _menuButton[4].aboveButtonRect.bottom;
	_menuButton[4].belowButtonRect = RectMake(_menuButton[4].belowBX, _menuButton[4].belowBY,
		_menuButton[4].belowButton->getWidth(), _menuButton[4].belowButton->getHeight());
	_menuButton[4].menuBg = IMAGEMANAGER->findImage("메뉴버튼배경");

	_menuButton[5].aboveButton = IMAGEMANAGER->findImage("퀘스트윗버튼");
	_menuButton[5].aboveBX = WINSIZEX - _menuBar->getWidth() + 42 * 5 + 5;
	_menuButton[5].aboveBY = WINSIZEY - _menuButton[5].aboveButton->getHeight() - 3;
	_menuButton[5].aboveButtonRect = RectMake(_menuButton[5].aboveBX, _menuButton[5].aboveBY,
		_menuButton[5].aboveButton->getWidth(), _menuButton[5].aboveButton->getHeight());
	_menuButton[5].belowButton = IMAGEMANAGER->findImage("퀘스트아이콘");
	_menuButton[5].belowBX = _menuButton[5].aboveBX;
	_menuButton[5].belowBY = _menuButton[5].aboveButtonRect.bottom;
	_menuButton[5].belowButtonRect = RectMake(_menuButton[5].belowBX, _menuButton[5].belowBY,
		_menuButton[5].belowButton->getWidth(), _menuButton[5].belowButton->getHeight());
	_menuButton[5].menuBg = IMAGEMANAGER->findImage("메뉴버튼배경");

	_menuButton[6].aboveButton = IMAGEMANAGER->findImage("길드윗버튼");
	_menuButton[6].aboveBX = WINSIZEX - _menuBar->getWidth() + 42 * 6 + 5;
	_menuButton[6].aboveBY = WINSIZEY - _menuButton[6].aboveButton->getHeight() - 3;
	_menuButton[6].aboveButtonRect = RectMake(_menuButton[6].aboveBX, _menuButton[6].aboveBY,
		_menuButton[6].aboveButton->getWidth(), _menuButton[6].aboveButton->getHeight());
	_menuButton[6].belowButton = IMAGEMANAGER->findImage("길드아이콘");
	_menuButton[6].belowBX = _menuButton[6].aboveBX;
	_menuButton[6].belowBY = _menuButton[6].aboveButtonRect.bottom;
	_menuButton[6].belowButtonRect = RectMake(_menuButton[6].belowBX, _menuButton[6].belowBY,
		_menuButton[6].belowButton->getWidth(), _menuButton[6].belowButton->getHeight());
	_menuButton[6].menuBg = IMAGEMANAGER->findImage("메뉴버튼배경");

	_menuButton[7].aboveButton = IMAGEMANAGER->findImage("친구윗버튼");
	_menuButton[7].aboveBX = WINSIZEX - _menuBar->getWidth() + 42 * 7 + 5;
	_menuButton[7].aboveBY = WINSIZEY - _menuButton[7].aboveButton->getHeight() - 3;
	_menuButton[7].aboveButtonRect = RectMake(_menuButton[7].aboveBX, _menuButton[7].aboveBY,
		_menuButton[7].aboveButton->getWidth(), _menuButton[7].aboveButton->getHeight());
	_menuButton[7].belowButton = IMAGEMANAGER->findImage("친구아이콘");
	_menuButton[7].belowBX = _menuButton[7].aboveBX;
	_menuButton[7].belowBY = _menuButton[7].aboveButtonRect.bottom;
	_menuButton[7].belowButtonRect = RectMake(_menuButton[7].belowBX, _menuButton[7].belowBY,
		_menuButton[7].belowButton->getWidth(), _menuButton[7].belowButton->getHeight());
	_menuButton[7].menuBg = IMAGEMANAGER->findImage("메뉴버튼배경");

	//장비창 추가
	_equipWindow.windowOpenImage = IMAGEMANAGER->addImage("장비창오픈", "images/ui/equipWindow.bmp", 190, 301, true, RGB(255, 0, 255));
	_equipWindow.x = WINDOWINITX;
	_equipWindow.y = WINDOWINITY;
	_equipWindow.windowOpenRect = RectMake(_equipWindow.x, _equipWindow.y, _equipWindow.windowOpenImage->getWidth(),
		_equipWindow.windowOpenImage->getHeight());
	_equipWindow.exitImage = IMAGEMANAGER->addFrameImage("창끄기", "images/ui/windowExit.bmp", 18, 54, 1, 3, true, RGB(255, 0, 255));
	_equipWindow.exitRect = RectMake(_equipWindow.x + 164, _equipWindow.y + 4, 
		_equipWindow.exitImage->getFrameWidth(), _equipWindow.exitImage->getFrameHeight());
	_equipWindow.exitFrame = 0;
	_equipWindow.isOpen = false;
	_vWindows.push_back(&_equipWindow);

	//아이템 창 추가
	_itemWindow.windowOpenImage = IMAGEMANAGER->addImage("아이템창오픈", "images/ui/itemWindow.bmp", 244, 178, true, RGB(255, 0, 255));
	_itemWindow.x = WINDOWINITX;
	_itemWindow.y = WINDOWINITY;
	_itemWindow.windowOpenRect = RectMake(_itemWindow.x, _itemWindow.y, _itemWindow.windowOpenImage->getWidth(), _itemWindow.windowOpenImage->getHeight());
	_itemWindow.exitImage = IMAGEMANAGER->findImage("창끄기");
	_itemWindow.exitRect = RectMake(_itemWindow.x + 218, _itemWindow.y + 4, _itemWindow.exitImage->getFrameWidth(), _itemWindow.exitImage->getFrameHeight());
	_itemWindow.exitFrame = 0;
	_itemWindow.isOpen = false;
	_vWindows.push_back(&_itemWindow);

	//스킬 창 추가
	_skillWindow.windowOpenImage = IMAGEMANAGER->addImage("스킬창오픈", "images/ui/skillWindow.bmp", 351, 322, true, RGB(255, 0, 255));
	_skillWindow.x = WINDOWINITX;
	_skillWindow.y = WINDOWINITY;
	_skillWindow.windowOpenRect = RectMake(_skillWindow.x, _skillWindow.y, _skillWindow.windowOpenImage->getWidth(), _skillWindow.windowOpenImage->getHeight());
	_skillWindow.exitImage = IMAGEMANAGER->findImage("창끄기");
	_skillWindow.exitRect = RectMake(_skillWindow.x + 325, _skillWindow.y + 4, _skillWindow.exitImage->getFrameWidth(), _skillWindow.exitImage->getFrameHeight());
	_skillWindow.exitFrame = 0;
	_skillWindow.isOpen = false;
	_vWindows.push_back(&_skillWindow);

	//스탯창 추가
	_myViewWindow.windowOpenImage = IMAGEMANAGER->addFrameImage("스탯창오픈", "images/ui/myviewWindow.bmp", 443, 886, 1, 2, true, RGB(255, 0, 255));
	_myViewWindow.x = WINDOWINITX;
	_myViewWindow.y = WINDOWINITY;
	_myViewWindow.windowOpenRect = RectMake(_myViewWindow.x, _myViewWindow.y, _myViewWindow.windowOpenImage->getFrameWidth(), _myViewWindow.windowOpenImage->getFrameHeight());
	_myViewWindow.exitImage = IMAGEMANAGER->findImage("창끄기");
	_myViewWindow.exitRect = RectMake(_myViewWindow.x + 410, _myViewWindow.y + 4, _myViewWindow.exitImage->getFrameWidth(), _myViewWindow.exitImage->getFrameHeight());
	_myViewWindow.exitFrame = 0;
	_myViewWindow.isOpen = false;
	_myViewFrame = 0;
	_myViewChangeButton[0] = RectMake(_myViewWindow.x + 46, _myViewWindow.y + 24, 61, 19);
	_myViewChangeButton[1] = RectMake(_myViewWindow.x + 106, _myViewWindow.y + 24, 61, 19);
	_vWindows.push_back(&_myViewWindow);

	//상점
	_shop = new shop;
	_shop->init();

	_skillQWindow = IMAGEMANAGER->findImage("스킬퀵슬롯");
	_skillQx = 50;
	_skillQy = WINSIZEY - 50;
	

	return S_OK;
}

void uiManager::release(void)
{
	_vWindows.clear();

	_shop->release();
	SAFE_DELETE(_shop);
}

void uiManager::update(void)
{
	for (int i = 0; i < 8; i++)
	{
		_menuButton[i].belowBX = _menuButton[i].aboveBX;
		_menuButton[i].belowBY = _menuButton[i].aboveButtonRect.bottom;
		_menuButton[i].aboveButtonRect = RectMake(_menuButton[i].aboveBX, _menuButton[i].aboveBY,
			_menuButton[i].aboveButton->getWidth(), _menuButton[i].aboveButton->getHeight());
		_menuButton[i].belowButtonRect = RectMake(_menuButton[i].belowBX, _menuButton[i].belowBY,
			_menuButton[i].belowButton->getWidth(), _menuButton[i].belowButton->getHeight());
		_menuButton[i].menuRect = RectMake(_menuButton[i].aboveBX, _menuButton[i].aboveBY,
			_menuButton[i].aboveButton->getWidth(), _menuButton[i].aboveButton->getHeight() + _menuButton[i].belowButton->getHeight() + 50);
	}

	windowManagement();
	menuMouseOver();
	moveWindow();

	shopOpenOrNot();
	_shop->update();

	setPlayerItemLocation();

	statUp();

	skillQuickSlotManagement();
	skillLvUp();
}

void uiManager::render(void)
{
	//hp바 출력
	_hpBar.gauge->render(getCameraDC(), UISTARTX + 2, UISTARTY + 2, 0, 0,
		_hpBar.gauge->getWidth() * _playerManagerLink->getPlayer()->getHp() / _playerManagerLink->getPlayer()->getMaxHp(), _hpBar.gauge->getHeight());
	_hpBar.maxGauge->render(getCameraDC(), UISTARTX, UISTARTY);
	_hpBar.showtext->render(getCameraDC(), UISTARTX, UISTARTY - 6);
	fontImageRender(IMAGEMANAGER->findImage("폰트1"), _playerManagerLink->getPlayer()->getMaxHp(), UISTARTX + _hpBar.maxGauge->getWidth() - 20, UISTARTY - 6);
	IMAGEMANAGER->findImage("폰트1")->frameRender(getCameraDC(), UISTARTX + _hpBar.maxGauge->getWidth() - 85, UISTARTY - 6, 10, 1);
	fontImageRender(IMAGEMANAGER->findImage("폰트1"), _playerManagerLink->getPlayer()->getHp(), UISTARTX + _hpBar.maxGauge->getWidth() - 110, UISTARTY - 6);

	//mp바 출력
	_mpBar.gauge->render(getCameraDC(), UISTARTX + 2, UISTARTY + 40, 0, 0,
		_mpBar.gauge->getWidth() * _playerManagerLink->getPlayer()->getMp() / _playerManagerLink->getPlayer()->getMaxMp(), _mpBar.gauge->getHeight());
	_mpBar.maxGauge->render(getCameraDC(), UISTARTX, UISTARTY + 38);
	_mpBar.showtext->render(getCameraDC(), UISTARTX, UISTARTY + 32);
	fontImageRender(IMAGEMANAGER->findImage("폰트1"), _playerManagerLink->getPlayer()->getMaxMp(), UISTARTX + _mpBar.maxGauge->getWidth() - 20, UISTARTY + 32);
	IMAGEMANAGER->findImage("폰트1")->frameRender(getCameraDC(), UISTARTX + _hpBar.maxGauge->getWidth() - 85, UISTARTY + 32, 10, 1);
	fontImageRender(IMAGEMANAGER->findImage("폰트1"), _playerManagerLink->getPlayer()->getMp(), UISTARTX + _mpBar.maxGauge->getWidth() - 110, UISTARTY + 32);
	
	//경험치(lv)바, tm바 출력
	_expBar.gauge->render(getCameraDC(), UISTARTX + 1, UISTARTY - 25, 0, 0,
		_expBar.gauge->getWidth() * _playerManagerLink->getPlayer()->getLvExp() / _playerManagerLink->getPlayer()->getMaxLvExp(), _expBar.gauge->getHeight());
	_tmBar.gauge->render(getCameraDC(), UISTARTX + 1, UISTARTY - 17, 0, 0,
		_tmBar.gauge->getWidth() * _playerManagerLink->getPlayer()->getTmExp() / _playerManagerLink->getPlayer()->getMaxTmExp(), _tmBar.gauge->getHeight());
	_expBar.maxGauge->render(getCameraDC(), UISTARTX, UISTARTY - 26);
	_expBar.showtext->render(getCameraDC(), UISTARTX, UISTARTY - 42);
	_tmBar.showtext->render(getCameraDC(), UISTARTX + 130, UISTARTY - 39);
	fontImageRender(IMAGEMANAGER->findImage("폰트2"), _playerManagerLink->getPlayer()->getLv(), UISTARTX + 80, UISTARTY - 42);
	fontImageRender(IMAGEMANAGER->findImage("폰트3"), _playerManagerLink->getPlayer()->getTm(), UISTARTX + 190, UISTARTY - 39);
	fontImageRender(IMAGEMANAGER->findImage("폰트1"), (int)(_playerManagerLink->getPlayer()->getLvExp() / (float)_playerManagerLink->getPlayer()->getMaxLvExp() * 100), UISTARTX + 355, UISTARTY - 32);
	IMAGEMANAGER->findImage("폰트1")->frameRender(getCameraDC(), UISTARTX + 380, UISTARTY - 32, 11, 1);
	fontImageRender(IMAGEMANAGER->findImage("폰트1"), (int)(_playerManagerLink->getPlayer()->getTmExp() / (float)_playerManagerLink->getPlayer()->getMaxTmExp() * 100), UISTARTX + 355, UISTARTY - 18);
	IMAGEMANAGER->findImage("폰트1")->frameRender(getCameraDC(), UISTARTX + 380, UISTARTY - 18, 11, 1);

	//창들
	windowRender();

	//기타 표시
	IMAGEMANAGER->findImage("돈표시")->render(getCameraDC(), UISTARTX, UISTARTY + 73);
	fontImageRender(IMAGEMANAGER->findImage("폰트1"), _playerManagerLink->getPlayer()->getMoney(), UISTARTX + 90, UISTARTY + 70);
	IMAGEMANAGER->findImage("무게표시")->render(getCameraDC(), UISTARTX + 120, UISTARTY + 71);
	fontImageRender(IMAGEMANAGER->findImage("폰트1"), (int)(_playerManagerLink->getPlayer()->getWeight() / (float)_playerManagerLink->getPlayer()->getMaxWeight() * 100)
		, UISTARTX + 155, UISTARTY + 70);
	IMAGEMANAGER->findImage("폰트1")->frameRender(getCameraDC(), UISTARTX + 170, UISTARTY + 70, 11, 0);

	//메뉴 배경바 출력
	_menuBar->render(getCameraDC(), WINSIZEX - _menuBar->getWidth(), WINSIZEY - _menuBar->getHeight() - 1);
	_menuBarOnOff = true;

	//메뉴 각가 바 출력
	for (int i = 0; i < 8; i++)
	{
		_menuButton[i].menuBg->alphaRender(getCameraDC(), _menuButton[i].aboveBX, _menuButton[i].aboveButtonRect.bottom, 100);
		_menuButton[i].belowButton->render(getCameraDC(), _menuButton[i].belowBX, _menuButton[i].belowBY);
		_menuButton[i].aboveButton->render(getCameraDC(), _menuButton[i].aboveBX, _menuButton[i].aboveBY);
	}

	skillQuickSlotRender();
	//상점 렌더
	_shop->render();

	_playerManagerLink->getPlayer()->hitEnemyInfoRender(getCameraDC(), 450, 100);
}


void uiManager::fontImageRender(image* fontImage, int value, int x, int y)
{
	int _vl = value;
	whe = x;
	fontImage->frameRender(getCameraDC(), whe, y, _vl % 10, 1);
	_vl /= 10;
	if (_vl == 0) return;
	whe -= fontImage->getFrameWidth();
	fontImage->frameRender(getCameraDC(), whe, y, _vl % 10, 1);
	_vl /= 10;
	whe -= fontImage->getFrameWidth();
	if (_vl == 0) return;
	fontImage->frameRender(getCameraDC(), whe, y, _vl % 10, 1);
	_vl /= 10;
	whe -= fontImage->getFrameWidth();
	if (_vl == 0) return;
	fontImage->frameRender(getCameraDC(), whe, y, _vl % 10, 1);
	_vl /= 10;
	whe -= fontImage->getFrameWidth();
	if (_vl == 0) return;
	fontImage->frameRender(getCameraDC(), whe, y, _vl % 10, 1);
	_vl /= 10;
	whe -= fontImage->getFrameWidth();
	if (_vl == 0) return;
}	

void uiManager::menuMouseOver(void)
{
	for (int i = 0; i < 8; i++)
	{
		if (PtInRect(&_menuButton[i].menuRect, _ptMouse))
		{
			if (_menuButton[i].aboveBY > 740) _menuButton[i].aboveBY -= 5;
		}
		else
			if (_menuButton[i].aboveBY < WINSIZEY - _menuButton[i].aboveButton->getHeight() - 3)
				_menuButton[i].aboveBY += 5;
	}
}


void uiManager::windowManagement(void)
{
	//창관리
	//1 . 장비참
	_equipWindow.windowOpenRect = RectMake(_equipWindow.x, _equipWindow.y, _equipWindow.windowOpenImage->getWidth(),
		_equipWindow.windowOpenImage->getHeight());
	_equipWindow.exitRect = RectMake(_equipWindow.x + 164, _equipWindow.y + 4,
		_equipWindow.exitImage->getFrameWidth(), _equipWindow.exitImage->getFrameHeight());

	//2. 아이템창
	_itemWindow.windowOpenRect = RectMake(_itemWindow.x, _itemWindow.y, _itemWindow.windowOpenImage->getWidth(),
		_itemWindow.windowOpenImage->getHeight());
	_itemWindow.exitRect = RectMake(_itemWindow.x + 218, _itemWindow.y + 4, _itemWindow.exitImage->getFrameWidth(),
		_itemWindow.exitImage->getFrameHeight());

	//3. 스킬창
	_skillWindow.windowOpenRect = RectMake(_skillWindow.x, _skillWindow.y, _skillWindow.windowOpenImage->getWidth(), 
		_skillWindow.windowOpenImage->getHeight());
	_skillWindow.exitRect = RectMake(_skillWindow.x + 325, _skillWindow.y + 4, _skillWindow.exitImage->getFrameWidth(), 
		_skillWindow.exitImage->getFrameHeight());
	
	//4. 스탯창
	_myViewWindow.windowOpenRect = RectMake(_myViewWindow.x, _myViewWindow.y, _myViewWindow.windowOpenImage->getFrameWidth(),
		_myViewWindow.windowOpenImage->getFrameHeight());
	_myViewWindow.exitRect = RectMake(_myViewWindow.x + 410, _myViewWindow.y + 4, _myViewWindow.exitImage->getFrameWidth(),
		_myViewWindow.exitImage->getFrameHeight());
	_myViewChangeButton[0] = RectMake(_myViewWindow.x + 46, _myViewWindow.y + 24, 61, 19);
	_myViewChangeButton[1] = RectMake(_myViewWindow.x + 106, _myViewWindow.y + 24, 61, 19);
	
	if (_menuBtnDelay <= 0) _menuBtnDelay = 0.0f;
	else _menuBtnDelay -= TIMEMANAGER->getElapsedTime();

	//장비창 오픈
	if (KEYMANAGER->isOnceKeyDown('E')
		|| (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && PtInRect(&_menuButton[3].menuRect, _ptMouse)) && _menuBtnDelay == 0)
	{
		if (_shop->getShopOn()) return;

		if (!_equipWindow.isOpen)
		{
			_equipWindow.isOpen = true;
		}
		else
		{
			_equipWindow.isOpen = false;
		}

		clickSound();
		_menuBtnDelay = 0.8f;
	}
	//아이템창 오픈
	else if (KEYMANAGER->isOnceKeyDown('I')
		|| (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && PtInRect(&_menuButton[2].menuRect, _ptMouse)) && _menuBtnDelay == 0)
	{
		if (_shop->getShopOn()) return;

		if (!_itemWindow.isOpen)
		{
			_itemWindow.isOpen = true;
		}
		else _itemWindow.isOpen = false;

		clickSound();
		_menuBtnDelay = 0.8f;
	}
	//스킬창 오픈
	else if (KEYMANAGER->isOnceKeyDown('S')
		|| (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && PtInRect(&_menuButton[0].menuRect, _ptMouse)) && _menuBtnDelay == 0)
	{
		if (!_skillWindow.isOpen)
		{
			_skillWindow.isOpen = true;
		}
		else _skillWindow.isOpen = false;

		clickSound();
		_menuBtnDelay = 0.8f;
	}
	//스탯창
	else if (KEYMANAGER->isOnceKeyDown('V')
		|| PtInRect(&_menuButton[4].menuRect, _ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _menuBtnDelay == 0)
	{
		if (!_myViewWindow.isOpen)
		{
			_myViewWindow.isOpen = true;
		}
		else _myViewWindow.isOpen = false;

		clickSound();
		_menuBtnDelay = 0.8f;
	}

	//스탯창 관련
	if (_myViewWindow.isOpen)
	{
		if (PtInRect(&_myViewChangeButton[0], _ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON)
			&& _myViewFrame == 1)
		{
			_myViewFrame = 0;
			clickSound();
		}
		if (PtInRect(&_myViewChangeButton[1], _ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON)
			&& _myViewFrame == 0)	
		{
			_myViewFrame = 1;
			clickSound();
		}
	}

	for (int i = 0; i < _vWindows.size(); i++)
	{
		if (PtInRect(&RectMake(_vWindows[i]->x, _vWindows[i]->y, _vWindows[i]->windowOpenImage->getWidth(),
			20), _ptMouse)
			&& KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			tagWindow* _temp = _vWindows[i];
			_vWindows[i] = _vWindows[_vWindows.size() - 1];
			_vWindows[_vWindows.size() - 1] = _temp;
		}

		//exit
		if (PtInRect(&_vWindows[i]->exitRect, _ptMouse))
		{
			_vWindows[i]->exitFrame = 1;
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)
				&& _vWindows[i]->isOpen)
			{
				_vWindows[i]->exitFrame = 2;
				_vWindows[i]->isOpen = false;
				if (SOUNDMANAGER->isPlaySound("창닫기"))
				{
					SOUNDMANAGER->stop("창닫기");
					SOUNDMANAGER->play("창닫기", 0.5f);
				}
				else SOUNDMANAGER->play("창닫기", 0.5f);
			}
		}
		else _vWindows[i]->exitFrame = 0;

	}


	//스탯올리기
	if (_myViewWindow.isOpen && _myViewFrame == 1)
	{
		_statsRect[0] = RectMake(_myViewWindow.x + 417, _myViewWindow.y - 443 + 528, 9, 15);
		_statsRect[1] = RectMake(_myViewWindow.x + 417, _myViewWindow.y - 443 + 548, 9, 15);
		_statsRect[2] = RectMake(_myViewWindow.x + 417, _myViewWindow.y - 443 + 568, 9, 15);
		_statsRect[3] = RectMake(_myViewWindow.x + 417, _myViewWindow.y - 443 + 591, 9, 15);
		_statsRect[4] = RectMake(_myViewWindow.x + 417, _myViewWindow.y - 443 + 654, 9, 15);
		_statsRect[5] = RectMake(_myViewWindow.x + 417, _myViewWindow.y - 443 + 674, 9, 15);
		_statsRect[6] = RectMake(_myViewWindow.x + 417, _myViewWindow.y - 443 + 694, 9, 15);
		_statsRect[7] = RectMake(_myViewWindow.x + 417, _myViewWindow.y - 443 + 717, 9, 15);
		_statsRect[8] = RectMake(_myViewWindow.x + 417, _myViewWindow.y - 443 + 737, 9, 15);
		_statsRect[9] = RectMake(_myViewWindow.x + 417, _myViewWindow.y - 443 + 757, 9, 15);
	}
}

void uiManager::windowRender(void)
{
	for (int i = 0; i < _vWindows.size(); i++)
	{
		if (_vWindows[i]->isOpen)
		{
			char str[128];
			if (_vWindows[i] == &_myViewWindow)
			{
				_vWindows[i]->windowOpenImage->frameRender(getCameraDC(), _vWindows[i]->x, _vWindows[i]->y, 0, _myViewFrame);
				fontCameraRender("NtreevSoft", _playerManagerLink->getPlayer()->getName(), 17, 1,
					_myViewWindow.x + 82, _myViewWindow.y + 46, RGB(0, 0, 0));
				

				if (_myViewFrame == 0)
				{
					sprintf(str, "%d", _playerManagerLink->getPlayer()->getLv());
					fontCameraRender("NtreevSoft", str, 17, 1,
						_myViewWindow.x + 250, _myViewWindow.y + 99, RGB(0, 0, 0));

					sprintf(str, "%d", _playerManagerLink->getPlayer()->getTm());
					fontCameraRender("NtreevSoft", str, 17, 1,
						_myViewWindow.x + 250, _myViewWindow.y + 121, RGB(0, 0, 0));
				}
				else if (_myViewFrame == 1)
				{
					sprintf(str, "%d", _playerManagerLink->getPlayer()->getAp());
					fontCameraRender("NtreevSoft", str, 17, 1,
						_myViewWindow.x + 200, _myViewWindow.y + 85, RGB(0, 0, 0));
					sprintf(str, "%2.0f", _playerManagerLink->getPlayer()->getAc());
					fontCameraRender("NtreevSoft", str, 17, 1,
						_myViewWindow.x + 200, _myViewWindow.y + 105, RGB(0, 0, 0));
					sprintf(str, "%d", _playerManagerLink->getPlayer()->getDx());
					fontCameraRender("NtreevSoft", str, 17, 1,
						_myViewWindow.x + 200, _myViewWindow.y + 125, RGB(0, 0, 0));
					sprintf(str, "%d", _playerManagerLink->getPlayer()->getMaxMp());
					fontCameraRender("NtreevSoft", str, 17, 1,
						_myViewWindow.x + 200, _myViewWindow.y + 148, RGB(0, 0, 0));
					sprintf(str, "%d", _playerManagerLink->getPlayer()->getWt());
					fontCameraRender("NtreevSoft", str, 17, 1,
						_myViewWindow.x + 200, _myViewWindow.y + 211, RGB(0, 0, 0));
					sprintf(str, "%d", _playerManagerLink->getPlayer()->getDa());
					fontCameraRender("NtreevSoft", str, 17, 1,
						_myViewWindow.x + 200, _myViewWindow.y + 231, RGB(0, 0, 0));
					sprintf(str, "%d", _playerManagerLink->getPlayer()->getDa());
					fontCameraRender("NtreevSoft", str, 17, 1,
						_myViewWindow.x + 200, _myViewWindow.y + 231, RGB(0, 0, 0));
					sprintf(str, "%d", _playerManagerLink->getPlayer()->getLk());
					fontCameraRender("NtreevSoft", str, 17, 1,
						_myViewWindow.x + 200, _myViewWindow.y + 251, RGB(0, 0, 0));
					sprintf(str, "%d", _playerManagerLink->getPlayer()->getMaxHp());
					fontCameraRender("NtreevSoft", str, 17, 1,
						_myViewWindow.x + 200, _myViewWindow.y + 274, RGB(0, 0, 0));
					sprintf(str, "%d", _playerManagerLink->getPlayer()->getDp());
					fontCameraRender("NtreevSoft", str, 17, 1,
						_myViewWindow.x + 200, _myViewWindow.y + 294, RGB(0, 0, 0));
					sprintf(str, "%d", _playerManagerLink->getPlayer()->getHv());
					fontCameraRender("NtreevSoft", str, 17, 1,
						_myViewWindow.x + 200, _myViewWindow.y + 314, RGB(0, 0, 0));

					sprintf(str, "%d", _playerManagerLink->getPlayer()->getBonusStat());
					fontCameraRender("NtreevSoft", str, 15, 1,
						_myViewWindow.x + 400, _myViewWindow.y + 66, RGB(0, 0, 0));
				}
			}
			else
			{
				_vWindows[i]->windowOpenImage->render(getCameraDC(), _vWindows[i]->x, _vWindows[i]->y);

				if (_vWindows[i] == &_skillWindow)
				{
					sprintf(str, "%d", _playerManagerLink->getPlayer()->getTm());
					fontCameraRender("NtreevSoft", str, 14, 1,
						_skillWindow.x + 98, _skillWindow.y + 66, RGB(0, 0, 0));

					sprintf(str, "%d", _playerManagerLink->getPlayer()->getSkillPoint());
					fontCameraRender("NtreevSoft", str, 14, 1,
						_skillWindow.x + 263, _skillWindow.y + 48, RGB(0, 0, 0));

					sprintf(str, "%3.0f", _playerManagerLink->getPlayer()->getTmExp()
						/ (float)_playerManagerLink->getPlayer()->getMaxTmExp() * 100);
					fontCameraRender("NtreevSoft", str, 14, 1,
						_skillWindow.x + 304, _skillWindow.y + 67, RGB(0, 0, 0));

					IMAGEMANAGER->findImage("tmBar2")->render(getCameraDC(), _skillWindow.x + 177, _skillWindow.y + 70, 0, 0, (int)(_playerManagerLink->getPlayer()->getTmExp()
						/ (float)_playerManagerLink->getPlayer()->getMaxTmExp() * IMAGEMANAGER->findImage("tmBar2")->getWidth()), IMAGEMANAGER->findImage("tmBar2")->getHeight());
					
					//스킬1 렌더
					if (_playerManagerLink->getPlayer()->getSkill(0).isGet)
					{
						_playerManagerLink->getPlayer()->getSkill(0).skillIcon->render(getCameraDC(), _skillWindow.x + 22, _skillWindow.y + 98);
						sprintf(str, "%d", _playerManagerLink->getPlayer()->getSkill(0).lv);
						fontCameraRender("NtreevSoft", str, 15, 1000, _skillWindow.x + 35, _skillWindow.y + 109, RGB(0, 0, 0));
					}
					else
						_playerManagerLink->getPlayer()->getSkill(0).skillIcon->alphaRender(getCameraDC(), _skillWindow.x + 22, _skillWindow.y + 98, 125);

					//스킬2 렌더
					if (_playerManagerLink->getPlayer()->getSkill(1).isGet)
					{
						_playerManagerLink->getPlayer()->getSkill(1).skillIcon->render(getCameraDC(), _skillWindow.x + 65, _skillWindow.y + 98);
						sprintf(str, "%d", _playerManagerLink->getPlayer()->getSkill(1).lv);
						fontCameraRender("NtreevSoft", str, 15, 1000, _skillWindow.x + 78, _skillWindow.y + 109, RGB(0, 0, 0));
					}
					else
						_playerManagerLink->getPlayer()->getSkill(1).skillIcon->alphaRender(getCameraDC(), _skillWindow.x + 65, _skillWindow.y + 98, 125);

					//스킬3 렌더
					if (_playerManagerLink->getPlayer()->getSkill(2).isGet)
					{
						_playerManagerLink->getPlayer()->getSkill(2).skillIcon->render(getCameraDC(), _skillWindow.x + 108, _skillWindow.y + 98);
						sprintf(str, "%d", _playerManagerLink->getPlayer()->getSkill(2).lv);
						fontCameraRender("NtreevSoft", str, 15, 1000, _skillWindow.x + 121, _skillWindow.y + 109, RGB(0, 0, 0));
					}
					else
						_playerManagerLink->getPlayer()->getSkill(2).skillIcon->alphaRender(getCameraDC(), _skillWindow.x + 108, _skillWindow.y + 98, 125);
				}

				if (_vWindows[i] == &_itemWindow)
				{
					sprintf(str, "( %d / %d )", _playerManagerLink->getPlayer()->getInven().size(), _playerManagerLink->getPlayer()->getInvenMaxSize());
					fontCameraRender("NtreevSoft", str, 14, 1, _vWindows[i]->x + 78, _vWindows[i]->y + 5, RGB(0, 0, 0));

					playerInvenItemRender();
				}

				if (_vWindows[i] == &_equipWindow)
				{
					playerEquipItemRender();
				}
			}
			
			_vWindows[i]->exitImage->frameRender(getCameraDC(), _vWindows[i]->exitRect.left, _vWindows[i]->exitRect.top, 0, _vWindows[i]->exitFrame);
		}
	}
}

void uiManager::moveWindow(void)
{
	
	for (int i = 0; i < _vWindows.size(); i++)
	{
		if (_vWindows[i]->isOpen)
		{
			if(PtInRect(&RectMake(_vWindows[i]->x, _vWindows[i]->y, _vWindows[i]->windowOpenImage->getWidth(),
				20), _ptMouse)
				&& KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				_vWindows[i]->x = _ptMouse.x - _vWindows[i]->windowOpenImage->getWidth() / 2;
				_vWindows[i]->y = _ptMouse.y - 8;
			}
		}
	}
}

void uiManager::shopOpenOrNot(void)
{
	//로비맵일 때
	if (_equipWindow.isOpen || _itemWindow.isOpen) return;
	_shop->shopOpenAndClose();
}

void uiManager::setPlayerItemLocation(void)
{
	//무기 아이콘 위치잡기
	if (_playerManagerLink->getPlayer()->getWeapon() != NULL)
	{
		_playerManagerLink->getPlayer()->getWeapon()->setIconX(_equipWindow.x + 27);
		_playerManagerLink->getPlayer()->getWeapon()->setIconY(_equipWindow.y + 74);
	}
	//헬멧 아이콘 위치잡기
	if (_playerManagerLink->getPlayer()->getHelmet() != NULL)
	{
		_playerManagerLink->getPlayer()->getHelmet()->setIconX(_equipWindow.x + 62);
		_playerManagerLink->getPlayer()->getHelmet()->setIconY(_equipWindow.y + 36);
	}
	//방패 아이콘 위치잡기
	if (_playerManagerLink->getPlayer()->getShield() != NULL)
	{
		_playerManagerLink->getPlayer()->getShield()->setIconX(_equipWindow.x + 140);
		_playerManagerLink->getPlayer()->getShield()->setIconY(_equipWindow.y + 70);
	}
	//악세서리 아이콘 위치잡기
	if (_playerManagerLink->getPlayer()->getAccessory() != NULL)
	{
		_playerManagerLink->getPlayer()->getAccessory()->setIconX(_equipWindow.x + 20);
		_playerManagerLink->getPlayer()->getAccessory()->setIconY(_equipWindow.y + 102);
	}
	if (_playerManagerLink->getPlayer()->getDrillItem() != NULL)
	{
		_playerManagerLink->getPlayer()->getDrillItem()->setIconX(_equipWindow.x + 140);
		_playerManagerLink->getPlayer()->getDrillItem()->setIconY(_equipWindow.y + 134);
	}
	//인벤토리 아이템 아이콘 위치잡기
	for (int i = 0; i < _playerManagerLink->getPlayer()->getInventorySize(); i++)
	{
		_playerManagerLink->getPlayer()->getInvenItem(i)->setIconX(_itemWindow.x + 12 + 36 * (i % 6));
		_playerManagerLink->getPlayer()->getInvenItem(i)->setIconY(_itemWindow.y + 56 + 36 * (i / 6));
	}
}

void uiManager::playerEquipItemRender(void)
{
	if (_playerManagerLink->getPlayer()->getWeapon() != NULL)
	{
		_playerManagerLink->getPlayer()->getWeapon()->iconRender();
		if (PtInRect(&_playerManagerLink->getPlayer()->getWeapon()->getIconRC(), _ptMouse))
		{
			_playerManagerLink->getPlayer()->getWeapon()->desRender();
		}
	}

	if (_playerManagerLink->getPlayer()->getHelmet() != NULL)
	{
		_playerManagerLink->getPlayer()->getHelmet()->iconRender();
		if (PtInRect(&_playerManagerLink->getPlayer()->getHelmet()->getIconRC(), _ptMouse))
		{
			_playerManagerLink->getPlayer()->getHelmet()->desRender();
		}
	}

	if (_playerManagerLink->getPlayer()->getShield() != NULL)
	{
		_playerManagerLink->getPlayer()->getShield()->iconRender();
		if (PtInRect(&_playerManagerLink->getPlayer()->getShield()->getIconRC(), _ptMouse))
			_playerManagerLink->getPlayer()->getShield()->desRender();
	}

	if (_playerManagerLink->getPlayer()->getAccessory() != NULL)
	{
		_playerManagerLink->getPlayer()->getAccessory()->iconRender();
		if (PtInRect(&_playerManagerLink->getPlayer()->getAccessory()->getIconRC(), _ptMouse))
			_playerManagerLink->getPlayer()->getAccessory()->desRender();
	}

	if (_playerManagerLink->getPlayer()->getDrillItem() != NULL)
	{
		_playerManagerLink->getPlayer()->getDrillItem()->iconRender();
		if (PtInRect(&_playerManagerLink->getPlayer()->getDrillItem()->getIconRC(), _ptMouse))
			_playerManagerLink->getPlayer()->getDrillItem()->desRender();
	}
}

void uiManager::playerInvenItemRender(void)
{
	char str[128];
	int k;
	for (int i = 0; i < _playerManagerLink->getPlayer()->getInventorySize(); i++)
	{
		_playerManagerLink->getPlayer()->getInvenItem(i)->iconRender();
		if (PtInRect(&_playerManagerLink->getPlayer()->getInvenItem(i)->getIconRC(), _ptMouse))
		{
			_playerManagerLink->getPlayer()->getInvenItem(i)->desRender();
			switch (_playerManagerLink->getPlayer()->getInvenItem(i)->getItemKind())
			{
			case ITEM_WEAPON:
				if (_playerManagerLink->getPlayer()->getWeapon() == NULL) break;

				//ap비교
				k = _playerManagerLink->getPlayer()->getWeapon()->getApUp()
					- _playerManagerLink->getPlayer()->getInvenItem(i)->getApUp();
				if (k > 0)
				{
					IMAGEMANAGER->findImage("스펙업")->render(getCameraDC(),
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 184,
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() - 6);
				}
				else if (k < 0)
				{
					IMAGEMANAGER->findImage("스펙다운")->render(getCameraDC(),
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 184,
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() - 6);
				}
				else;
				sprintf_s(str, "%d", abs(k));
				fontCameraRender("NtreevSoft", str, 16, 1,
					_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 204,
					_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() - 6, RGB(255, 255, 255));
				
				//ac비교
				k = (int)(_playerManagerLink->getPlayer()->getWeapon()->getAcUp()
					- _playerManagerLink->getPlayer()->getInvenItem(i)->getAcUp());
				if (k > 0)
				{
					IMAGEMANAGER->findImage("스펙업")->render(getCameraDC(),
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 184,
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() + 10);
				}
				else if (k < 0)
				{
					IMAGEMANAGER->findImage("스펙다운")->render(getCameraDC(),
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 184,
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() + 10);
				}
				sprintf_s(str, "%d", abs(k));
				fontCameraRender("NtreevSoft", str, 16, 1,
					_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 204,
					_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() + 10, RGB(255, 255, 255));

				//dx비교
				k = (int)(_playerManagerLink->getPlayer()->getWeapon()->getDxUp()
					- _playerManagerLink->getPlayer()->getInvenItem(i)->getDxUp());
				if (k > 0)
				{
					IMAGEMANAGER->findImage("스펙업")->render(getCameraDC(),
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 184,
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() + 26);
				}
				else if (k < 0)
				{
					IMAGEMANAGER->findImage("스펙다운")->render(getCameraDC(),
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 184,
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() + 26);
				}
				sprintf_s(str, "%d", abs(k));
				fontCameraRender("NtreevSoft", str, 16, 1,
					_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 204,
					_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() + 26, RGB(255, 255, 255));

				break;
			case ITEM_SHIELD:
				if (_playerManagerLink->getPlayer()->getShield() == NULL) break;
				//Hp
				k = _playerManagerLink->getPlayer()->getShield()->getHpUp()
					- _playerManagerLink->getPlayer()->getInvenItem(i)->getHpUp();
				if (k > 0)
				{
					IMAGEMANAGER->findImage("스펙업")->render(getCameraDC(),
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 287,
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() + 10);
				}
				else if (k < 0)
				{
					IMAGEMANAGER->findImage("스펙다운")->render(getCameraDC(),
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 287,
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() + 10);
				}
				else;
				sprintf_s(str, "%d", abs(k));
				fontCameraRender("NtreevSoft", str, 16, 1,
					_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 307,
					_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() + 10, RGB(255, 255, 255));

				//Dp
				k = _playerManagerLink->getPlayer()->getShield()->getDpUp()
					- _playerManagerLink->getPlayer()->getInvenItem(i)->getDpUp();
				if (k > 0)
				{
					IMAGEMANAGER->findImage("스펙업")->render(getCameraDC(),
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 287,
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() + 26);
				}
				else if (k < 0)
				{
					IMAGEMANAGER->findImage("스펙다운")->render(getCameraDC(),
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 287,
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() + 26);
				}
				else;
				sprintf_s(str, "%d", abs(k));
				fontCameraRender("NtreevSoft", str, 16, 1,
					_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 307,
					_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() + 26, RGB(255, 255, 255));

				break;
			case ITEM_HAT:
				if (_playerManagerLink->getPlayer()->getHelmet() == NULL) break;

				//dx
				k = _playerManagerLink->getPlayer()->getHelmet()->getDxUp()
					- _playerManagerLink->getPlayer()->getInvenItem(i)->getDxUp();
				if (k > 0)
				{
					IMAGEMANAGER->findImage("스펙업")->render(getCameraDC(),
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 184,
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() + 26);
				}
				else if (k < 0)
				{
					IMAGEMANAGER->findImage("스펙다운")->render(getCameraDC(),
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 184,
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() + 26);
				}
				else;
				sprintf_s(str, "%d", abs(k));
				fontCameraRender("NtreevSoft", str, 16, 1,
					_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 204,
					_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() + 26, RGB(255, 255, 255));
				
				//dp
				k = _playerManagerLink->getPlayer()->getHelmet()->getDpUp()
					- _playerManagerLink->getPlayer()->getInvenItem(i)->getDpUp();
				if (k > 0)
				{
					IMAGEMANAGER->findImage("스펙업")->render(getCameraDC(),
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 287,
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() + 26);
				}
				else if (k < 0)
				{
					IMAGEMANAGER->findImage("스펙다운")->render(getCameraDC(),
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 287,
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() + 26);
				}
				else;
				sprintf_s(str, "%d", abs(k));
				fontCameraRender("NtreevSoft", str, 16, 1,
					_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 307,
					_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() + 26, RGB(255, 255, 255));
				
				//hv
				k = _playerManagerLink->getPlayer()->getHelmet()->getHvUp()
					- _playerManagerLink->getPlayer()->getInvenItem(i)->getHvUp();
				if (k > 0)
				{
					IMAGEMANAGER->findImage("스펙업")->render(getCameraDC(),
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 287,
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() + 42);
				}
				else if (k < 0)
				{
					IMAGEMANAGER->findImage("스펙다운")->render(getCameraDC(),
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 287,
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() + 42);
				}
				else;
				sprintf_s(str, "%d", abs(k));
				fontCameraRender("NtreevSoft", str, 16, 1,
					_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 307,
					_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() + 42, RGB(255, 255, 255));
				
				break;
			case ITEM_ACCESSORY:
				if (_playerManagerLink->getPlayer()->getAccessory() == NULL) break;

				//wt
				k = _playerManagerLink->getPlayer()->getAccessory()->getWtUp()
					- _playerManagerLink->getPlayer()->getInvenItem(i)->getWtUp();
				if (k > 0)
				{
					IMAGEMANAGER->findImage("스펙업")->render(getCameraDC(),
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 184,
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() + 58);
				}
				else if (k < 0)
				{
					IMAGEMANAGER->findImage("스펙다운")->render(getCameraDC(),
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 184,
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() + 58);
				}
				else;
				sprintf_s(str, "%d", abs(k));
				fontCameraRender("NtreevSoft", str, 16, 1,
					_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 204,
					_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() + 58, RGB(255, 255, 255));

				//lk
				k = _playerManagerLink->getPlayer()->getAccessory()->getLkUp()
					- _playerManagerLink->getPlayer()->getInvenItem(i)->getLkUp();
				if (k > 0)
				{
					IMAGEMANAGER->findImage("스펙업")->render(getCameraDC(),
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 287,
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() - 6);
				}
				else if (k < 0)
				{
					IMAGEMANAGER->findImage("스펙다운")->render(getCameraDC(),
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 287,
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() - 6);
				}
				else;
				sprintf_s(str, "%d", abs(k));
				fontCameraRender("NtreevSoft", str, 16, 1,
					_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 307,
					_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() - 6, RGB(255, 255, 255));
				
				//mp
				k = _playerManagerLink->getPlayer()->getAccessory()->getMpUp()
					- _playerManagerLink->getPlayer()->getInvenItem(i)->getMpUp();
				if (k > 0)
				{
					IMAGEMANAGER->findImage("스펙업")->render(getCameraDC(),
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 184,
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() + 42);
				}
				else if (k < 0)
				{
					IMAGEMANAGER->findImage("스펙다운")->render(getCameraDC(),
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 184,
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() + 42);
				}
				else;
				sprintf_s(str, "%d", abs(k));
				fontCameraRender("NtreevSoft", str, 16, 1,
					_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 204,
					_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() + 42, RGB(255, 255, 255));

				//hv
				k = _playerManagerLink->getPlayer()->getAccessory()->getHvUp()
					- _playerManagerLink->getPlayer()->getInvenItem(i)->getHvUp();
				if (k > 0)
				{
					IMAGEMANAGER->findImage("스펙업")->render(getCameraDC(),
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 287,
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() + 42);
				}
				else if (k < 0)
				{
					IMAGEMANAGER->findImage("스펙다운")->render(getCameraDC(),
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 287,
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() + 42);
				}
				else;
				sprintf_s(str, "%d", abs(k));
				fontCameraRender("NtreevSoft", str, 16, 1,
					_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 307,
					_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() + 42, RGB(255, 255, 255));


				break;
			case ITEM_DRILL:
				//da
				if (_playerManagerLink->getPlayer()->getDrillItem() == NULL) break;

				k = _playerManagerLink->getPlayer()->getDrillItem()->getDaUp()
					- _playerManagerLink->getPlayer()->getInvenItem(i)->getDaUp();
				if (k > 0)
				{
					IMAGEMANAGER->findImage("스펙업")->render(getCameraDC(),
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 184,
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() + 74);
				}
				else if (k < 0)
				{
					IMAGEMANAGER->findImage("스펙다운")->render(getCameraDC(),
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 184,
						_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() + 74);
				}
				else;
				sprintf_s(str, "%d", abs(k));
				fontCameraRender("NtreevSoft", str, 16, 1,
					_playerManagerLink->getPlayer()->getInvenItem(i)->getDesX() + 204,
					_playerManagerLink->getPlayer()->getInvenItem(i)->getDesY() + 74, RGB(255, 255, 255));
				break;
			}
		}
	}
}

void uiManager::statUp(void)
{
	if (_playerManagerLink->getPlayer()->getBonusStat() <= 0) return;
	
	if (!_myViewWindow.isOpen) return;
	else
	{
		if (_myViewFrame != 1) return;
	}

	_statBtnDelay -= TIMEMANAGER->getElapsedTime();
	if (_statBtnDelay < 0) _statBtnDelay = 0;

	if (PtInRect(&_statsRect[0], _ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON)
		&& _statBtnDelay == 0)
	{
		_statBtnDelay = 0.5f;
		_playerManagerLink->getPlayer()->setAp(_playerManagerLink->getPlayer()->getAp() + 1);
		_playerManagerLink->getPlayer()->setBonusStat(_playerManagerLink->getPlayer()->getBonusStat() - 1);
		clickSound();
	}
	else if (PtInRect(&_statsRect[1], _ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON)
		&& _statBtnDelay == 0)
	{
		_statBtnDelay = 0.5f;
		_playerManagerLink->getPlayer()->setAc(_playerManagerLink->getPlayer()->getAc() + 1);
		_playerManagerLink->getPlayer()->setBonusStat(_playerManagerLink->getPlayer()->getBonusStat() - 1);
		clickSound();
	}
	else if (PtInRect(&_statsRect[2], _ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON)
		&& _statBtnDelay == 0)
	{
		_statBtnDelay = 0.5f;
		_playerManagerLink->getPlayer()->setDx(_playerManagerLink->getPlayer()->getDx() + 1);
		_playerManagerLink->getPlayer()->setBonusStat(_playerManagerLink->getPlayer()->getBonusStat() - 1);
		clickSound();
	}
	else if (PtInRect(&_statsRect[3], _ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON)
		&& _statBtnDelay == 0)
	{
		_statBtnDelay = 0.5f;
		_playerManagerLink->getPlayer()->setMaxMp(_playerManagerLink->getPlayer()->getMaxMp() + 30);
		_playerManagerLink->getPlayer()->setBonusStat(_playerManagerLink->getPlayer()->getBonusStat() - 1);
		clickSound();
	}
	else if (PtInRect(&_statsRect[4], _ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON)
		&& _statBtnDelay == 0)
	{
		_statBtnDelay = 0.5f;
		_playerManagerLink->getPlayer()->setWt(_playerManagerLink->getPlayer()->getWt() + 1);
		_playerManagerLink->getPlayer()->setBonusStat(_playerManagerLink->getPlayer()->getBonusStat() - 1);
		clickSound();
	}
	else if (PtInRect(&_statsRect[5], _ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON)
		&& _statBtnDelay == 0)
	{
		_statBtnDelay = 0.5f;
		_playerManagerLink->getPlayer()->setDa(_playerManagerLink->getPlayer()->getDa() + 1);
		_playerManagerLink->getPlayer()->setBonusStat(_playerManagerLink->getPlayer()->getBonusStat() - 1);
		clickSound();
	}
	else if (PtInRect(&_statsRect[6], _ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON)
		&& _statBtnDelay == 0)
	{
		_statBtnDelay = 0.5f;
		_playerManagerLink->getPlayer()->setLk(_playerManagerLink->getPlayer()->getLk() + 1);
		_playerManagerLink->getPlayer()->setBonusStat(_playerManagerLink->getPlayer()->getBonusStat() - 1);
		clickSound();
	}
	else if (PtInRect(&_statsRect[7], _ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON)
		&& _statBtnDelay == 0)
	{
		_statBtnDelay = 0.5f;
		_playerManagerLink->getPlayer()->setMaxHp(_playerManagerLink->getPlayer()->getMaxHp() + 30);
		_playerManagerLink->getPlayer()->setBonusStat(_playerManagerLink->getPlayer()->getBonusStat() - 1);
		clickSound();
	}
	else if (PtInRect(&_statsRect[8], _ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON)
		&& _statBtnDelay == 0)
	{
		_statBtnDelay = 0.5f;
		_playerManagerLink->getPlayer()->setDp(_playerManagerLink->getPlayer()->getDp() + 1);
		_playerManagerLink->getPlayer()->setBonusStat(_playerManagerLink->getPlayer()->getBonusStat() - 1);
		clickSound();
	}
	else if (PtInRect(&_statsRect[9], _ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON)
		&& _statBtnDelay == 0)
	{
		_statBtnDelay = 0.5f;
		_playerManagerLink->getPlayer()->setHv(_playerManagerLink->getPlayer()->getHv() + 1);
		_playerManagerLink->getPlayer()->setBonusStat(_playerManagerLink->getPlayer()->getBonusStat() - 1);
		clickSound();
	}
}

void uiManager::skillLvUp(void)
{
	if (_skillWindow.isOpen)
	{
		if (_playerManagerLink->getPlayer()->getSkill(0).isGet)
		{
			if (PtInRect(&RectMake(_skillWindow.x + 22, _skillWindow.y + 98, 26, 26), _ptMouse)
				&& KEYMANAGER->isOnceKeyDown(VK_RBUTTON) && _playerManagerLink->getPlayer()->getSkill(0).lv < 10)
			{
				if (_playerManagerLink->getPlayer()->getSkillPoint() > 0)
				{
					_playerManagerLink->getPlayer()->setSkillLv(0, _playerManagerLink->getPlayer()->getSkillLv(0) + 1);
					_playerManagerLink->getPlayer()->setSkillPoint(_playerManagerLink->getPlayer()->getSkillPoint() - 1);
					clickSound();
					if (_playerManagerLink->getPlayer()->getSkillLv(0) <= 9)
					{
						SOUNDMANAGER->play("스킬레벨업", 0.5f);
						_playerManagerLink->getPlayer()->skillLvUpEffectRender();
					}
					if (_playerManagerLink->getPlayer()->getSkillLv(0) == 10)
					{
						_playerManagerLink->getPlayer()->skillMasterRender();
						SOUNDMANAGER->play("스킬마스터", 0.5f);
					}
				}
			}
		}

		if (_playerManagerLink->getPlayer()->getSkill(1).isGet)
		{
			if (PtInRect(&RectMake(_skillWindow.x + 65, _skillWindow.y + 98, 26, 26), _ptMouse)
				&& KEYMANAGER->isOnceKeyDown(VK_RBUTTON) && _playerManagerLink->getPlayer()->getSkill(1).lv < 10)
			{
				if (_playerManagerLink->getPlayer()->getSkillPoint() > 0)
				{
					_playerManagerLink->getPlayer()->setSkillLv(1, _playerManagerLink->getPlayer()->getSkillLv(1) + 1);
					_playerManagerLink->getPlayer()->setSkillPoint(_playerManagerLink->getPlayer()->getSkillPoint() - 1);
					clickSound();
					if (_playerManagerLink->getPlayer()->getSkillLv(1) <= 9)
					{
						SOUNDMANAGER->play("스킬레벨업", 0.5f);
						_playerManagerLink->getPlayer()->skillLvUpEffectRender();
					}
					if (_playerManagerLink->getPlayer()->getSkillLv(1) == 10)
					{
						_playerManagerLink->getPlayer()->skillMasterRender();
						SOUNDMANAGER->play("스킬마스터", 0.5f);
					}
				}
			}
		}

		if (_playerManagerLink->getPlayer()->getSkill(2).isGet)
		{
			if (PtInRect(&RectMake(_skillWindow.x + 108, _skillWindow.y + 98, 26, 26), _ptMouse)
				&& KEYMANAGER->isOnceKeyDown(VK_RBUTTON) && _playerManagerLink->getPlayer()->getSkill(2).lv < 10)
			{
				if (_playerManagerLink->getPlayer()->getSkillPoint() > 0)
				{
					_playerManagerLink->getPlayer()->setSkillLv(2, _playerManagerLink->getPlayer()->getSkillLv(2) + 1);
					_playerManagerLink->getPlayer()->setSkillPoint(_playerManagerLink->getPlayer()->getSkillPoint() - 1);
					clickSound();
					if (_playerManagerLink->getPlayer()->getSkillLv(2) <= 9)
					{
						SOUNDMANAGER->play("스킬레벨업", 0.5f);
						_playerManagerLink->getPlayer()->skillLvUpEffectRender();
					}
					if (_playerManagerLink->getPlayer()->getSkillLv(2) == 10)
					{
						_playerManagerLink->getPlayer()->skillMasterRender();
						SOUNDMANAGER->play("스킬마스터", 0.5f);
					}
				}
			}
		}
	}
}

void uiManager::skillQuickSlotManagement(void)
{
	_skillQRC = RectMake(_skillQx, _skillQy, _skillQWindow->getWidth(), _skillQWindow->getHeight());
}

void uiManager::skillQuickSlotRender(void)
{
	_skillQWindow->render(getCameraDC(), _skillQx, _skillQy);

	_playerManagerLink->getPlayer()->skillIconRender(0);
	_playerManagerLink->getPlayer()->skillIconRender(1);
	_playerManagerLink->getPlayer()->skillIconRender(2);
}