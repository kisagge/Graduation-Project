#include "stdafx.h"
#include "animation.h"
animation::animation()
	:_frameNum(0), _frameWidth(0), _frameHeight(0), _loop(FALSE), _elapsedSec(0), _nowPlayIdx(0), _play(FALSE)
{
}
animation::~animation()
{
}
//==================================================================
//		## ���̻� ������, �Ҹ��ڴ� ������� �ʴ´� ##
//==================================================================

//�ʱ�ȭ(�̹��� ��ü����ũ��, ��ü����ũ��, �������� ����ũ��, �������� ����ũ��)
HRESULT animation::init(int totalW, int totalH, int frameW, int frameH)
{
	//���� ������ ����
	_frameWidth = frameW;
	int frameWidthNum = totalW / _frameWidth;
	//���� ������ ����
	_frameHeight = frameH;
	int frameHeightNum = totalH / _frameHeight;

	//�� ������ ��
	_frameNum = frameWidthNum * frameHeightNum;

	//������ ��ġ ��� �����ϱ�
	_frameList.clear();
	for (int i = 0; i < frameHeightNum; i++)
	{
		for (int j = 0; j < frameWidthNum; j++)
		{
			POINT framePos;
			framePos.x = j * _frameWidth;
			framePos.y = i * _frameHeight;

			//������ ��ġ ��Ͽ� �߰�
			_frameList.push_back(framePos);
		}
	}

	//�⺻ ���������� ����
	setDefPlayFrame();

	return S_OK;
}

void animation::release(void)
{
}

//ó������ ������ �ִϸ��̼� �����ϱ�
void animation::setDefPlayFrame(BOOL reverse, BOOL loop)
{
	//��������
	_loop = loop;
	//�÷��� ��� �ʱ�ȭ
	_playList.clear();

	if (reverse)
	{
		if (_loop) //������ �� 1���ε���������
		{
			//������
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}
			//������
			for (int i = _frameNum - 2; i > 0; i--)
			{
				_playList.push_back(i);
			}
		}
		else //������ �� 0���ε�������
		{
			//������
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}
			//������
			for (int i = _frameNum - 2; i >= 0; i--)
			{
				_playList.push_back(i);
			}
		}
	}
	else
	{
		//������
		for (int i = 0; i < _frameNum; i++)
		{
			_playList.push_back(i);
		}
	}
}

//�迭�� ��Ƽ� ����ִ°͸� �ִϸ��̼� �����ϱ�
void animation::setPlayFrame(int* playArr, int arrLen, BOOL loop)
{
	//��������
	_loop = loop;
	//�÷��� ��� �ʱ�ȭ
	_playList.clear();

	for (int i = 0; i < arrLen; i++)
	{
		_playList.push_back(playArr[i]);
	}
}

//����, �� ������ ���ؼ� ���� �ִϸ��̼� �����ϱ�
void animation::setPlayFrame(int start, int end, BOOL reverse, BOOL loop)
{
	//��������
	_loop = loop;
	//�÷��� ��� �ʱ�ȭ
	_playList.clear();

	//���۰� �� ������ ������ ������� ����� �ʿ� ����
	if (start == end)
	{
		_playList.clear();
		stop();
		return;
	}
	//���� �������� ���������Ӻ��� ū���
	else if (start > end)
	{
		if (reverse)
		{
			if (_loop) //������ �� 1���ε���������
			{
				//������
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}
				//������
				for (int i = end + 1; i < start; i++)
				{
					_playList.push_back(i);
				}
			}
			else //������ �� 0���ε�������
			{
				//������
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}
				//������
				for (int i = end + 1; i <= start; i++)
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			//������
			for (int i = start; i >= end; i--)
			{
				_playList.push_back(i);
			}
		}
	}
	else //���������� ������������ ���������Ӻ��� �������
	{
		if (reverse)
		{
			if (_loop) //������ �� 1���ε���������
			{
				//������
				for (int i = start; i <= end; i++)
				{
					_playList.push_back(i);
				}
				//������
				for (int i = end - 1; i > start; i--)
				{
					_playList.push_back(i);
				}
			}
			else //������ �� 0���ε�������
			{
				//������
				for (int i = start; i <= end; i++)
				{
					_playList.push_back(i);
				}
				//������
				for (int i = end - 1; i >= start; i--)
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			//������
			for (int i = start; i <= end; i++)
			{
				_playList.push_back(i);
			}
		}
	}

}

//�ʴ� ���� Ƚ��
void animation::setFPS(int framePerSec)
{
	_frameUpdateSec = 1.0f / framePerSec;
}

//������ ������Ʈ Ÿ��
void animation::frameUpdate(float elapsedTime)
{
	//�÷������̳�?
	if (_play)
	{
		_elapsedSec += elapsedTime;

		//������ ������Ʈ �ð��� �Ǿ��ٸ�
		if (_elapsedSec >= _frameUpdateSec)
		{
			_elapsedSec -= _frameUpdateSec;
			_nowPlayIdx++;
			if (_nowPlayIdx == _playList.size())
			{
				if (_loop)
				{
					_nowPlayIdx = 0;
				}
				else
				{
					_nowPlayIdx--;
					_play = FALSE;
				}
			}
		}
	}
}

//�÷��� ����
void animation::start(void)
{
	_play = true;
	_nowPlayIdx = 0;
}

//�÷��� ����
void animation::stop(void)
{
	_play = false;
	_nowPlayIdx = 0;
}

//�Ͻ�����
void animation::pause(void)
{
	_play = false;
}

//�ٽ����
void animation::resume(void)
{
	_play = true;
}
