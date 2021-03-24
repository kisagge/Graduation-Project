#include "stdafx.h"
#include "shop.h"
#include "playerManager.h"

shop::shop()
{
}


shop::~shop()
{
}

HRESULT shop::init(void)
{
	_shopWindow = IMAGEMANAGER->findImage("상점구입창");
	_sellWindow = IMAGEMANAGER->findImage("상점판매창");
	_shopExitImage = IMAGEMANAGER->findImage("창끄기");
	_shopX = SHOPINITX;
	_shopY = SHOPINITY;
	_exitFrame = 0;
	_nowShopPage = 1;
	_shopOn = false;

	_showStart = 0;
	_showEnd = 7;
	
	_shopUpDownButton[0] = RectMake(_shopX + 338, _shopY + 43, 13, 9);
	_shopUpDownButton[1] = RectMake(_shopX + 338, _shopY + 336, 13, 9);

	_sellEquipList.push_back(ITEMDB->findItem("무기_1"));
	_sellEquipList.push_back(ITEMDB->findItem("무기_2"));
	_sellEquipList.push_back(ITEMDB->findItem("무기_3"));
	_sellEquipList.push_back(ITEMDB->findItem("모자_1"));
	_sellEquipList.push_back(ITEMDB->findItem("모자_2"));
	_sellEquipList.push_back(ITEMDB->findItem("모자_3"));
	_sellEquipList.push_back(ITEMDB->findItem("방패_1"));
	_sellEquipList.push_back(ITEMDB->findItem("방패_2"));
	_sellEquipList.push_back(ITEMDB->findItem("방패_3"));
	_sellEquipList.push_back(ITEMDB->findItem("악세_1"));
	_sellEquipList.push_back(ITEMDB->findItem("악세_2"));
	_sellEquipList.push_back(ITEMDB->findItem("악세_3"));
	_sellEquipList.push_back(ITEMDB->findItem("드릴_1"));
	_sellEquipList.push_back(ITEMDB->findItem("드릴_2"));
	_sellEquipList.push_back(ITEMDB->findItem("드릴_3"));

	_sellSpendList.push_back(ITEMDB->findItem("포션_1"));
	_sellSpendList.push_back(ITEMDB->findItem("포션_2"));
	_sellSpendList.push_back(ITEMDB->findItem("스킬카드_1"));
	_sellSpendList.push_back(ITEMDB->findItem("스킬카드_2"));
	_sellSpendList.push_back(ITEMDB->findItem("스킬카드_3"));

	_buyEquipCheck = new int[_sellEquipList.size()];
	_buySpendCheck = new int[_sellSpendList.size()];

	for (int i = 0; i < _sellEquipList.size(); i++)
	{
		_buyEquipCheck[i] = 0;
	}

	for (int i = 0; i < _sellSpendList.size(); i++)
	{
		_buySpendCheck[i] = 0;
	}

	return S_OK;
}

void shop::release(void)
{
	for (int i = 0; i < _sellEquipList.size(); i++)
	{
		_sellEquipList[i]->release();
		SAFE_DELETE(_sellEquipList[i]);
	}

	for (int i = 0; i < _sellSpendList.size(); i++)
	{
		_sellSpendList[i]->release();
		SAFE_DELETE(_sellSpendList[i]);
	}

	for (int i = 0; i < _buyList.size(); i++)
	{
		_buyList[i]->release();
		SAFE_DELETE(_buyList[i]);
	}

	for (int i = 0; i < _soldList.size(); i++)
	{
		_soldList[i]->release();
		SAFE_DELETE(_soldList[i]);
	}

	delete _buyEquipCheck;
	delete _buySpendCheck;

	_sellEquipList.clear();
	_sellSpendList.clear();
	_buyList.clear();
	_soldList.clear();
}

void shop::update(void)
{
	if (!_shopOn) return;

	shopSettingWindow();
	shopSetItemLocation();
	shopEquipUpDoWn();
	shopManageMent();
	purchaseManagement();
	sellManagement();
	sellUpDown();
}

void shop::render(void)
{
	shopRender(_shopOn, _nowShopPage);
}

