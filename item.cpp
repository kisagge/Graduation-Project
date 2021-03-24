#include "stdafx.h"
#include "item.h"


item::item()
{
}


item::~item()
{
}

HRESULT item::init(void)
{
	return S_OK;
}

HRESULT item::init(int x, int y)
{
	return S_OK;
}

void item::release(void)
{

}

void item::update(void)
{

}

void item::render(void)
{

}

void item::setInitValue(void)
{
	_weight = 0;
	_hpUp = 0;
	_mpUp = 0;
	_speedUp = 0;
	_apUp = 0;
	_acUp = 0;
	_dxUp = 0;
	_wtUp = 0;
	_daUp = 0;
	_lkUp = 0;
	_dpUp = 0;
	_hvUp = 0;
	_boughtPrice = 0;
	_sellPrice = 0;
}

void item::setItemWhere(void)
{
	_iconRc = RectMake(_iconX, _iconY, _iconImg->getWidth(), _iconImg->getHeight());
	_desX = _iconX;
	_desY = _iconY - _desCripImg->getHeight() - 250;
	_desRC = RectMake(_desX, _desY, _desCripImg->getWidth(), _desCripImg->getHeight());
}

void item::iconRender(void)
{
	_iconImg->render(getCameraDC(), _iconX, _iconY);
}

