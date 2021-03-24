#include "stdafx.h"
#include "mapClass.h"
#include "playerManager.h"

mapClass::mapClass()
{
}


mapClass::~mapClass()
{
}

HRESULT mapClass::init(void)
{
	return S_OK;
}

void mapClass::release(void)
{
	
}

void mapClass::update(void)
{
	for (_iobjVec = _objVec.begin(); _iobjVec != _objVec.end(); ++_iobjVec)
	{
		if (_iobjVec->isFrameImage)
		{
			if (0.22f + _iobjVec->frameTimeCount <= TIMEMANAGER->getWorldTime())
			{
				_iobjVec->frameTimeCount = TIMEMANAGER->getWorldTime();
				if (_iobjVec->image->getFrameX() >= _iobjVec->image->getMaxFrameX())
				{
					_iobjVec->image->setFrameX(0);
				}
				_iobjVec->image->setFrameX(_iobjVec->image->getFrameX() + 1);
			}
		}
	}
}

void mapClass::render(void)
{
	
}


void mapClass::addObj(const char* strKey, int imageIndX, int imageIndY, int collIndX, int collIndY,
	int widthTileNum, int heightTileNum, bool isFrame)
{
	tagObject temp;
	temp.image = IMAGEMANAGER->findImage(strKey);
	temp.indX = collIndX;
	temp.indY = collIndY;
	temp.x = ISOSTARTX + TILEWIDTH * collIndX;
	temp.y = ISOSTARTY + TILEHEIGHT* collIndY;
	temp.imageX = ISOSTARTX + TILEWIDTH * imageIndX;
	temp.imageY = ISOSTARTY + TILEHEIGHT* imageIndY;
	temp.collRc = RectMake(temp.x, temp.y, TILEWIDTH * widthTileNum, TILEHEIGHT * heightTileNum);
	temp.isFrameImage = isFrame;

	if (isFrame) temp.imageRc = RectMake(temp.imageX, temp.imageY, temp.image->getFrameWidth(), temp.image->getFrameHeight());
	else temp.imageRc = RectMake(temp.imageX, temp.imageY, temp.image->getWidth(), temp.image->getHeight());
	
	temp.frameTimeCount = 0.0f;

	for (int i = collIndX; i < collIndX + widthTileNum; i++)
	{
		for (int j = collIndY; j < collIndY + heightTileNum; j++)
		{
			_lobbyTile[i][j]->setMove(UNMOVE);
		}
	}

	_objVec.push_back(temp);
}