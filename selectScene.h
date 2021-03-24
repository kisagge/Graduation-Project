#pragma once
#include "gameNode.h"

class playerManager;

class selectScene : public gameNode
{
private:
	image* _bg;
	image* _selectButton;
	RECT _selectRC;
	int _selectX, _selectY;
	image* _openCharCard;
	image* _closeCharCard[3];
	RECT _charCardRC[3];

	RECT _selectOkRect;
	image* _selectOkImage;

	RECT _selectBackRect;
	image* _selectBackImage;

	image* _nowChar;
	int _nowCharIndex;

	image* _chaWait[2];

	float _frameCount = 0.0f;

	playerManager* _playerManagerLink;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setPlayerManagerLink(playerManager* pl){ _playerManagerLink = pl; }

	void clickSound()
	{
		if (SOUNDMANAGER->isPlaySound("창클릭1"))
		{
			SOUNDMANAGER->stop("창클릭1");
			SOUNDMANAGER->play("창클릭1", 0.5f);
		}
		else SOUNDMANAGER->play("창클릭1", 0.5f);
	}

	selectScene();
	~selectScene();
};

