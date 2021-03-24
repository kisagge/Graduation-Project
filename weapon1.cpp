#include "stdafx.h"
#include "weapon1.h"


weapon1::weapon1()
{
}


weapon1::~weapon1()
{
}

HRESULT weapon1::init(int x, int y)
{
	_iconImg = IMAGEMANAGER->findImage("무기1");
	_iconX = x;
	_iconY = y;
	_iconRc = RectMake(_iconX, _iconY, _iconImg->getWidth(), _iconImg->getHeight());

	_desCripImg = IMAGEMANAGER->findImage("무기1확대");
	_desX = _iconX;
	_desY = _iconY - _desCripImg->getHeight();
	_desRC = RectMake(_desX, _desY, _desCripImg->getWidth(), _desCripImg->getHeight());
	
	sprintf(_itemName, "나무 검");
	sprintf(_description, "나무로 만든 칼. 이걸로 뭘 할 수 있나...");

	this->setInitValue();

	_weight = 10;

	_apUp = 3;
	_acUp = 1;
	_dxUp = 3;

	_boughtPrice = 100;
	_sellPrice = _boughtPrice / 2;

	_itemkind = ITEM_WEAPON;
	_itemlist = ITEM_WEAPON_1;

	_itemInfoShow = IMAGEMANAGER->findImage("아이템정보표시");

	_requiredLv = 1;

	return S_OK;
}

void weapon1::release(void)
{

}

void weapon1::update(void)
{
	this->setItemWhere();
}

void weapon1::render(void)
{

}