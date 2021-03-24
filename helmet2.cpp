#include "stdafx.h"
#include "helmet2.h"


helmet2::helmet2()
{
}


helmet2::~helmet2()
{
}

HRESULT helmet2::init(int x, int y)
{
	_iconImg = IMAGEMANAGER->findImage("����2");
	_iconX = x;
	_iconY = y;
	_iconRc = RectMake(_iconX, _iconY, _iconImg->getWidth(), _iconImg->getHeight());

	_desCripImg = IMAGEMANAGER->findImage("����2Ȯ��");
	_desX = _iconX;
	_desY = _iconY - _desCripImg->getHeight();
	_desRC = RectMake(_desX, _desY, _desCripImg->getWidth(), _desCripImg->getHeight());

	sprintf(_itemName, "������ ����");
	sprintf(_description, "�����з� ���� ����. �����ϴ�.");

	this->setInitValue();

	_weight = 10;

	_dxUp = 10;
	_dpUp = 25;
	_hvUp = 8;

	_boughtPrice = 1000;
	_sellPrice = _boughtPrice / 2;

	_itemkind = ITEM_HAT;
	_itemlist = ITEM_HAT_2;

	_itemInfoShow = IMAGEMANAGER->findImage("����������ǥ��");

	_requiredLv = 5;

	return S_OK;
}

void helmet2::release(void)
{

}

void helmet2::update(void)
{
	this->setItemWhere();
}

void helmet2::render(void)
{

}
