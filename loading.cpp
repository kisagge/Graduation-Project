#include "stdafx.h"
#include "loading.h"

//키값으로 빈 비트맵으로 초기화
HRESULT loadItem::initForImage(string keyName, int width, int height)
{
	_kind = LOAD_KIND_IMAGE_0;

	//이미지 구조체 초기화
	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.width = width;
	_imageResource.height = height;

	return S_OK;
}
//키값으로 이미지 파일로 초기화 (주 사용)
HRESULT loadItem::initForImage(string keyName, const char* fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	_kind = LOAD_KIND_IMAGE_1;

	//이미지 구조체 초기화
	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}
HRESULT loadItem::initForImage(string keyName, const char* fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	_kind = LOAD_KIND_IMAGE_2;

	//이미지 구조체 초기화
	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}
//키값으로 프레임 이미지 파일로 초기화
HRESULT loadItem::initForFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, BOOL isTrans, COLORREF transColor)
{
	_kind = LOAD_KIND_FRAMEIMAGE_0;

	//이미지 구조체 초기화
	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}
HRESULT loadItem::initForFrameImage(string keyName, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL isTrans, COLORREF transColor)
{
	_kind = LOAD_KIND_FRAMEIMAGE_1;

	//이미지 구조체 초기화
	memset(&_imageResource, 0, sizeof(tagImageResource));

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loading::init(void)
{
	//로딩화면 백그라운드 초기화
	_background = IMAGEMANAGER->addImage("시작", "images/로딩.bmp", WINSIZEX, WINSIZEY);

	//로딩바 초기화
	_loadingBar = new progressBar;
	_loadingBar->init("images/loadingBarFront.bmp", "images/loadingBarBack.bmp", 100, 660, 600, 30);
	_loadingBar->setGauge(0, 0);

	//로딩바 게이지 초기화
	_currentGauge = 0;

	return S_OK;
}
void loading::release(void)
{
	//로딩바 해제
	SAFE_DELETE(_loadingBar);
}
void loading::update(void)
{
	//로딩바 업데이트
	_loadingBar->update();
}
void loading::render(void)
{
	//백그라운드 렌더
	_background->render(getMemDC());
	//로딩바 렌더
	_loadingBar->render();
}


//키값으로 빈 비트맵으로 초기화
void loading::loadImage(string keyName, int width, int height)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, width, height);

	_vLoadItem.push_back(item);
}
//키값으로 이미지 파일로 초기화 (주 사용)
void loading::loadImage(string keyName, const char* fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, width, height, isTrans, transColor);

	_vLoadItem.push_back(item);
}
void loading::loadImage(string keyName, const char* fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, x, y, width, height, isTrans, transColor);

	_vLoadItem.push_back(item);
}
//키값으로 프레임 이미지 파일로 초기화
void loading::loadFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, BOOL isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, width, height, frameX, frameY, isTrans, transColor);

	_vLoadItem.push_back(item);
}
void loading::loadFrameImage(string keyName, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL isTrans, COLORREF transColor)
{
	loadItem* item = new loadItem; item->initForFrameImage(keyName, fileName, x, y, width, height, frameX, frameY, isTrans, transColor);

	_vLoadItem.push_back(item);
}

//중요하다
//로딩 완료 됬냐(로딩완료후 씬 변경)
BOOL loading::loadingDone()
{
	if (_currentGauge >= _vLoadItem.size())
	{
		return TRUE;
	}
	loadItem* item = _vLoadItem[_currentGauge];
	switch (item->getLoadingKind())
	{
	case LOAD_KIND_IMAGE_0:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.width, img.height);
	}
	break;
	case LOAD_KIND_IMAGE_1:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.fileName, img.width, img.height, img.trans, img.transColor);
	}
	break;
	case LOAD_KIND_IMAGE_2:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.trans, img.transColor);
	}
	break;
	case LOAD_KIND_FRAMEIMAGE_0:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor);
	}
	break;
	case LOAD_KIND_FRAMEIMAGE_1:
	{
		tagImageResource img = item->getImageResource();
		IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor);
	}
	break;
	//너희들이 할 것 ! 
	case LOAD_KIND_SOUND:
		break;
	}

	//로딩바 이미지 변경
	_loadingBar->setGauge(_currentGauge, _vLoadItem.size());

	//카운트
	_currentGauge++;

	return FALSE;
}