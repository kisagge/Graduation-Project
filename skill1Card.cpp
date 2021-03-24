#include "stdafx.h"
#include "skill1Card.h"


skill1Card::skill1Card()
{
}


skill1Card::~skill1Card()
{
}

HRESULT skill1Card::init(int x, int y)
{
	_iconImg = IMAGEMANAGER->findImage("스킬1카드");
	_iconX = x;
	_iconY = y;
	_iconRc = RectMake(_iconX, _iconY, _iconImg->getWidth(), _iconImg->getHeight());

	_desCripImg = IMAGEMANAGER->findImage("스킬1확대");
	_desX = _iconX;
	_desY = _iconY - _desCripImg->getHeight();
	_desRC = RectMake(_desX, _desY, _desCripImg->getWidth(), _desCripImg->getHeight());

	sprintf(_itemName, "일격 스킬 카드");
	sprintf(_description, "사용하면 일격 스킬을 습득한다.");

	this->setInitValue();

	_weight = 1;

	_boughtPrice = 500;
	_sellPrice = _boughtPrice / 2;

	_itemkind = ITEM_SKILLCARD;
	_itemlist = ITEM_SKILLCARD_1;

	_itemInfoShow = IMAGEMANAGER->findImage("아이템정보표시");

	_requiredLv = 1;

	return S_OK;
}

void skill1Card::release(void)
{

}

void skill1Card::update(void)
{
	this->setItemWhere();
}

void skill1Card::render(void)
{

}