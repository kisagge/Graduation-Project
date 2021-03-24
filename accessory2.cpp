#include "stdafx.h"
#include "accessory2.h"


accessory2::accessory2()
{
}


accessory2::~accessory2()
{
}

HRESULT accessory2::init(int x, int y)
{
	_iconImg = IMAGEMANAGER->findImage("�Ǽ�2");
	_iconX = x;
	_iconY = y;
	_iconRc = RectMake(_iconX, _iconY, _iconImg->getWidth(), _iconImg->getHeight());

	_desCripImg = IMAGEMANAGER->findImage("�Ǽ�2Ȯ��");
	_desX = _iconX;
	_desY = _iconY - _desCripImg->getHeight();
	_desRC = RectMake(_desX, _desY, _desCripImg->getWidth(), _desCripImg->getHeight());

	sprintf(_itemName, "���� ����");
	sprintf(_description, "������ ��Ʈ��� ����. �ſ� �����ϰ� ������.");

	this->setInitValue();

	_weight = 10;

	_wtUp = 7;
	_lkUp = 10;
	_mpUp = 70;
	_hvUp = 10;

	_boughtPrice = 1000;
	_sellPrice = _boughtPrice / 2;

	_itemkind = ITEM_ACCESSORY;
	_itemlist = ITEM_ACCESSORY_2;

	_itemInfoShow = IMAGEMANAGER->findImage("����������ǥ��");

	_requiredLv = 5;

	return S_OK;
}

void accessory2::release(void)
{

}

void accessory2::update(void)
{
	this->setItemWhere();
}

void accessory2::render(void)
{

}