#include "stdafx.h"
#include "selectScene.h"
#include "playerManager.h"

selectScene::selectScene()
{
}


selectScene::~selectScene()
{
}

HRESULT selectScene::init(void)
{
	_bg = IMAGEMANAGER->findImage("����");
	_selectButton = IMAGEMANAGER->addImage("ĳ���ͼ��ù��", "images/ui/charShow.bmp", 582, 346, true, RGB(255, 0, 255));

	_nowChar = IMAGEMANAGER->addImage("���缱��ĳ����", "images/ui/nowChar.bmp", 176, 260, true, RGB(255, 0, 255));

	_charCardRC[0] = RectMake(2 * WINSIZEX / 7 + 22, WINSIZEY / 4 + 44, 176, 260);
	_charCardRC[1] = RectMake(2 * WINSIZEX / 7 + 203, WINSIZEY / 4 + 44, 176, 260);
	_charCardRC[2] = RectMake(2 * WINSIZEX / 7 + 384, WINSIZEY / 4 + 44, 176, 260);

	_closeCharCard[0] = IMAGEMANAGER->addImage("ī��޸�", "images/ui/closeCard.bmp", 172, 245, true, RGB(255, 0, 255));
	_closeCharCard[1] = IMAGEMANAGER->findImage("ī��޸�");
	_closeCharCard[2] = IMAGEMANAGER->findImage("ī��޸�");

	_openCharCard = IMAGEMANAGER->addImage("�ŷ�ĳ����", "images/ui/mainCard.bmp", 172, 245, true, RGB(255, 0, 255));

	_nowCharIndex = 0;

	_chaWait[0] = IMAGEMANAGER->addFrameImage("���1", "images/character/chaBreak.bmp", 462, 40, 6, 1, true, RGB(255, 0, 255));
	_chaWait[1] = IMAGEMANAGER->addFrameImage("���2", "images/character/chaWalk5.bmp", 240, 73, 6, 1, true, RGB(255, 0, 255));

	_selectBackImage = IMAGEMANAGER->findImage("ĳ����back");
	_selectBackRect = RectMake(2 * WINSIZEX / 7 + 22, WINSIZEY / 4 + 312, _selectBackImage->getFrameWidth(),
		_selectBackImage->getFrameHeight());
	_selectOkImage = IMAGEMANAGER->findImage("ĳ����OK");
	_selectOkRect = RectMake(2 * WINSIZEX / 7 + 84, WINSIZEY / 4 + 312, _selectOkImage->getFrameWidth(),
		_selectOkImage->getFrameHeight());

	return S_OK;
}

void selectScene::release(void)
{

}

void selectScene::update(void)
{
	for (int i = 0; i < 3; i++)
	{
		if (PtInRect(&_charCardRC[i], _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_nowCharIndex = i;
		}
	}

	switch (_nowCharIndex)
	{
	case 0:
		if (0.15f + _frameCount <= TIMEMANAGER->getWorldTime())
		{
			_frameCount = TIMEMANAGER->getWorldTime();
			if (_chaWait[1]->getFrameX() >= _chaWait[1]->getMaxFrameX())
			{
				_chaWait[1]->setFrameX(0);
				return;
			}
			_chaWait[1]->setFrameX(_chaWait[1]->getFrameX() + 1);
		}
		break;
	default:
		if (0.2f + _frameCount <= TIMEMANAGER->getWorldTime())
		{
			_frameCount = TIMEMANAGER->getWorldTime();
			if (_chaWait[0]->getFrameX() >= _chaWait[0]->getMaxFrameX())
			{
				_chaWait[0]->setFrameX(0);
				return;
			}
			_chaWait[0]->setFrameX(_chaWait[0]->getFrameX() + 1);
		}
		break;
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{
		if (PtInRect(&_selectBackRect, _ptMouse))
		{
			clickSound();
			_sceneType = TITLE;
		}
		else if (PtInRect(&_selectOkRect, _ptMouse) && _nowCharIndex == 0)
		{
			_sceneType = MAIN;
			clickSound();
			SOUNDMANAGER->stop("�⺻���");
			SOUNDMANAGER->play("�����Ҷ�", 0.7f);
			SOUNDMANAGER->soundFadeIn("�κ��", 0.5f);
		}
	}

	if (PtInRect(&_selectBackRect, _ptMouse))
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) _selectBackImage->setFrameY(2);
		else _selectBackImage->setFrameY(1);
	}
	else _selectBackImage->setFrameY(0);

	if (PtInRect(&_selectOkRect, _ptMouse))
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)) _selectOkImage->setFrameY(2);
		else _selectOkImage->setFrameY(1);
	}
	else _selectOkImage->setFrameY(0);

	_selectBackRect = RectMake(2 * WINSIZEX / 7 + 23, WINSIZEY / 4 + 313, _selectBackImage->getFrameWidth(),
		_selectBackImage->getFrameHeight());
	_selectOkRect = RectMake(2 * WINSIZEX / 7 + 85, WINSIZEY / 4 + 313, _selectOkImage->getFrameWidth(),
		_selectOkImage->getFrameHeight());
}

