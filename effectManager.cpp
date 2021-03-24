#include "stdafx.h"
#include "effectManager.h"
#include "effect.h"
effectManager::effectManager()
{
}
effectManager::~effectManager()
{
}
//==================================================================
//		## 더이상 생성자, 소멸자는 사용하지 않는다 ##
//==================================================================

HRESULT effectManager::init(void)
{
	return S_OK;
}

void effectManager::release(void)
{
	viTotalEffect vIter;
	miEffect mIter;

	for (vIter = _vTotalEffect.begin(); vIter != _vTotalEffect.end(); ++vIter)
	{
		mIter = vIter->begin();
		for (; mIter != vIter->end();)
		{
			if (mIter->second.size() != 0)
			{
				viEffect vArrIter = mIter->second.begin();
				for (; vArrIter != mIter->second.end();)
				{
					//이펙트클래스 릴리즈
					(*vArrIter)->release();
					//이펙트클래스 해제
					SAFE_DELETE(*vArrIter);
					//반복자 해제
					vArrIter = mIter->second.erase(vArrIter);
				}
			}
			else
			{
				++mIter;
			}
		}
	}
}

void effectManager::update(void)
{
	viTotalEffect vIter;
	miEffect mIter;

	for (vIter = _vTotalEffect.begin(); vIter != _vTotalEffect.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			viEffect vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				(*vArrIter)->update();
			}
		}
	}
}

void effectManager::render(void)
{
	viTotalEffect vIter;
	miEffect mIter;

	for (vIter = _vTotalEffect.begin(); vIter != _vTotalEffect.end(); ++vIter)
	{
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			viEffect vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				(*vArrIter)->render();
			}
		}
	}
}

//이펙트추가(이펙트키값, 이미지이름, 이미지가로크기, 이미지세로크기, 한프레임가로크기, 한프레임세로크기, FPS, 이펙트속도, 버퍼갯수)
void effectManager::addEffect(string effectKey, char* imageName, int imageW, int imageH, int frameW, int frameH, int fps, float elapsedTime, int buffer)
{
	image* img;
	vEffect vEffectBuffer;
	mEffect mArrEffect;

	//이미지가 이미지매니져에 등록되어 있다면
	if (IMAGEMANAGER->findImage(imageName))
	{
		img = IMAGEMANAGER->findImage(imageName);
	}
	else
	{
		//이미지 새로등록
		img = IMAGEMANAGER->addImage(imageName, imageName, imageW, imageH, true, RGB(255, 0, 255));
	}

	//버퍼크기만큼 이펙트를 동적할당후 초기화 해서 벡터에 담는다
	for (int i = 0; i < buffer; i++)
	{
		vEffectBuffer.push_back(new effect);
		vEffectBuffer[i]->init(img, frameW, frameH, fps, elapsedTime);
	}

	//벡터에담긴 이펙트버퍼를 맵에 담는다
	mArrEffect.insert(make_pair(effectKey, vEffectBuffer));

	//맵에담긴 벡터를 토탈벡터에 담는다
	_vTotalEffect.push_back(mArrEffect);
}

//이펙트 플레이(이펙트키값, 이펙트 터트릴 x, y 좌표)
void effectManager::play(string effectKey, int x, int y)
{
	viTotalEffect vIter;
	miEffect mIter;

	//모든 이펙트가 담겨있는 벡터를 돌아라
	for (vIter = _vTotalEffect.begin(); vIter != _vTotalEffect.end(); ++vIter)
	{
		//이펙트가 담겨있는 맵을 돌아라
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			//이펙트키값과 비교해서 같지 않으면 다음맵으로 넘긴다
			if (!(mIter->first == effectKey)) break;

			//이펙트키값과 일치하면 이펙트 플레이
			viEffect vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				if ((*vArrIter)->getIsRunning()) continue;
				(*vArrIter)->startEffect(x, y);
				return;
			}
		}
	}
}
