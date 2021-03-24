#pragma once
#include "singletonBase.h"
#include "inc/fmod.hpp"						//fmod.hpp 추가
#pragma comment(lib, "lib/fmodex_vc.lib")	//lib 링크
using namespace FMOD;						//FMOD 네임스페이스 사용
//==================================================================
//		## soundManager ## (사운드 매니져)
//==================================================================

//채널버퍼, 사운드버퍼
#define EXTRACHANNELBUFFER 5
#define SOUNDBUFFER 30
//총사운드 버퍼설정 : 버퍼가 작아서 씹히는 문제를 해결해주기 위함
#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER

class soundManager : public singletonBase <soundManager>
{
private:
	typedef map<string, Sound**> arrSounds;
	typedef map<string, Sound**>::iterator arrSoundIter;

private:
	System* _system;			//fmod의 시스템클래스
	Sound** _sound;				//fmod의 사운드클래스
	Channel** _channel;			//fmod의 채널클래스

	arrSounds _mTotalSounds;	//맵에 담긴 사운드목록

	bool _isFadeIn = false;
	float _fadeIn = 0.0f;
	float _nowFadeIn = 0.0f;

	string _key;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//사운드 추가 (키값, 파일이름, BGM?, 루프냐?)
	void addSound(string keyName, string soundName, bool bgm = FALSE, bool loop = FALSE);

	//사운드 플레이 (키값, 볼륨) 0.0f ~ 1.0f
	void play(string keyName, float volume = 1.0f);
	//사운드 정지
	void stop(string keyName);
	//사운드 일시정지
	void pause(string keyName);
	//사운드 다시재생
	void resume(string keyName);

	//플레이 중이냐?
	bool isPlaySound(string keyName);
	//일시정지 중이냐?
	bool isPauseSound(string keyName);

	//볼륨 조절
	void setVolume(string keyName, float volume);

	//fadeIn, fadeOut
	void soundFadeIn(string keyName, float volume);

	soundManager();
	~soundManager();
};

