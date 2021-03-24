#pragma once
#include "image.h"

//백버퍼 이미지를 스태틱으로 만들어 두기
static image* _backBuffer = IMAGEMANAGER->addImage("backbuffer", 2000, 2000);
static image* _backBuffer2 = IMAGEMANAGER->addImage("backbuffer2", WINSIZEX, WINSIZEY);

//미니맵
static image* _backBuffer3 = IMAGEMANAGER->addImage("backbuffer3", 200, 150);
static image* _tempBuffer = IMAGEMANAGER->addImage("tempbuffer", 2000, 2000);

class gameNode
{
private:
	HDC _hdc;				//HDC
	bool _managerInit;		//매니져 초기화 했냐?

	int _zOrder;			//z오더
public:
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	virtual void render(int x, int y);

	//백버퍼 얻어오기
	image* getBackBuffer(void) { return _backBuffer; }
	//카메라 버퍼
	image* getCameraBuffer(void){ return _backBuffer2; }
	image* getTempBuffer(void){ return _tempBuffer; }
	//메모리DC 얻기
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	//HDC 얻기
	HDC getHDC() { return _hdc; }
	HDC getCameraDC(){ return _backBuffer2->getMemDC(); }
	HDC getTempDC(){ return _tempBuffer->getMemDC(); }

	//보이는 화면 카메라( 렌더에서 호출해준다)
	virtual void setCamera(int a, int b, int width, int height);

	//메인 프로시져
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	//폰트 체인지
	void fontRender(const char* fontName, const char* destStr, int nHeight, int fnWeight, int x, int y, COLORREF color);
	void fontCameraRender(const char* fontname, const char* destStr, int nHeight, int fnWeight, int x, int y, COLORREF color);

	//z오더 벡터에 넣기
	virtual void putZorderVec(image* image, int x, int y, int ZO);
	virtual void putZorderVec(image* image, int x, int y,int ZO, int alp);
	virtual void putZorderVec(image* image, int x, int y,int ZO, int frameX, int frameY);
	virtual void putZorderVec(image* image, int x, int y,int ZO, int frameX, int frameY, int alp);

	//z오더
	int getZOrder(){ return _zOrder; }


	gameNode();
	virtual ~gameNode();
};

