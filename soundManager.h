#pragma once
#include "singletonBase.h"
#include "inc/fmod.hpp"						//fmod.hpp �߰�
#pragma comment(lib, "lib/fmodex_vc.lib")	//lib ��ũ
using namespace FMOD;						//FMOD ���ӽ����̽� ���
//==================================================================
//		## soundManager ## (���� �Ŵ���)
//==================================================================

//ä�ι���, �������
#define EXTRACHANNELBUFFER 5
#define SOUNDBUFFER 30
//�ѻ��� ���ۼ��� : ���۰� �۾Ƽ� ������ ������ �ذ����ֱ� ����
#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER

class soundManager : public singletonBase <soundManager>
{
private:
	typedef map<string, Sound**> arrSounds;
	typedef map<string, Sound**>::iterator arrSoundIter;

private:
	System* _system;			//fmod�� �ý���Ŭ����
	Sound** _sound;				//fmod�� ����Ŭ����
	Channel** _channel;			//fmod�� ä��Ŭ����

	arrSounds _mTotalSounds;	//�ʿ� ��� ������

	bool _isFadeIn = false;
	float _fadeIn = 0.0f;
	float _nowFadeIn = 0.0f;

	string _key;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//���� �߰� (Ű��, �����̸�, BGM?, ������?)
	void addSound(string keyName, string soundName, bool bgm = FALSE, bool loop = FALSE);

	//���� �÷��� (Ű��, ����) 0.0f ~ 1.0f
	void play(string keyName, float volume = 1.0f);
	//���� ����
	void stop(string keyName);
	//���� �Ͻ�����
	void pause(string keyName);
	//���� �ٽ����
	void resume(string keyName);

	//�÷��� ���̳�?
	bool isPlaySound(string keyName);
	//�Ͻ����� ���̳�?
	bool isPauseSound(string keyName);

	//���� ����
	void setVolume(string keyName, float volume);

	//fadeIn, fadeOut
	void soundFadeIn(string keyName, float volume);

	soundManager();
	~soundManager();
};

