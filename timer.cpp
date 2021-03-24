#include "stdafx.h"
#include "timer.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
//timeGetTime 함수를 사용하기 위한 라이브러리 추가
//윈도우가 시작되고 난후 시간을 리턴시켜줌
timer::timer()
{
}
timer::~timer()
{
}
//==================================================================
//		## 더이상 생성자, 소멸자는 사용하지 않는다 ##
//==================================================================

//타이머 초기화
HRESULT timer::init(void)
{
	//고성능 타이머 지원여부 체크
	//고성능 타이머를 지원하면 초당 마이크로세컨드까지 값이 들어간다 (1 / 1000000)
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		_isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);

		//초당 시간 계산 범위
		_timeScale = 1.0f / _periodFrequency;
	}
	else
	{
		_isHardware = false;
		//밀리세컨드 단위의 시간으로 카운트 한다
		_lastTime = timeGetTime();
		_timeScale = 0.001f;
	}

	//타이머 과련 변수들 초기화
	_frameRate = 0;
	_FPSFrameCount = 0;
	_FPSTimeElapsed = 0.0f;
	_worldTime = 0;

	return S_OK;
}

//현재시간 계산
void timer::tick(float lockFPS)
{
	//고성능 타이머를 지원한다면
	if (_isHardware)
	{
		//마이크로세컨 단위로 계산한다 (1 / 1000000)
		QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	}
	else
	{
		//고성능 타이머를 지원하지 않기때문에 걍 time함수를 이용한다 (1 / 1000)
		_curTime = timeGetTime();
	}

	//마지막 시간과 현재시간의 경과량
	_timeElapsed = (_curTime - _lastTime) * _timeScale;

	if (lockFPS > 0.0f)
	{
		while (_timeElapsed < (1.0f / lockFPS))
		{
			if (_isHardware) QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			else _curTime = timeGetTime();
		
			//마지막 시간과 현재시간의 경과량
			_timeElapsed = (_curTime - _lastTime) * _timeScale;
		}
	}

	_lastTime = _curTime;
	_FPSFrameCount++;
	_FPSTimeElapsed += _timeElapsed;
	_worldTime += _timeElapsed;

	//프레임 초기화를 1초마다 진행하기
	if (_FPSTimeElapsed > 1.0f)
	{
		_frameRate = _FPSFrameCount;
		_FPSFrameCount = 0;
		_FPSTimeElapsed = 0.0f;
	}
}

//현재 FPS 가져오기
unsigned long timer::getFrameRate(char* str) const
{
	if (str != NULL)
	{
		wsprintf(str, "FPS : %d", _frameRate);
	}

	return _frameRate;
}
