#include "stdafx.h"
#include "shield2.h"


shield2::shield2()
{
}


shield2::~shield2()
{
}

HRESULT shield2::init(int x, int y)
{
	_iconImg = IMAGEMANAGER->findImage("방패2");
	_iconX = x;
	_iconY = y;
	_iconRc = RectMake(_iconX, _iconY, _iconImg->getWidth(), _iconImg->getHeight());

	_desCripImg = IMAGEMANAGER->findImage("방패2확대");
	_desX = _iconX;
	_desY = _iconY - _desCripImg->getHeight();
	_desRC = RectMake(_desX, _desY, _desCripImg->getWidth(), _desCripImg->getHeight());

	sprintf(_itemName, "철제 방패");
	sprintf(_description, "철로 만든 방패. 낡았지만 쓸 만하다.");

	this->setInitValue();

	_weight = 20;

	_hpUp = 60;
	_dpUp = 20;

	_boughtPrice = 1000;
	_sellPrice = _boughtPrice / 2;

	_itemkind = ITEM_SHIELD;
	_itemlist = ITEM_SHIELD_2;

	_itemInfoShow = IMAGEMANAGER->findImage("아이템정보표시");

	_requiredLv = 5;

	return S_OK;
}

void shield2::release(void)
{

}

void shield2::update(void)
{
	this->setItemWhere();
}

void shield2::render(void)
{

}
