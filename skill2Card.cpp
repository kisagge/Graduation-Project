#include "stdafx.h"
#include "skill2Card.h"


skill2Card::skill2Card()
{
}


skill2Card::~skill2Card()
{
}

HRESULT skill2Card::init(int x, int y)
{
	_iconImg = IMAGEMANAGER->findImage("스킬2카드");
	_iconX = x;
	_iconY = y;
	_iconRc = RectMake(_iconX, _iconY, _iconImg->getWidth(), _iconImg->getHeight());

	_desCripImg = IMAGEMANAGER->findImage("스킬2확대");
	_desX = _iconX;
	_desY = _iconY - _desCripImg->getHeight();
	_desRC = RectMake(_desX, _desY, _desCripImg->getWidth(), _desCripImg->getHeight());

	sprintf(_itemName, "유연한 허리 스킬 카드");
	sprintf(_description, "사용하면 유연한 허리 스킬을 습득한다.");

	this->setInitValue();

	_weight = 1;

	_boughtPrice = 700;
	_sellPrice = _boughtPrice / 2;

	_itemkind = ITEM_SKILLCARD;
	_itemlist = ITEM_SKILLCARD_2;

	_itemInfoShow = IMAGEMANAGER->findImage("아이템정보표시");

	_requiredLv = 5;

	return S_OK;
}

void skill2Card::release(void)
{

}

void skill2Card::update(void)
{
	this->setItemWhere();
}

void skill2Card::render(void)
{

}