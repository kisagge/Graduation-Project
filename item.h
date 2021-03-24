#pragma once
#include "gameNode.h"

enum ITEMKIND
{
	ITEM_WEAPON,
	ITEM_SHIELD,
	ITEM_HAT,
	ITEM_ACCESSORY,
	ITEM_DRILL,
	ITEM_SPEND,
	ITEM_SKILLCARD
};

class item : public gameNode
{
protected:
	image* _iconImg;			//아이템 아이콘 이미지
	int _iconX, _iconY;			//아이템 아이콘 좌표
	RECT _iconRc;				//아이템 아이콘 렉트

	image* _desCripImg;			//크게 보기 이미지
	int _desX, _desY;			//크게 보기 x,y
	RECT _desRC;				//크게 보기 렉트

	char _itemName[128];		//아이템 이름
	char _description[256];		//아이템 설명
	int _weight;				//아이템 무게

	int _hpUp, _mpUp;			//체력, 마나 업
	int _speedUp;				//이동속도 업
	int _apUp, _acUp, _dxUp;	//공격관련
	int _wtUp, _daUp, _lkUp;	//감각관련
	int _dpUp, _hvUp;			//매력관련

	int _boughtPrice;			//살 때 가격
	int _sellPrice;				//팔 때 가격

	image* _showImg;			//인게임 이미지 ( 모자일때만 쓸 것 )
	int _showX, _showY;			//인게임 출력 좌표 ( 모자일때만 쓸 것 )
	RECT _showRc;				//인게임 사용 렉트 ( 모자일때만 쓸 것 )

	ITEMKIND _itemkind;			//아이템 종류
	ITEMLIST _itemlist;			//어떤 아이템이냐 ( 구제적 )

	image* _itemInfoShow;
	int _requiredLv;			//필요레벨
public:
	virtual HRESULT init(void);
	virtual HRESULT init(int x, int y);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	int getIconX(){ return _iconX; }
	void setIconX(int iconX){ _iconX = iconX; }
	int getIconY(){ return _iconY; }
	void setIconY(int iconY){ _iconY = iconY; }
	RECT getIconRC(){ return _iconRc; }
	int getDesX(){ return _desX; }
	int getDesY(){ return _desY; }
	void setDesX(int k){ _desX = k; }
	void setDesY(int k){ _desY = k; }

	RECT getDesRC(){ return _desRC; }

	//스탯 관련
	int getHpUp(){ return _hpUp; }
	void setHpYp(int hpUp){ _hpUp = hpUp; }

	int getMpUp(){ return _mpUp; }
	void setMpUp(int mpUp){ _mpUp = mpUp; }

	int getSpeedUp(){ return _speedUp; }

	int getApUp(){ return _apUp; }
	int getAcUp(){ return _acUp; }
	int getDxUp(){ return _dxUp; }
	int getWtUp(){ return _wtUp; }
	int getDaUp(){ return _daUp; }
	int getLkUp(){ return _lkUp; }
	int getDpUp(){ return _dpUp; }
	int getHvUp(){ return _hvUp; }

	ITEMKIND getItemKind(){ return _itemkind; }
	ITEMLIST getItemlist(){ return _itemlist; }

	int getBoughtPrice(){ return _boughtPrice; }
	int getSellPrice(){ return _sellPrice; }

	int getShowX(){ return _showX; }
	int getShowY(){ return _showY; }

	int getRequiredLv(){ return _requiredLv; }

	int getWeight(){ return _weight; }

	char* getItemName(){ return _itemName; }

	void setInitValue(void);
	void setItemWhere(void);
	void iconRender(void);
	void desRender(void);
	void showRender(int x, int y);

	item();
	~item();
};

