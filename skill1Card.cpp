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
	_iconImg = IMAGEMANAGER->findImage("��ų1ī��");
	_iconX = x;
	_iconY = y;
	_iconRc = RectMake(_iconX, _iconY, _iconImg->getWidth(), _iconImg->getHeight());

	_desCripImg = IMAGEMANAGER->findImage("��ų1Ȯ��");
	_desX = _iconX;
	_desY = _iconY - _desCripImg->getHeight();
	_desRC = RectMake(_desX, _desY, _desCripImg->getWidth(), _desCripImg->getHeight());

	sprintf(_itemName, "�ϰ� ��ų ī��");
	sprintf(_description, "����ϸ� �ϰ� ��ų�� �����Ѵ�.");

	this->setInitValue();

	_weight = 1;

	_boughtPrice = 500;
	_sellPrice = _boughtPrice / 2;

	_itemkind = ITEM_SKILLCARD;
	_itemlist = ITEM_SKILLCARD_1;

	_itemInfoShow = IMAGEMANAGER->findImage("����������ǥ��");

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