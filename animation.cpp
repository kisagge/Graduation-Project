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
//		## 더이상 생성자, 소멸자는 사용하지 않는다 ##
//==================================================================

//초기화(이미지 전체가로크기, 전체세로크기, 한프레임 가로크기, 한프레임 세로크기)
HRESULT animation::init(int totalW, int totalH, int frameW, int frameH)
{
	//가로 프레임 갯수
	_frameWidth = frameW;
	int frameWidthNum = totalW / _frameWidth;
	//세로 프레임 갯수
	_frameHeight = frameH;
	int frameHeightNum = totalH / _frameHeight;

	//총 프레임 수
	_frameNum = frameWidthNum * frameHeightNum;

	//프레임 위치 목록 세팅하기
	_frameList.clear();
	for (int i = 0; i < frameHeightNum; i++)
	{
		for (int j = 0; j < frameWidthNum; j++)
		{
			POINT framePos;
			framePos.x = j * _frameWidth;
			framePos.y = i * _frameHeight;

			//프레임 위치 목록에 추가
			_frameList.push_back(framePos);
		}
	}

	//기본 프레임으로 셋팅
	setDefPlayFrame();

	return S_OK;
}

void animation::release(void)
{
}

//처음부터 끝까지 애니메이션 셋팅하기
void animation::setDefPlayFrame(BOOL reverse, BOOL loop)
{
	//루프여부
	_loop = loop;
	//플레이 목록 초기화
	_playList.clear();

	if (reverse)
	{
		if (_loop) //리버스 후 1번인덱스까지만
		{
			//정방향
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}
			//역방향
			for (int i = _frameNum - 2; i > 0; i--)
			{
				_playList.push_back(i);
			}
		}
		else //리버스 후 0번인덱스까지
		{
			//정방향
			for (int i = 0; i < _frameNum; i++)
			{
				_playList.push_back(i);
			}
			//역방향
			for (int i = _frameNum - 2; i >= 0; i--)
			{
				_playList.push_back(i);
			}
		}
	}
	else
	{
		//정방향
		for (int i = 0; i < _frameNum; i++)
		{
			_playList.push_back(i);
		}
	}
}

//배열에 담아서 담겨있는것만 애니메이션 셋팅하기
void animation::setPlayFrame(int* playArr, int arrLen, BOOL loop)
{
	//루프여부
	_loop = loop;
	//플레이 목록 초기화
	_playList.clear();

	for (int i = 0; i < arrLen; i++)
	{
		_playList.push_back(playArr[i]);
	}
}

//시작, 끝 구간을 정해서 구간 애니메이션 셋팅하기
void animation::setPlayFrame(int start, int end, BOOL reverse, BOOL loop)
{
	//루프여부
	_loop = loop;
	//플레이 목록 초기화
	_playList.clear();

	//시작과 끝 프레임 구간이 같은경우 재생할 필요 없다
	if (start == end)
	{
		_playList.clear();
		stop();
		return;
	}
	//시작 프레임이 종료프레임보다 큰경우
	else if (start > end)
	{
		if (reverse)
		{
			if (_loop) //리버스 후 1번인덱스까지만
			{
				//정방향
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}
				//역방향
				for (int i = end + 1; i < start; i++)
				{
					_playList.push_back(i);
				}
			}
			else //리버스 후 0번인덱스까지
			{
				//정방향
				for (int i = start; i >= end; i--)
				{
					_playList.push_back(i);
				}
				//역방향
				for (int i = end + 1; i <= start; i++)
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			//정방향
			for (int i = start; i >= end; i--)
			{
				_playList.push_back(i);
			}
		}
	}
	else //정상적으로 시작프레임이 종료프레임보다 작은경우
	{
		if (reverse)
		{
			if (_loop) //리버스 후 1번인덱스까지만
			{
				//정방향
				for (int i = start; i <= end; i++)
				{
					_playList.push_back(i);
				}
				//역방향
				for (int i = end - 1; i > start; i--)
				{
					_playList.push_back(i);
				}
			}
			else //리버스 후 0번인덱스까지
			{
				//정방향
				for (int i = start; i <= end; i++)
				{
					_playList.push_back(i);
				}
				//역방향
				for (int i = end - 1; i >= start; i--)
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			//정방향
			for (int i = start; i <= end; i++)
			{
				_playList.push_back(i);
			}
		}
	}

}

//초당 갱신 횟수
void animation::setFPS(int framePerSec)
{
	_frameUpdateSec = 1.0f / framePerSec;
}

//프레임 업데이트 타임
void animation::frameUpdate(float elapsedTime)
{
	//플레이중이냐?
	if (_play)
	{
		_elapsedSec += elapsedTime;

		//프레임 업데이트 시간이 되었다면
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

//플레이 시작
void animation::start(void)
{
	_play = true;
	_nowPlayIdx = 0;
}

//플레이 정지
void animation::stop(void)
{
	_play = false;
	_nowPlayIdx = 0;
}

//일시정지
void animation::pause(void)
{
	_play = false;
}

//다시재생
void animation::resume(void)
{
	_play = true;
}
