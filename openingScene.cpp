#include "stdafx.h"
#include "openingScene.h"


openingScene::openingScene()
{
}


openingScene::~openingScene()
{
}

HRESULT openingScene::init(void)
{
	_bg = IMAGEMANAGER->findImage("시작");
	_startButton = IMAGEMANAGER->addFrameImage("시작버튼", "images/UI/gameStart.bmp", 246, 270, 1, 3, true, RGB(255, 0, 255));
	_startBtnX = 1050;
	_startBtnY = 550;
	_startBtnRect = RectMake(_startBtnX, _startBtnY, _startButton->getFrameWidth(), _startButton->getFrameHeight());

	

	return S_OK;
}

void openingScene::release(void)
{

}

void openingScene::update(void)
{
	_startBtnRect = RectMake(_startBtnX, _startBtnY, 
		_startButton->getFrameWidth(), _startButton->getFrameHeight());
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && PtInRect(&_startBtnRect, _ptMouse))
	{
		clickSound();
		_sceneType = SELECT;
	}
}

void openingScene::render(void)
{
	_bg->render(getMemDC(), 0, 0);

	if (PtInRect(&_startBtnRect, _ptMouse))
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			_startButton->frameRender(getMemDC(), _startBtnX, _startBtnY, 0, 2);
		else
			_startButton->frameRender(getMemDC(), _startBtnX, _startBtnY, 0, 1);
	}
	else _startButton->frameRender(getMemDC(), _startBtnX, _startBtnY, 0, 0);
}