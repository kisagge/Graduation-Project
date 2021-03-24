#pragma once
#include "gameNode.h"
#include "tile.h"

#define TILEX 40
#define TILEY 20

class playerManager;

struct tagObject
{
	image* image;				//�̹���
	RECT collRc;				//�浹 ��Ʈ
	RECT imageRc;				//�̹��� ��� ��Ʈ
	int indX, indY;				//�浹 �ε���
	int x, y;					//���� �ߵ� ��ǥ
	int imageX, imageY;			//�̹��� ���� ���� ��ǥ
	bool isFrameImage;			//������ �̹�����
	float frameTimeCount;		//������ �����µ� �ʿ���
};

struct tagPortal
{
	image* img;
	RECT rc;
	int x, y;
	int gotoMap;		//0.�κ��  1.��ɸ�  2.������
};

class mapClass : public gameNode
{
protected:
	image* _bg;
	tile* _lobbyTile[TILEX][TILEY];

	vector<tagObject> _objVec;
	vector<tagObject>::iterator _iobjVec;

	vector<tagPortal> _portalVec;
	vector<tagPortal>::iterator _iportalVec;

	playerManager* _playerManagerLink;

	image* _portalIcon = IMAGEMANAGER->findImage("��Żǥ��");
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void addObj(const char* strKey, int imageIndX, int imageIndY, int collIndX, int collIndY,
		int widthTileNum, int heightTileNum, bool isFrame);

	image* getBg(){ return _bg; }
	tagObject getObj(int i){ return _objVec.at(i); }

	vector<tagPortal> getPortalVec(){ return _portalVec; }

	void setPlayerManagerLink(playerManager* pl){ _playerManagerLink = pl; }

	mapClass();
	~mapClass();
};

