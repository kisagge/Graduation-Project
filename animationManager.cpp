#include "stdafx.h"
#include "animationManager.h"
animationManager::animationManager()
{
}
animationManager::~animationManager()
{
}
//==================================================================
//		## 더이상 생성자, 소멸자는 사용하지 않는다 ##
//==================================================================

HRESULT animationManager::init(void)
{
	return S_OK;
}

void animationManager::release(void)
{
	deleteAll();
}

void animationManager::update(void)
{
	iterAnimation iter = _mTotalAnimation.begin();
	for (iter; iter != _mTotalAnimation.end(); ++iter)
	{
		if (!iter->second->isPlay()) continue;
		iter->second->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
	}
}

void animationManager::render(void)
{
}

/*애니메이션 추가*/
//처음부터 끝까지
void animationManager::addDefAnimation(string animationKeyName, char* imageKeyName, int fps, BOOL reverse, BOOL loop)
{
	//이미지 및 애니메이션 초기화
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop);
	ani->setFPS(fps);

	//이미지와 애니메이션을 초기화 후 맵에 추가한다
	_mTotalAnimation.insert(make_pair(animationKeyName, ani));
}

//배열에 담아서
void animationManager::addAnimation(string animationKeyName, char* imageKeyName, int* playArr, int arrLen, int fps, BOOL loop)
{
	//이미지 및 애니메이션 초기화
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(playArr, arrLen, loop);
	ani->setFPS(fps);

	//이미지와 애니메이션을 초기화 후 맵에 추가한다
	_mTotalAnimation.insert(make_pair(animationKeyName, ani));
}
//구간 정해서
void animationManager::addAnimation(string animationKeyName, char* imageKeyName, int start, int end, int fps, BOOL reverse, BOOL loop)
{
	//이미지 및 애니메이션 초기화
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop);
	ani->setFPS(fps);

	//이미지와 애니메이션을 초기화 후 맵에 추가한다
	_mTotalAnimation.insert(make_pair(animationKeyName, ani));
}

//플레이
void animationManager::start(string animationKeyName)
{
	iterAnimation iter = _mTotalAnimation.find(animationKeyName);
	iter->second->start();
}
//정지
void animationManager::stop(string animationKeyName)
{
	iterAnimation iter = _mTotalAnimation.find(animationKeyName);
	iter->second->stop();
}
//일시정지
void animationManager::pause(string animationKeyName)
{
	iterAnimation iter = _mTotalAnimation.find(animationKeyName);
	iter->second->pause();
}
//다시재생
void animationManager::resume(string animationKeyName)
{
	iterAnimation iter = _mTotalAnimation.find(animationKeyName);
	iter->second->resume();
}

//애니메이션 찾기
animation* animationManager::findAnimation(string animationKeyName)
{
	iterAnimation iter = _mTotalAnimation.find(animationKeyName);
	if (iter != _mTotalAnimation.end())
	{
		return iter->second;
	}
	
	return NULL;
}

//애니메이션 전부삭제
void animationManager::deleteAll(void)
{
	iterAnimation iter = _mTotalAnimation.begin();
	for (; iter != _mTotalAnimation.end();)
	{
		if (iter->second != NULL)
		{
			//애니메이션 클래스 삭제
			SAFE_DELETE(iter->second);
			//반복자 삭제
			iter = _mTotalAnimation.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}
