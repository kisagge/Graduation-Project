#include "stdafx.h"
#include "gameNode.h"
gameNode::gameNode()
{
}
gameNode::~gameNode()
{
}
//==================================================================
//		## ���̻� ������, �Ҹ��ڴ� ������� �ʴ´� ##
//==================================================================

//==================================================================
//		## �ʱ�ȭ ## init(void)
//==================================================================
HRESULT gameNode::init(void)
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;
	
	return S_OK;
}

//==================================================================
//		## �ʱ�ȭ - init(bool managerInit) ## 
//==================================================================
HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (managerInit)
	{
		KEYMANAGER->init();					//Ű�Ŵ��� ����
		IMAGEMANAGER->init();				//�̹����Ŵ��� ����
		TIMEMANAGER->init();				//Ÿ�ӸŴ��� ����
		TXTDATA->init();					//�ؽ�Ʈ������ ����
		INIDATA->init();					//INI������ ����
		SCENEMANAGER->init();				//���Ŵ��� ����
		SOUNDMANAGER->init();				//����Ŵ��� ����
		EFFECTMANAGER->init();				//����Ʈ�Ŵ��� ����
		ANIMANAGER->init();					//�ִϸ��̼ǸŴ��� ����

	}

	return S_OK;
}

//==================================================================
//		## ���� ## release(void)
//==================================================================
void gameNode::release(void)
{
	if (_managerInit)
	{
		//Ű�Ŵ��� ����
		KEYMANAGER->releaseSingleton();
		//�̹����Ŵ��� ����, �̱��� ����
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		//Ÿ�ӸŴ��� �̱��� ����
		TIMEMANAGER->releaseSingleton();
		//�ؽ�Ʈ������ �̱��� ����
		TXTDATA->releaseSingleton();
		//INI������ �̱��� ����
		INIDATA->releaseSingleton();
		//���Ŵ��� ����, �̱��� ����
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();
		//����Ŵ��� ����, �̱��� ����
		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();
		//����Ʈ�Ŵ��� ����, �̱��� ����
		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();
		//�ִϸ��̼ǸŴ��� ����, �̱��� ����
		ANIMANAGER->release();
		ANIMANAGER->releaseSingleton();

	}
	
	//DC ����
	ReleaseDC(_hWnd, _hdc);
}

//==================================================================
//		## ������Ʈ ## update(void)
//==================================================================
void gameNode::update(void)
{
}

//==================================================================
//		## ���� ## render(HDC hdc)
//==================================================================
void gameNode::render(void)
{
}

void gameNode::render(int x, int y)
{

}

//==================================================================
//		## ���� ���ν��� ## 
//==================================================================
LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{

	switch (iMessage)
	{
	case WM_MOUSEMOVE:
		_ptMouse.x = static_cast<float>LOWORD(lParam);
		_ptMouse.y = static_cast<float>HIWORD(lParam);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void gameNode::setCamera(int a, int b, int width, int height)
{
	if (a < WINSIZEX / 2) cameraX = 0;
	else if (a + WINSIZEX / 2 > width)
		cameraX = width - WINSIZEX;
	else cameraX = a - WINSIZEX / 2;

	if (b < WINSIZEY / 2) cameraY = 0;
	else if (b + WINSIZEY / 2 > height)
		cameraY = height - WINSIZEY;
	else cameraY = b - WINSIZEY / 2;

	char str[128];
	sprintf(str, "(%d,%d)", _ptMouse.x + cameraX, _ptMouse.y + cameraY);
	fontRender("�����ձ۾� ��", str, 20, 1, _ptMouse.x + cameraX, _ptMouse.y + cameraY, RGB(0, 0, 0));
	BitBlt(getCameraDC(), 0, 0, width, height, getMemDC(), cameraX, cameraY, SRCCOPY);
}

void gameNode::fontRender(const char* fontName, const char* destStr, int nHeight,
	int fnWeight, int x, int y, COLORREF color)
{
	HFONT myFont = CreateFont(nHeight, 0, 0, 0, fnWeight, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, fontName);
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), myFont);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), color);
	TextOut(getMemDC(), x, y, destStr, strlen(destStr));
	SelectObject(getMemDC(), oldFont);
	DeleteObject(myFont);
}

void gameNode::fontCameraRender(const char* fontName, const char* destStr, int nHeight,
	int fnWeight, int x, int y, COLORREF color)
{
	HFONT myFont = CreateFont(nHeight, 0, 0, 0, fnWeight, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, fontName);
	HFONT oldFont = (HFONT)SelectObject(getCameraDC(), myFont);
	SetBkMode(getCameraDC(), TRANSPARENT);
	SetTextColor(getCameraDC(), color);
	TextOut(getCameraDC(), x, y, destStr, strlen(destStr));
	SelectObject(getCameraDC(), oldFont);
	DeleteObject(myFont);
}

//z���� ���Ϳ� �ֱ�
void gameNode::putZorderVec(image* image, int x, int y, int ZO)
{
	tagZorderImage temp;
	temp.img = image;
	temp.x = x;
	temp.y = y;
	temp.zorder = ZO;
	temp.rc = RectMake(x, ZO, temp.img->getWidth(), temp.img->getHeight());
	temp.isFrameImage = false;
	temp.isAlpha = false;
	_zorderVec.push_back(temp);
}

void gameNode::putZorderVec(image* image, int x, int y, int ZO, int alp)
{
	tagZorderImage temp;
	temp.img = image;
	temp.x = x;
	temp.y = y;
	temp.zorder = ZO;
	temp.rc = RectMake(x, ZO, temp.img->getWidth(), temp.img->getHeight());
	temp.isFrameImage = false;
	temp.alpha = alp;
	temp.isAlpha = true;
	_zorderVec.push_back(temp);
}

void gameNode::putZorderVec(image* image, int x, int y, int ZO, int frameX, int frameY)
{
	tagZorderImage temp;
	temp.img = image;
	temp.x = x;
	temp.y = y;
	temp.zorder = ZO;
	temp.rc = RectMake(x, ZO, temp.img->getFrameWidth(), temp.img->getFrameHeight());
	temp.frameX = frameX;
	temp.frameY = frameY;
	temp.isFrameImage = true;
	temp.isAlpha = false;
	_zorderVec.push_back(temp);
}

void gameNode::putZorderVec(image* image, int x, int y, int ZO, int frameX, int frameY, int alp)
{
	tagZorderImage temp;
	temp.img = image;
	temp.x = x;
	temp.y = y;
	temp.zorder = ZO;
	temp.rc = RectMake(x, ZO, temp.img->getFrameWidth(), temp.img->getFrameHeight());
	temp.frameX = frameX;
	temp.frameY = frameY;
	temp.isFrameImage = true;
	temp.alpha = alp;
	temp.isAlpha = true;
	_zorderVec.push_back(temp);
}