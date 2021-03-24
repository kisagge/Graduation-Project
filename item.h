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
	image* _iconImg;			//������ ������ �̹���
	int _iconX, _iconY;			//������ ������ ��ǥ
	RECT _iconRc;				//������ ������ ��Ʈ

	image* _desCripImg;			//ũ�� ���� �̹���
	int _desX, _desY;			//ũ�� ���� x,y
	RECT _desRC;				//ũ�� ���� ��Ʈ

	char _itemName[128];		//������ �̸�
	char _description[256];		//������ ����
	int _weight;				//������ ����

	int _hpUp, _mpUp;			//ü��, ���� ��
	int _speedUp;				//�̵��ӵ� ��
	int _apUp, _acUp, _dxUp;	//���ݰ���
	int _wtUp, _daUp, _lkUp;	//��������
	int _dpUp, _hvUp;			//�ŷ°���

	int _boughtPrice;			//�� �� ����
	int _sellPrice;				//�� �� ����

	image* _showImg;			//�ΰ��� �̹��� ( �����϶��� �� �� )
	int _showX, _showY;			//�ΰ��� ��� ��ǥ ( �����϶��� �� �� )
	RECT _showRc;				//�ΰ��� ��� ��Ʈ ( �����϶��� �� �� )

	ITEMKIND _itemkind;			//������ ����
	ITEMLIST _itemlist;			//� �������̳� ( ������ )

	image* _itemInfoShow;
	int _requiredLv;			//�ʿ䷹��
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

	//���� ����
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