void selectScene::render(void)
{
	_bg->render(getMemDC(), 0, 0);
	
	_selectButton->render(getMemDC(), 2 * WINSIZEX / 7, WINSIZEY / 4);

	for (int i = 0; i < 3; i++)
	{
		if (i == _nowCharIndex) continue;

		_closeCharCard[i]->render(getMemDC(), _charCardRC[i].left + 2, _charCardRC[i].top + 14);
	}

	_nowChar->render(getMemDC(), _charCardRC[_nowCharIndex].left, _charCardRC[_nowCharIndex].top);
	
	char str[128];
	_openCharCard->render(getMemDC(), _charCardRC[0].left + 2, _charCardRC[0].top + 14);
	fontRender("NtreevSoft", _playerManagerLink->getPlayer()->getName(), 15, 1, _charCardRC[0].left + 45,
		_charCardRC[0].top + 25, RGB(255, 255, 255));
	fontRender("NtreevSoft", "TYPE : �ŷ���", 15, 1, _charCardRC[0].left + 25, _charCardRC[0].top + 160, RGB(0, 0, 0));
	fontRender("NtreevSoft", "JOB : ��", 15, 1, _charCardRC[0].left + 25, _charCardRC[0].top + 180, RGB(0, 0, 0));
	sprintf(str, "LV : %d", _playerManagerLink->getPlayer()->getLv());
	fontRender("NtreevSoft", str, 15, 1, _charCardRC[0].left + 25, _charCardRC[0].top + 200, RGB(0, 0, 0));
	sprintf(str, "%d G", _playerManagerLink->getPlayer()->getMoney());
	fontRender("NtreevSoft", str, 15, 1, _charCardRC[0].left + 90, _charCardRC[0].top + 220, RGB(0, 0, 0));

	switch (_nowCharIndex)
	{
	case 0:
		_chaWait[1]->frameRender(getMemDC(), _charCardRC[0].left + 65, _charCardRC[0].top + 64,
			_chaWait[1]->getFrameX(), _chaWait[1]->getFrameY());
		break;
	default:
		_chaWait[0]->frameRender(getMemDC(), _charCardRC[0].left + 45, _charCardRC[0].top + 104,
			_chaWait[0]->getFrameX(), _chaWait[0]->getFrameY());
		break;
	}

	_selectBackImage->frameRender(getMemDC(), _selectBackRect.left, _selectBackRect.top, _selectBackImage->getFrameX(), _selectBackImage->getFrameY());
	_selectOkImage->frameRender(getMemDC(), _selectOkRect.left, _selectOkRect.top, _selectOkImage->getFrameX(), _selectOkImage->getFrameY());
}