#pragma once
//==================================================================
//		## animation ## (애니메이션 클래스)
//==================================================================

class animation
{
public:
	typedef vector<POINT> _vFrameList;	//프레임 접근을 입의접근이 가능해야 하기때문에
	typedef vector<int> _vPlayList;		//프레임 플레이 목록

private:
	int _frameNum;				//프레임 갯수
	_vFrameList _frameList;		//프레임 위치 목록
	_vPlayList _playList;		//플레이 목록

	int _frameWidth;			//프레임 가로크기
	int _frameHeight;			//프레임 세로크기
	BOOL _loop;					//루프냐?

	float _frameUpdateSec;		//프레임 업데이트 초
	float _elapsedSec;			//프레임 경과 초
	DWORD _nowPlayIdx;			//현재 플레이 인덱스(플레이 목록 값을 참조)
	BOOL _play;					//현재 플레이 여부

public:
	//초기화(이미지 전체가로크기, 전체세로크기, 한프레임 가로크기, 한프레임 세로크기)
	HRESULT init(int totalW, int totalH, int frameW, int frameH);
	void release(void);

	//처음부터 끝까지 애니메이션 셋팅하기
	void setDefPlayFrame(BOOL reverse = FALSE, BOOL loop = FALSE);
	//배열에 담아서 담겨있는것만 애니메이션 셋팅하기
	void setPlayFrame(int* playArr, int arrLen, BOOL loop = FALSE);
	//시작, 끝 구간을 정해서 구간 애니메이션 셋팅하기
	void setPlayFrame(int start, int end, BOOL reverse = FALSE, BOOL loop = FALSE);

	//초당 갱신 횟수
	void setFPS(int framePerSec);
	//프레임 업데이트 타임
	void frameUpdate(float elapsedTime);

	//플레이 시작
	void start(void);
	//플레이 정지
	void stop(void);
	//일시정지
	void pause(void);
	//다시재생
	void resume(void);

	//겟터
	inline BOOL isPlay(void) { return _play; }
	inline POINT getFramePos(void) { return _frameList[_playList[_nowPlayIdx]]; }
	inline int getFrameWidth(void) { return _frameWidth; }
	inline int getFrameHeight(void) { return _frameHeight; }

	animation();
	~animation();
};