void shop::shopOpenAndClose(void)
{
	if (KEYMANAGER->isOnceKeyDown('U'))
	{
		clickSound();
		if (_shopOn)
		{
			if (_nowShopPage == 0 || _nowShopPage == 1)
				_shopOn = false;
		}
		else
		{
			_nowShopPage = 1;
			_shopOn = true;
			_showStart = 0;
			_showEnd = 7;
			for (int i = 0; i < _sellEquipList.size(); i++)
				_buyEquipCheck[i] = 0;

			for (int i = 0; i < _sellSpendList.size(); i++)
				_buySpendCheck[i] = 0;
		}
	}
	else if (KEYMANAGER->isOnceKeyDown('Y'))
	{
		clickSound();
		if (_shopOn)
		{
			if (_nowShopPage == 2)
			{
				for (int i = 0; i < _soldList.size(); i++)
				{
					_soldList[i]->release();
					SAFE_DELETE(_soldList[i]);
				}
				_soldList.clear();
				_shopOn = false;
			}
		}
		else
		{
			_nowShopPage = 2;
			_shopOn = true;
			_showStart = 0;
			_showEnd = 7;

			for (int i = 0; i < _playerManagerLink->getPlayer()->getInventorySize(); i++)
			{
				_soldList.push_back(ITEMDB->returnItemUsingEnum(_playerManagerLink->getPlayer()->getInvenItem(i)->getItemlist()));
			}
		}
	}
}

//상점 윈도우 위치 잡아주기
void shop::shopSettingWindow(void)
{
	if (!_shopOn) return;

	//상점 전체 렉트
	_shopRect = RectMake(_shopX, _shopY, _shopWindow->getFrameWidth(), 
		_shopWindow->getFrameHeight());
	//상점 나가기
	_shopExitButton = RectMake(_shopX + 335, _shopY + 5, _shopExitImage->getFrameWidth(), _shopExitImage->getFrameHeight());
	_cancelButton = RectMake(_shopX + 246, _shopY + 394, 51, 18);
	switch (_nowShopPage)
	{
	case 0:
		//상점 소모품, 장비 아이템창 변경 버튼들
		_shopChangeButton[0] = RectMake(_shopX + 12, _shopY + 24, 29, 18);
		_shopChangeButton[1] = RectMake(_shopX + 41, _shopY + 24, 39, 18);

		_buyButton = RectMake(_shopX + 208, _shopY + 394, 36, 18);

		for (int i = 0; i < 8; i++)
		{
			_numDownButton[i] = RectMake(_shopX + 274, _shopY + 83 + 34 * i, 12, 17);
			_numUpButton[i] = RectMake(_shopX + 319, _shopY + 83 + 34 * i, 12, 17);
		}
		break;
	case 1:
		//상점 소모품, 장비 아이템창 변경 버튼들
		_shopChangeButton[0] = RectMake(_shopX + 12, _shopY + 24, 29, 18);
		_shopChangeButton[1] = RectMake(_shopX + 41, _shopY + 24, 39, 18);

		//
		_shopUpDownButton[0] = RectMake(_shopX + 338, _shopY + 40, 13, 15);
		_shopUpDownButton[1] = RectMake(_shopX + 338, _shopY + 333, 13, 15);

		//상점 구입, 취소 버튼
		_buyButton = RectMake(_shopX + 208, _shopY + 394, 36, 18);

		for (int i = 0; i < 8; i++)
		{
			_numDownButton[i] = RectMake(_shopX + 274, _shopY + 83 + 34 * i, 12, 17);
			_numUpButton[i] = RectMake(_shopX + 319, _shopY + 83 + 34 * i, 12, 17);
		}

		break;
	case 2:
		_shopUpDownButton[0] = RectMake(_shopX + 338, _shopY + 40, 13, 15);
		_shopUpDownButton[1] = RectMake(_shopX + 338, _shopY + 333, 13, 15);

		_sellButton = RectMake(_shopX + 210, _shopY + 394, 34, 18);
		break;
	}
}

