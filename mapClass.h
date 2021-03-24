#pragma once
#include "gameNode.h"
#include "tile.h"

#define TILEX 40
#define TILEY 20

class playerManager;

struct tagObject
{
	image* image;				//이미지
	RECT collRc;				//충돌 렉트
	RECT imageRc;				//이미지 출력 렉트
	int indX, indY;				//충돌 인덱스
	int x, y;					//실제 중돌 좌표
	int imageX, imageY;			//이미지 렌더 시작 좌표
	bool isFrameImage;			//프레임 이미지냐
	float frameTimeCount;		//프레임 돌리는데 필요함
};

struct tagPortal
{
	image* img;
	RECT rc;
	int x, y;
	int gotoMap;		//0.로비맵  1.사냥맵  2.보스맵
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

	image* _portalIcon = IMAGEMANAGER->findImage("포탈표시");
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

