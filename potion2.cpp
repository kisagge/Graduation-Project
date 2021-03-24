#include "stdafx.h"
#include "potion2.h"


potion2::potion2()
{
}


potion2::~potion2()
{
}

HRESULT potion2::init(int x, int y)
{
	_iconImg = IMAGEMANAGER->findImage("포션2");
	_iconX = x;
	_iconY = y;
	_iconRc = RectMake(_iconX, _iconY, _iconImg->getWidth(), _iconImg->getHeight());

	_desCripImg = IMAGEMANAGER->findImage("포션2확대");
	_desX = _iconX;
	_desY = _iconY - _desCripImg->getHeight();
	_desRC = RectMake(_desX, _desY, _desCripImg->getWidth(), _desCripImg->getHeight());

	sprintf(_itemName, "파란 포션");
	sprintf(_description, "파란색 포션. 마시면 마나가 찬다.");

	this->setInitValue();

	_weight = 1;

	_mpUp = 150;

	_boughtPrice = 200;
	_sellPrice = _boughtPrice / 2;

	_itemkind = ITEM_SPEND;
	_itemlist = ITEM_SPEND_2;

	_itemInfoShow = IMAGEMANAGER->findImage("아이템정보표시");

	_requiredLv = 1;

	return S_OK;
}

void potion2::release(void)
{

}

void potion2::update(void)
{
	this->setItemWhere();
}

void potion2::render(void)
{

}