void item::desRender(void)
{
	if (_desY - 56 < 0) _desY = 56;

	_itemInfoShow->alphaRender(getCameraDC(), _desX - 12, _desY - 55, 180);
	_desCripImg->render(getCameraDC(), _desX, _desY);

	char str[128];
	//ap표시
	if (_apUp > 0)
	{
		fontCameraRender("NtreevSoft", "AP", 16, 1, _desX + 114, _desY - 6, RGB(255, 255, 255));
		sprintf_s(str, "%d", _apUp);
		fontCameraRender("NtreevSoft", str, 16, 1, _desX + 154, _desY - 6, RGB(255, 255, 255));
	}
	//ac표시
	if (_acUp > 0)
	{
		fontCameraRender("NtreevSoft", "AC", 16, 1, _desX + 114, _desY + 10, RGB(255, 255, 255));
		sprintf_s(str, "%d", (int)_acUp);
		fontCameraRender("NtreevSoft", str, 16, 1, _desX + 154, _desY + 10, RGB(255, 255, 255));
	}
	//dx표시
	if (_dxUp > 0)
	{
		fontCameraRender("NtreevSoft", "DX", 16, 1, _desX + 114, _desY + 26, RGB(255, 255, 255));
		sprintf_s(str, "%d", _dxUp);
		fontCameraRender("NtreevSoft", str, 16, 1, _desX + 154, _desY + 26, RGB(255, 255, 255));
	}
	//mpUp표시
	if (_mpUp > 0)
	{
		fontCameraRender("NtreevSoft", "MP", 16, 1, _desX + 114, _desY + 42, RGB(255, 255, 255));
		sprintf_s(str, "%d", _mpUp);
		fontCameraRender("NtreevSoft", str, 16, 1, _desX + 154, _desY + 42, RGB(255, 255, 255));
	}
	//wtUp표시
	if (_wtUp > 0)
	{
		fontCameraRender("NtreevSoft", "WT", 16, 1, _desX + 114, _desY + 58, RGB(255, 255, 255));
		sprintf_s(str, "%d", _wtUp);
		fontCameraRender("NtreevSoft", str, 16, 1, _desX + 154, _desY + 58, RGB(255, 255, 255));
	}
	//daUp표시
	if (_daUp > 0)
	{
		fontCameraRender("NtreevSoft", "DA", 16, 1, _desX + 114, _desY + 74, RGB(255, 255, 255));
		sprintf_s(str, "%d", _daUp);
		fontCameraRender("NtreevSoft", str, 16, 1, _desX + 154, _desY + 74, RGB(255, 255, 255));
	}
	//lk표시
	if (_lkUp > 0)
	{
		fontCameraRender("NtreevSoft", "LK", 16, 1, _desX + 224, _desY - 6, RGB(255, 255, 255));
		sprintf_s(str, "%d", _lkUp);
		fontCameraRender("NtreevSoft", str, 16, 1, _desX + 264, _desY - 6, RGB(255, 255, 255));
	}
	//HP표시
	if (_hpUp > 0)
	{
		fontCameraRender("NtreevSoft", "HP", 16, 1, _desX + 224, _desY + 10, RGB(255, 255, 255));
		sprintf_s(str, "%d", _hpUp);
		fontCameraRender("NtreevSoft", str, 16, 1, _desX + 264, _desY + 10, RGB(255, 255, 255));
	}
	//dpUP표시
	if (_dpUp > 0)
	{
		fontCameraRender("NtreevSoft", "DP", 16, 1, _desX + 224, _desY + 26, RGB(255, 255, 255));
		sprintf_s(str, "%d", _dpUp);
		fontCameraRender("NtreevSoft", str, 16, 1, _desX + 264, _desY + 26, RGB(255, 255, 255));
	}
	//hvUp표시
	if (_hvUp > 0)
	{
		fontCameraRender("NtreevSoft", "HV", 16, 1, _desX + 224, _desY + 42, RGB(255, 255, 255));
		sprintf_s(str, "%d", _hvUp);
		fontCameraRender("NtreevSoft", str, 16, 1, _desX + 264, _desY + 42, RGB(255, 255, 255));
	}

	fontCameraRender("NtreevSoft", _itemName, 16, 1, _desX - 1, _desY - 34, RGB(255, 255, 255));
	fontCameraRender("NtreevSoft", "필요레벨", 14, 1, _desX, _desY + 119, RGB(255, 255, 255));
	sprintf_s(str, "%d", _requiredLv);
	fontCameraRender("NtreevSoft", str, 16, 1, _desX + 78, _desY + 120, RGB(255, 255, 255));
	fontCameraRender("NtreevSoft", "가격", 16, 1, _desX + 110, _desY + 120, RGB(255, 255, 255));
	sprintf_s(str, "%d", _boughtPrice);
	fontCameraRender("NtreevSoft", str, 16, 1, _desX + 170, _desY + 120, RGB(255, 255, 255));
	fontCameraRender("NtreevSoft", "무게", 16, 1, _desX + 236, _desY + 120, RGB(255, 255, 255));
	sprintf_s(str, "%d", _weight);
	fontCameraRender("NtreevSoft", str, 16, 1, _desX + 284, _desY + 120, RGB(255, 255, 255));
	fontCameraRender("NtreevSoft", "종류", 14, 1, _desX, _desY + 138, RGB(255, 255, 255));
	switch (_itemkind)
	{
	case ITEM_WEAPON:
		fontCameraRender("NtreevSoft", "무기", 16, 1, _desX + 50, _desY + 138, RGB(255, 255, 255));
		break;
	case ITEM_SHIELD:
		fontCameraRender("NtreevSoft", "방패", 16, 1, _desX + 50, _desY + 138, RGB(255, 255, 255));
		break;
	case ITEM_HAT:
		fontCameraRender("NtreevSoft", "모자", 16, 1, _desX + 50, _desY + 138, RGB(255, 255, 255));
		break;
	case ITEM_ACCESSORY:
		fontCameraRender("NtreevSoft", "악세서리", 16, 1, _desX + 50, _desY + 138, RGB(255, 255, 255));
		break;
	case ITEM_DRILL:
		fontCameraRender("NtreevSoft", "드릴", 16, 1, _desX + 50, _desY + 138, RGB(255, 255, 255));
		break;
	case ITEM_SPEND:
		fontCameraRender("NtreevSoft", "포션", 16, 1, _desX + 50, _desY + 138, RGB(255, 255, 255));
		break;
	}
	fontCameraRender("NtreevSoft", "설명", 19, 1, _desX, _desY + 200, RGB(255, 255, 255));
	fontCameraRender("NtreevSoft", _description, 16, 1, _desX + 62, _desY + 205, RGB(255, 255, 255));
}

void item::showRender(int x, int y)
{
	
}