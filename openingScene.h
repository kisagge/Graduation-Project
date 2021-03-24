#pragma once
#include "gameNode.h"
class openingScene : public gameNode
{
private:
	image* _bg;
	image* _startButton;
	int _startBtnX, _startBtnY;
	RECT _startBtnRect;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	
	void clickSound()
	{
		if (SOUNDMANAGER->isPlaySound("âŬ��1"))
		{
			SOUNDMANAGER->stop("âŬ��1");
			SOUNDMANAGER->play("âŬ��1", 0.5f);
		}
		else SOUNDMANAGER->play("âŬ��1", 0.5f);
	}

	openingScene();
	~openingScene();
};

