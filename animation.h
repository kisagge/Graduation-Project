#pragma once
//==================================================================
//		## animation ## (�ִϸ��̼� Ŭ����)
//==================================================================

class animation
{
public:
	typedef vector<POINT> _vFrameList;	//������ ������ ���������� �����ؾ� �ϱ⶧����
	typedef vector<int> _vPlayList;		//������ �÷��� ���

private:
	int _frameNum;				//������ ����
	_vFrameList _frameList;		//������ ��ġ ���
	_vPlayList _playList;		//�÷��� ���

	int _frameWidth;			//������ ����ũ��
	int _frameHeight;			//������ ����ũ��
	BOOL _loop;					//������?

	float _frameUpdateSec;		//������ ������Ʈ ��
	float _elapsedSec;			//������ ��� ��
	DWORD _nowPlayIdx;			//���� �÷��� �ε���(�÷��� ��� ���� ����)
	BOOL _play;					//���� �÷��� ����

public:
	//�ʱ�ȭ(�̹��� ��ü����ũ��, ��ü����ũ��, �������� ����ũ��, �������� ����ũ��)
	HRESULT init(int totalW, int totalH, int frameW, int frameH);
	void release(void);

	//ó������ ������ �ִϸ��̼� �����ϱ�
	void setDefPlayFrame(BOOL reverse = FALSE, BOOL loop = FALSE);
	//�迭�� ��Ƽ� ����ִ°͸� �ִϸ��̼� �����ϱ�
	void setPlayFrame(int* playArr, int arrLen, BOOL loop = FALSE);
	//����, �� ������ ���ؼ� ���� �ִϸ��̼� �����ϱ�
	void setPlayFrame(int start, int end, BOOL reverse = FALSE, BOOL loop = FALSE);

	//�ʴ� ���� Ƚ��
	void setFPS(int framePerSec);
	//������ ������Ʈ Ÿ��
	void frameUpdate(float elapsedTime);

	//�÷��� ����
	void start(void);
	//�÷��� ����
	void stop(void);
	//�Ͻ�����
	void pause(void);
	//�ٽ����
	void resume(void);

	//����
	inline BOOL isPlay(void) { return _play; }
	inline POINT getFramePos(void) { return _frameList[_playList[_nowPlayIdx]]; }
	inline int getFrameWidth(void) { return _frameWidth; }
	inline int getFrameHeight(void) { return _frameHeight; }

	animation();
	~animation();
};