//상점 아이템 위치 잡아주기
void shop::shopSetItemLocation(void)
{
	if (!_shopOn) return;

	switch (_nowShopPage)
	{
	//소모품 판매
	case 0:
		for (int i = _showStart; i <= _showEnd; i++)
		{
			if (_sellSpendList.size() <= i) return;
			_sellSpendList[i]->setIconX(_shopX + 15);
			_sellSpendList[i]->setIconY(_shopY + 82 + 34 * (i - _showStart));
			_sellSpendList[i]->update();
		}
		break;
	//장비품 판매
	case 1:
		for (int i = _showStart; i <= _showEnd; i++)
		{
			if (_sellEquipList.size() <= i) return;
			_sellEquipList[i]->setIconX(_shopX + 15);
			_sellEquipList[i]->setIconY(_shopY + 82 + 34 * (i - _showStart));
			_sellEquipList[i]->update();
		}
		break;
	case 2:
		if (!_shopOn) return;

		for (int i = _showStart; i <= _showEnd; i++)
		{
			if (_soldList.size() <= i) return;
			_soldList[i]->setIconX(_shopX + 15);
			_soldList[i]->setIconY(_shopY + 83 + 34 * (i - _showStart));
			_soldList[i]->update();
		}
		break;
	}

}

void shop::shopEquipUpDoWn(void)
{
	if (!_shopOn) return;

	if (_nowShopPage == 1)
	{
		//딜레이키
		_btnDelay -= TIMEMANAGER->getElapsedTime();
		if (_btnDelay < 0) _btnDelay = 0;
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON)
			&& PtInRect(&_shopUpDownButton[0], _ptMouse)
			&& _showStart > 0 && _btnDelay == 0)
		{
			_btnDelay = 1.0f;
			_showStart--;
			_showEnd--;
			clickSound();
		}

		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && PtInRect(&_shopUpDownButton[1], _ptMouse)
			&& _showEnd < _sellEquipList.size() - 1 && _btnDelay == 0)
		{
			_btnDelay = 1.0f;
			_showStart++;
			_showEnd++;
			clickSound();
		}
	}
}

