#include "stdafx.h"
#include "accessory3.h"


accessory3::accessory3()
{
}


accessory3::~accessory3()
{
}

HRESULT accessory3::init(int x, int y)
{
	_iconImg = IMAGEMANAGER->findImage("�Ǽ�3");
	_iconX = x;
	_iconY = y;
	_iconRc = RectMake(_iconX, _iconY, _iconImg->getWidth(), _iconImg->getHeight());

	_desCripImg = IMAGEMANAGER->findImage("�Ǽ�3Ȯ��");
	_desX = _iconX;
	_desY = _iconY - _desCripImg->getHeight();
	_desRC = RectMake(_desX, _desY, _desCripImg->getWidth(), _desCripImg->getHeight());

	sprintf(_itemName, "���� ����");
	sprintf(_description, "������ ����. ���� ������ �Ƿ��ִ�.");

	this->setInitValue();

	_weight = 15;

	_wtUp = 9;
	_lkUp = 15;
	_mpUp = 120;
	_hvUp = 15;

	_boughtPrice = 5000;
	_sellPrice = _boughtPrice / 2;

	_itemkind = ITEM_ACCESSORY;
	_itemlist = ITEM_ACCESSORY_3;

	_itemInfoShow = IMAGEMANAGER->findImage("����������ǥ��");

	_requiredLv = 10;

	return S_OK;
}

void accessory3::release(void)
{

}

void accessory3::update(void)
{
	this->setItemWhere();
}

void accessory3::render(void)
{

}