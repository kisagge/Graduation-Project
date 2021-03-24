#include "stdafx.h"
#include "skill3Card.h"


skill3Card::skill3Card()
{
}


skill3Card::~skill3Card()
{
}

HRESULT skill3Card::init(int x, int y)
{
	_iconImg = IMAGEMANAGER->findImage("��ų3ī��");
	_iconX = x;
	_iconY = y;
	_iconRc = RectMake(_iconX, _iconY, _iconImg->getWidth(), _iconImg->getHeight());

	_desCripImg = IMAGEMANAGER->findImage("��ų3Ȯ��");
	_desX = _iconX;
	_desY = _iconY - _desCripImg->getHeight();
	_desRC = RectMake(_desX, _desY, _desCripImg->getWidth(), _desCripImg->getHeight());

	sprintf(_itemName, "���� ����");
	sprintf(_description, "����ϸ� ���� ���� ��ų�� �����Ѵ�.");

	this->setInitValue();

	_weight = 1;

	_boughtPrice = 1000;
	_sellPrice = _boughtPrice / 2;

	_itemkind = ITEM_SKILLCARD;
	_itemlist = ITEM_SKILLCARD_3;

	_itemInfoShow = IMAGEMANAGER->findImage("����������ǥ��");

	_requiredLv = 10;

	return S_OK;
}

void skill3Card::release(void)
{

}

void skill3Card::update(void)
{
	this->setItemWhere();
}

void skill3Card::render(void)
{

}
