#pragma once
#include "image.h"

//����� �̹����� ����ƽ���� ����� �α�
static image* _backBuffer = IMAGEMANAGER->addImage("backbuffer", 2000, 2000);
static image* _backBuffer2 = IMAGEMANAGER->addImage("backbuffer2", WINSIZEX, WINSIZEY);

//�̴ϸ�
static image* _backBuffer3 = IMAGEMANAGER->addImage("backbuffer3", 200, 150);
static image* _tempBuffer = IMAGEMANAGER->addImage("tempbuffer", 2000, 2000);

class gameNode
{
private:
	HDC _hdc;				//HDC
	bool _managerInit;		//�Ŵ��� �ʱ�ȭ �߳�?

	int _zOrder;			//z����
public:
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	virtual void render(int x, int y);

	//����� ������
	image* getBackBuffer(void) { return _backBuffer; }
	//ī�޶� ����
	image* getCameraBuffer(void){ return _backBuffer2; }
	image* getTempBuffer(void){ return _tempBuffer; }
	//�޸�DC ���
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	//HDC ���
	HDC getHDC() { return _hdc; }
	HDC getCameraDC(){ return _backBuffer2->getMemDC(); }
	HDC getTempDC(){ return _tempBuffer->getMemDC(); }

	//���̴� ȭ�� ī�޶�( �������� ȣ�����ش�)
	virtual void setCamera(int a, int b, int width, int height);

	//���� ���ν���
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	//��Ʈ ü����
	void fontRender(const char* fontName, const char* destStr, int nHeight, int fnWeight, int x, int y, COLORREF color);
	void fontCameraRender(const char* fontname, const char* destStr, int nHeight, int fnWeight, int x, int y, COLORREF color);

	//z���� ���Ϳ� �ֱ�
	virtual void putZorderVec(image* image, int x, int y, int ZO);
	virtual void putZorderVec(image* image, int x, int y,int ZO, int alp);
	virtual void putZorderVec(image* image, int x, int y,int ZO, int frameX, int frameY);
	virtual void putZorderVec(image* image, int x, int y,int ZO, int frameX, int frameY, int alp);

	//z����
	int getZOrder(){ return _zOrder; }


	gameNode();
	virtual ~gameNode();
};

