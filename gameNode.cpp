#include "stdafx.h"
#include "gameNode.h"
gameNode::gameNode()
{
}
gameNode::~gameNode()
{
}
//==================================================================
//		## 더이상 생성자, 소멸자는 사용하지 않는다 ##
//==================================================================

//==================================================================
//		## 초기화 ## init(void)
//==================================================================
HRESULT gameNode::init(void)
{
	_hdc = GetDC(_hWnd);
	_managerInit = false;
	
	return S_OK;
}

//==================================================================
//		## 초기화 - init(bool managerInit) ## 
//==================================================================
HRESULT gameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (managerInit)
	{
		KEYMANAGER->init();					//키매니져 셋팅
		IMAGEMANAGER->init();				//이미지매니져 셋팅
		TIMEMANAGER->init();				//타임매니져 셋팅
		TXTDATA->init();					//텍스트데이터 셋팅
		INIDATA->init();					//INI데이터 셋팅
		SCENEMANAGER->init();				//씬매니져 셋팅
		SOUNDMANAGER->init();				//사운드매니져 셋팅
		EFFECTMANAGER->init();				//이펙트매니져 셋팅
		ANIMANAGER->init();					//애니메이션매니져 셋팅

	}

	return S_OK;
}

//==================================================================
//		## 해제 ## release(void)
//==================================================================
void gameNode::release(void)
{
	if (_managerInit)
	{
		//키매니져 해제
		KEYMANAGER->releaseSingleton();
		//이미지매니져 해제, 싱글톤 해제
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();
		//타임매니져 싱글톤 해제
		TIMEMANAGER->releaseSingleton();
		//텍스트데이터 싱글톤 해제
		TXTDATA->releaseSingleton();
		//INI데이터 싱글톤 해제
		INIDATA->releaseSingleton();
		//씬매니져 해제, 싱글톤 해제
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();
		//사운드매니져 해제, 싱글톤 해제
		SOUNDMANAGER->release();
		SOUNDMANAGER->releaseSingleton();
		//이펙트매니져 해제, 싱글톤 해제
		EFFECTMANAGER->release();
		EFFECTMANAGER->releaseSingleton();
		//애니메이션매니져 해제, 싱글톤 해제
		ANIMANAGER->release();
		ANIMANAGER->releaseSingleton();

	}
	
	//DC 해제
	ReleaseDC(_hWnd, _hdc);
}

//==================================================================
//		## 업데이트 ## update(void)
//==================================================================
void gameNode::update(void)
{
}

//==================================================================
//		## 렌더 ## render(HDC hdc)
//==================================================================
void gameNode::render(void)
{
}

void gameNode::render(int x, int y)
{

}

//==================================================================
//		## 메인 프로시져 ## 
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
	fontRender("나눔손글씨 펜", str, 20, 1, _ptMouse.x + cameraX, _ptMouse.y + cameraY, RGB(0, 0, 0));
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

//z오더 벡터에 넣기
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