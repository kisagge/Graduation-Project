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
//		## ���̻� ������, �Ҹ��ڴ� ������� �ʴ´� ##
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
					//����ƮŬ���� ������
					(*vArrIter)->release();
					//����ƮŬ���� ����
					SAFE_DELETE(*vArrIter);
					//�ݺ��� ����
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

//����Ʈ�߰�(����ƮŰ��, �̹����̸�, �̹�������ũ��, �̹�������ũ��, �������Ӱ���ũ��, �������Ӽ���ũ��, FPS, ����Ʈ�ӵ�, ���۰���)
void effectManager::addEffect(string effectKey, char* imageName, int imageW, int imageH, int frameW, int frameH, int fps, float elapsedTime, int buffer)
{
	image* img;
	vEffect vEffectBuffer;
	mEffect mArrEffect;

	//�̹����� �̹����Ŵ����� ��ϵǾ� �ִٸ�
	if (IMAGEMANAGER->findImage(imageName))
	{
		img = IMAGEMANAGER->findImage(imageName);
	}
	else
	{
		//�̹��� ���ε��
		img = IMAGEMANAGER->addImage(imageName, imageName, imageW, imageH, true, RGB(255, 0, 255));
	}

	//����ũ�⸸ŭ ����Ʈ�� �����Ҵ��� �ʱ�ȭ �ؼ� ���Ϳ� ��´�
	for (int i = 0; i < buffer; i++)
	{
		vEffectBuffer.push_back(new effect);
		vEffectBuffer[i]->init(img, frameW, frameH, fps, elapsedTime);
	}

	//���Ϳ���� ����Ʈ���۸� �ʿ� ��´�
	mArrEffect.insert(make_pair(effectKey, vEffectBuffer));

	//�ʿ���� ���͸� ��Ż���Ϳ� ��´�
	_vTotalEffect.push_back(mArrEffect);
}

//����Ʈ �÷���(����ƮŰ��, ����Ʈ ��Ʈ�� x, y ��ǥ)
void effectManager::play(string effectKey, int x, int y)
{
	viTotalEffect vIter;
	miEffect mIter;

	//��� ����Ʈ�� ����ִ� ���͸� ���ƶ�
	for (vIter = _vTotalEffect.begin(); vIter != _vTotalEffect.end(); ++vIter)
	{
		//����Ʈ�� ����ִ� ���� ���ƶ�
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			//����ƮŰ���� ���ؼ� ���� ������ ���������� �ѱ��
			if (!(mIter->first == effectKey)) break;

			//����ƮŰ���� ��ġ�ϸ� ����Ʈ �÷���
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
