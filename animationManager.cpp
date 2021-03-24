#include "stdafx.h"
#include "animationManager.h"
animationManager::animationManager()
{
}
animationManager::~animationManager()
{
}
//==================================================================
//		## ���̻� ������, �Ҹ��ڴ� ������� �ʴ´� ##
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

/*�ִϸ��̼� �߰�*/
//ó������ ������
void animationManager::addDefAnimation(string animationKeyName, char* imageKeyName, int fps, BOOL reverse, BOOL loop)
{
	//�̹��� �� �ִϸ��̼� �ʱ�ȭ
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop);
	ani->setFPS(fps);

	//�̹����� �ִϸ��̼��� �ʱ�ȭ �� �ʿ� �߰��Ѵ�
	_mTotalAnimation.insert(make_pair(animationKeyName, ani));
}

//�迭�� ��Ƽ�
void animationManager::addAnimation(string animationKeyName, char* imageKeyName, int* playArr, int arrLen, int fps, BOOL loop)
{
	//�̹��� �� �ִϸ��̼� �ʱ�ȭ
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(playArr, arrLen, loop);
	ani->setFPS(fps);

	//�̹����� �ִϸ��̼��� �ʱ�ȭ �� �ʿ� �߰��Ѵ�
	_mTotalAnimation.insert(make_pair(animationKeyName, ani));
}
//���� ���ؼ�
void animationManager::addAnimation(string animationKeyName, char* imageKeyName, int start, int end, int fps, BOOL reverse, BOOL loop)
{
	//�̹��� �� �ִϸ��̼� �ʱ�ȭ
	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop);
	ani->setFPS(fps);

	//�̹����� �ִϸ��̼��� �ʱ�ȭ �� �ʿ� �߰��Ѵ�
	_mTotalAnimation.insert(make_pair(animationKeyName, ani));
}

//�÷���
void animationManager::start(string animationKeyName)
{
	iterAnimation iter = _mTotalAnimation.find(animationKeyName);
	iter->second->start();
}
//����
void animationManager::stop(string animationKeyName)
{
	iterAnimation iter = _mTotalAnimation.find(animationKeyName);
	iter->second->stop();
}
//�Ͻ�����
void animationManager::pause(string animationKeyName)
{
	iterAnimation iter = _mTotalAnimation.find(animationKeyName);
	iter->second->pause();
}
//�ٽ����
void animationManager::resume(string animationKeyName)
{
	iterAnimation iter = _mTotalAnimation.find(animationKeyName);
	iter->second->resume();
}

//�ִϸ��̼� ã��
animation* animationManager::findAnimation(string animationKeyName)
{
	iterAnimation iter = _mTotalAnimation.find(animationKeyName);
	if (iter != _mTotalAnimation.end())
	{
		return iter->second;
	}
	
	return NULL;
}

//�ִϸ��̼� ���λ���
void animationManager::deleteAll(void)
{
	iterAnimation iter = _mTotalAnimation.begin();
	for (; iter != _mTotalAnimation.end();)
	{
		if (iter->second != NULL)
		{
			//�ִϸ��̼� Ŭ���� ����
			SAFE_DELETE(iter->second);
			//�ݺ��� ����
			iter = _mTotalAnimation.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}
