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
	_iconImg = IMAGEMANAGER->findImage("��ų2ī��");
	_iconX = x;
	_iconY = y;
	_iconRc = RectMake(_iconX, _iconY, _iconImg->getWidth(), _iconImg->getHeight());

	_desCripImg = IMAGEMANAGER->findImage("��ų2Ȯ��");
	_desX = _iconX;
	_desY = _iconY - _desCripImg->getHeight();
	_desRC = RectMake(_desX, _desY, _desCripImg->getWidth(), _desCripImg->getHeight());

	sprintf(_itemName, "������ �㸮 ��ų ī��");
	sprintf(_description, "����ϸ� ������ �㸮 ��ų�� �����Ѵ�.");

	this->setInitValue();

	_weight = 1;

	_boughtPrice = 700;
	_sellPrice = _boughtPrice / 2;

	_itemkind = ITEM_SKILLCARD;
	_itemlist = ITEM_SKILLCARD_2;

	_itemInfoShow = IMAGEMANAGER->findImage("����������ǥ��");

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