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
	_iconImg = IMAGEMANAGER->findImage("����1");
	_iconX = x;
	_iconY = y;
	_iconRc = RectMake(_iconX, _iconY, _iconImg->getWidth(), _iconImg->getHeight());

	_desCripImg = IMAGEMANAGER->findImage("����1Ȯ��");
	_desX = _iconX;
	_desY = _iconY - _desCripImg->getHeight();
	_desRC = RectMake(_desX, _desY, _desCripImg->getWidth(), _desCripImg->getHeight());
	
	sprintf(_itemName, "���� ��");
	sprintf(_description, "������ ���� Į. �̰ɷ� �� �� �� �ֳ�...");

	this->setInitValue();

	_weight = 10;

	_apUp = 3;
	_acUp = 1;
	_dxUp = 3;

	_boughtPrice = 100;
	_sellPrice = _boughtPrice / 2;

	_itemkind = ITEM_WEAPON;
	_itemlist = ITEM_WEAPON_1;

	_itemInfoShow = IMAGEMANAGER->findImage("����������ǥ��");

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