//상점 구입 관련 처리
void shop::shopManageMent(void)
{
	if (!_shopOn) return;

	switch (_nowShopPage)
	{
	case 0:
		if (PtInRect(&_shopChangeButton[1], _ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			clickSound();
			_nowShopPage = 1;
			for (int i = 0; i < _sellEquipList.size(); i++)
			{
				_buyEquipCheck[i] = 0;
			}
			_showStart = 0;
			_showEnd = 7;
		}
		//딜레이키
		_btnDelay -= TIMEMANAGER->getElapsedTime();
		if (_btnDelay < 0) _btnDelay = 0;
		if (PtInRect(&_buyButton, _ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON)
			&& _btnDelay == 0)
		{
			_btnDelay = 1.2f;
			buyManagement();
		}
		break;
	case 1:
		if (PtInRect(&_shopChangeButton[0], _ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			clickSound();
			_nowShopPage = 0;
			for (int i = 0; i < _sellSpendList.size(); i++)
			{
				_buySpendCheck[i] = 0;
			}
			_showStart = 0;
			_showEnd = 7;
		}

		_btnDelay -= TIMEMANAGER->getElapsedTime();
		if (_btnDelay < 0) _btnDelay = 0;
		if (PtInRect(&_buyButton, _ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON)
			&& _btnDelay == 0)
		{
			_btnDelay = 1.2f;
			buyManagement();
		}
		break;
	case 2:
		break;
	}

	if (PtInRect(&_shopExitButton, _ptMouse))
	{
		_exitFrame = 1;
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			_exitFrame = 2;
			_shopOn = false;
			if (SOUNDMANAGER->isPlaySound("창닫기"))
			{
				SOUNDMANAGER->stop("창닫기");
				SOUNDMANAGER->play("창닫기", 0.5f);
			}
			else SOUNDMANAGER->play("창닫기", 0.5f);
		}
	}
	else _exitFrame = 0;
}

void shop::purchaseManagement(void)
{
	if (!_shopOn) return;

	if (_nowShopPage == 2) return;

	if (_nowShopPage == 0)
	{
		for (int i = _showStart; i <= _showEnd; i++)
		{
			//딜레이키
			_btnDelay -= TIMEMANAGER->getElapsedTime();
			if (_btnDelay < 0) _btnDelay = 0;
			if (PtInRect(&_numUpButton[i - _showStart], _ptMouse)
				&& KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _btnDelay == 0)
			{
				_btnDelay = 1.0f;
				_buySpendCheck[i]++;
				clickSound();
			}

			if (PtInRect(&_numDownButton[i - _showStart], _ptMouse)
				&& KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _btnDelay == 0)
			{
				_btnDelay = 1.0f;
				if (_buySpendCheck[i] > 0)
					_buySpendCheck[i]--;
				clickSound();
			}
		}

		_btnDelay -= TIMEMANAGER->getElapsedTime();
		if (_btnDelay < 0) _btnDelay = 0;
		if (PtInRect(&_cancelButton, _ptMouse)
			&& KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _btnDelay == 0)
		{
			_btnDelay = 1.0f;
			for (int i = 0; i < _sellSpendList.size(); i++)
			{
				_buySpendCheck[i] = 0;
			}
		}

	}
	else if (_nowShopPage == 1)
	{
		for (int i = _showStart; i <= _showEnd; i++)
		{
			//딜레이키
			_btnDelay -= TIMEMANAGER->getElapsedTime();
			if (_btnDelay < 0) _btnDelay = 0;
			if (PtInRect(&_numUpButton[i - _showStart], _ptMouse)
				&& KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _btnDelay == 0)
			{
				_btnDelay = 1.0f;
				_buyEquipCheck[i]++;
				clickSound();
			}

			if (PtInRect(&_numDownButton[i - _showStart], _ptMouse)
				&& KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _btnDelay == 0)
			{
				_btnDelay = 1.0f;
				if (_buyEquipCheck[i] > 0)
					_buyEquipCheck[i]--;
				clickSound();
			}
		}

		_btnDelay -= TIMEMANAGER->getElapsedTime();
		if (_btnDelay < 0) _btnDelay = 0;
		if (PtInRect(&_cancelButton, _ptMouse)
			&& KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _btnDelay == 0)
		{
			_btnDelay = 1.0f;
			for (int i = 0; i < _sellEquipList.size(); i++)
			{
				_buyEquipCheck[i] = 0;
			}
		}
	}
}

int shop::returnMoneyPurchase(void)
{
	int k = 0;

	switch (_nowShopPage)
	{
	case 0:
		for (int i = 0; i < _sellSpendList.size(); i++)
		{
			k += _sellSpendList[i]->getBoughtPrice() * _buySpendCheck[i];
		}
		break;
	case 1:
		for (int i = 0; i < _sellEquipList.size(); i++)
		{
			k += _sellEquipList[i]->getBoughtPrice() * _buyEquipCheck[i];
		}
		break;
	}

	return k;
}

int shop::returnWeightPurchase(void)
{
	int k = 0;

	switch (_nowShopPage)
	{
	case 0:
		for (int i = 0; i < _sellSpendList.size(); i++)
		{
			k += _sellSpendList[i]->getWeight() * _buySpendCheck[i];
		}
		break;
	case 1:
		for (int i = 0; i < _sellEquipList.size(); i++)
		{
			k += _sellEquipList[i]->getWeight() * _buyEquipCheck[i];
		}
		break;
	}

	return k;
}

void shop::buyManagement(void)
{
	if (!_shopOn) return;

	if (returnMoneyPurchase() > _playerManagerLink->getPlayer()->getMoney()) return;

	int k = 0;

	if (_nowShopPage == 0)
	{
		for (int i = 0; i < _sellSpendList.size(); i++)
		{
			k += _buySpendCheck[i];
		}

		if (_playerManagerLink->getPlayer()->getInventorySize() + k
		> _playerManagerLink->getPlayer()->getInvenMaxSize()) return;

		for (int i = 0; i < _sellSpendList.size(); i++)
		{
			for (int j = 0; j < _buySpendCheck[i]; j++)
			{
				_playerManagerLink->getPlayer()->pushBackItem(ITEMDB->returnItemUsingEnum(_sellSpendList[i]->getItemlist()));
			}
		}

		_playerManagerLink->getPlayer()->setMoney(_playerManagerLink->getPlayer()->getMoney()
			- returnMoneyPurchase());
		SOUNDMANAGER->play("구입소리", 0.5f);
		for (int i = 0; i < _sellSpendList.size(); i++)
		{
			_buySpendCheck[i] = 0;
		}
	}
	else if (_nowShopPage == 1)
	{
		for (int i = 0; i < _sellEquipList.size(); i++)
		{
			k += _buyEquipCheck[i];
		}

		if (_playerManagerLink->getPlayer()->getInventorySize() + k
		> _playerManagerLink->getPlayer()->getInvenMaxSize()) return;

		for (int i = 0; i < _sellEquipList.size(); i++)
		{
			for (int j = 0; j < _buyEquipCheck[i]; j++)
			{
				_playerManagerLink->getPlayer()->pushBackItem(ITEMDB->returnItemUsingEnum(_sellEquipList[i]->getItemlist()));
			}
		}

		_playerManagerLink->getPlayer()->setMoney(_playerManagerLink->getPlayer()->getMoney()
			- returnMoneyPurchase());
		SOUNDMANAGER->play("구입소리", 0.5f);
		for (int i = 0; i < _sellEquipList.size(); i++)
		{
			_buyEquipCheck[i] = 0;
		}
	}
}

void shop::sellManagement(void)
{
	if (!_shopOn) return;

	if (!_nowShopPage == 2) return;

	_btnDelay -= TIMEMANAGER->getElapsedTime();
	if (_btnDelay < 0) _btnDelay = 0;
	for (int i = 0; i < _soldList.size(); i++)
	{
		if (PtInRect(&_soldList[i]->getIconRC(), _ptMouse)
			&& KEYMANAGER->isStayKeyDown(VK_RBUTTON) && _btnDelay == 0)
		{ 
			_btnDelay = 1.0f;
			_playerManagerLink->getPlayer()->setMoney(
				_playerManagerLink->getPlayer()->getMoney() + _soldList[i]->getSellPrice());
			_playerManagerLink->getPlayer()->eraseItem(i);
			_soldList.erase(_soldList.begin() + i);
			SOUNDMANAGER->play("판매소리", 0.5f);
			return;
		}
	}
}

void shop::sellUpDown(void)
{
	if (!_shopOn) return;

	if (!_nowShopPage == 2) return;

	_sellBtnDelay -= TIMEMANAGER->getElapsedTime();
	if (_sellBtnDelay < 0) _sellBtnDelay = 0;

	if (PtInRect(&_shopUpDownButton[0], _ptMouse)
		&& KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _sellBtnDelay == 0 && _showStart > 0)
	{
		_sellBtnDelay = 1.0f;
		_showStart--;
		_showEnd--;
	}
	else if (PtInRect(&_shopUpDownButton[1], _ptMouse)
		&& KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _sellBtnDelay == 0 && _showEnd < _playerManagerLink->getPlayer()->getInventorySize())
	{
		_sellBtnDelay = 1.0f;
		_showStart++;
		_showEnd++;
	}

}

//상점 렌더
void shop::shopRender(bool shopOn, int shopPage)
{
	char str[128];
	if (_shopOn)
	{
		switch (_nowShopPage)
		{
		case 0:
			shopBuyShopRender();
			shopSpendItemRender();
			sprintf(str, "%d", returnWeightPurchase());
			fontCameraRender("NtreevSoft", str, 14, 1, _shopX + 348 - strlen(str) * 8, _shopY + 353, RGB(0, 0, 0));
			sprintf(str, "%d", returnMoneyPurchase());
			fontCameraRender("NtreevSoft", str, 14, 1, _shopX + 348 - strlen(str) * 8, _shopY + 374, RGB(0, 0, 0));
			break;
		case 1:
			shopBuyShopRender();
			shopEquipItemRender();
			sprintf(str, "%d", returnWeightPurchase());
			fontCameraRender("NtreevSoft", str, 14, 1, _shopX + 348 - strlen(str) * 8, _shopY + 353, RGB(0, 0, 0));
			sprintf(str, "%d", returnMoneyPurchase());
			fontCameraRender("NtreevSoft", str, 14, 1, _shopX + 348 - strlen(str) * 8, _shopY + 374, RGB(0, 0, 0));
			break;
		case 2:
			shopSellShopRender();
			break;
		}
		_shopExitImage->frameRender(getCameraDC(), _shopExitButton.left, _shopExitButton.top, 0, _exitFrame);
		sprintf(str, "%d", _playerManagerLink->getPlayer()->getWeight());
		fontCameraRender("NtreevSoft", str, 14, 1, _shopX + 176 - strlen(str)*8, _shopY + 353, RGB(0, 0, 0));
		sprintf(str, "%d", _playerManagerLink->getPlayer()->getMoney());
		fontCameraRender("NtreevSoft", str, 14, 1, _shopX + 176 - strlen(str)*8, _shopY + 374, RGB(0, 0, 0));
	}
	else return;
}

void shop::shopBuyShopRender(void)
{
	switch (_nowShopPage)
	{
	case 0:
		_shopWindow->frameRender(getCameraDC(), _shopX, _shopY, 0, _nowShopPage);
		break;
	case 1:
		_shopWindow->frameRender(getCameraDC(), _shopX, _shopY, 0, _nowShopPage);
		break;
	case 2:
		break;
		_sellWindow->render(getCameraDC(), _shopX, _shopY);
	}
}

void shop::shopSellShopRender(void)
{
	_sellWindow->render(getCameraDC(), _shopX, _shopY);
	char str[128];
	for (int i = _showStart; i <= _showEnd; i++)
	{
		if (_soldList.size() <= i) return;
		_soldList[i]->iconRender();
		fontCameraRender("NtreevSoft", _soldList[i]->getItemName(), 14, 1, _shopX + 76, _soldList[i]->getIconY() + 4, RGB(0, 0, 0));
		sprintf(str, "%d", _soldList[i]->getSellPrice());
		fontCameraRender("NtreevSoft", str, 14, 1, _shopX + 176, _soldList[i]->getIconY() + 4, RGB(0, 0, 0));
	}
}

void shop::shopEquipItemRender(void)
{
	char str[128];
	for (int i = _showStart; i <= _showEnd; i++)
	{
		if (_sellEquipList.size() <= i) return;
		_sellEquipList[i]->iconRender();
		fontCameraRender("NtreevSoft", _sellEquipList[i]->getItemName(), 14, 1,
			_sellEquipList[i]->getIconX() + 60, _sellEquipList[i]->getIconY() + 5, RGB(0, 0, 0));
		sprintf(str, "%d", _sellEquipList[i]->getBoughtPrice());
		fontCameraRender("NtreevSoft", str, 14, 1,
			_sellEquipList[i]->getIconX() + 170, _sellEquipList[i]->getIconY() + 5, RGB(0, 0, 0));

		int k = 0;
		for (int j = 0; j < _playerManagerLink->getPlayer()->getInventorySize(); j++)
		{
			if (_sellEquipList[i]->getItemlist() == _playerManagerLink->getPlayer()->getInvenItem(j)->getItemlist())
				k++;
		}
		sprintf(str, "%d", k);
		fontCameraRender("NtreevSoft", str, 14, 1, _sellEquipList[i]->getIconX() + 220, _sellEquipList[i]->getIconY() + 5, RGB(0, 0, 0));
		sprintf(str, "%d", _buyEquipCheck[i]);
		fontCameraRender("NtreevSoft", str, 14, 1, _sellEquipList[i]->getIconX() + 282, _sellEquipList[i]->getIconY() + 4, RGB(0, 0, 0));
	}
}

void shop::shopSpendItemRender(void)
{
	char str[128];
	for (int i = _showStart; i <= _showEnd; i++)
	{
		if (_sellSpendList.size() <= i) return;
		_sellSpendList[i]->iconRender();
		fontCameraRender("NtreevSoft", _sellSpendList[i]->getItemName(), 14, 1,
			_sellSpendList[i]->getIconX() + 60, _sellSpendList[i]->getIconY() + 5, RGB(0, 0, 0));
		sprintf(str, "%d", _sellSpendList[i]->getBoughtPrice());
		fontCameraRender("NtreevSoft", str, 14, 1,
			_sellSpendList[i]->getIconX() + 170, _sellSpendList[i]->getIconY() + 5, RGB(0, 0, 0));

		int k = 0;
		for (int j = 0; j < _playerManagerLink->getPlayer()->getInventorySize(); j++)
		{
			if (_sellSpendList[i]->getItemlist() == _playerManagerLink->getPlayer()->getInvenItem(j)->getItemlist())
				k++;
		}

		sprintf(str, "%d", k);
		fontCameraRender("NtreevSoft", str, 14, 1, _sellSpendList[i]->getIconX() + 220, _sellSpendList[i]->getIconY() + 5, RGB(0, 0, 0));
		sprintf(str, "%d", _buySpendCheck[i]);
		fontCameraRender("NtreevSoft", str, 14, 1, _sellSpendList[i]->getIconX() + 282, _sellSpendList[i]->getIconY() + 4, RGB(0, 0, 0));
	}
}