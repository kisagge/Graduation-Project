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
		if (SOUNDMANAGER->isPlaySound("창클릭1"))
		{
			SOUNDMANAGER->stop("창클릭1");
			SOUNDMANAGER->play("창클릭1", 0.5f);
		}
		else SOUNDMANAGER->play("창클릭1", 0.5f);
	}

	openingScene();
	~openingScene();
};

