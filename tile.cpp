#include "stdafx.h"
#include "tile.h"


tile::tile()
{
}


tile::~tile()
{
}

HRESULT tile::init(void)
{

	return S_OK;
}

HRESULT tile::init(int indX, int indY)
{
	_indexX = indX;
	_indexY = indY;
	
	_screenX = ISOSTARTX + TILEWIDTH * _indexX;
	_screenY = ISOSTARTY + TILEHEIGHT* _indexY;

	_tile = RectMake(_screenX, _screenY, TILEWIDTH, TILEHEIGHT);

	_move = MOVE;

	return S_OK;
}

void tile::release(void)
{

}

void tile::update(void)
{
	_tile = RectMake(ISOSTARTX + TILEWIDTH / 2, ISOSTARTY + TILEHEIGHT / 2, TILEWIDTH, TILEHEIGHT);
}

void tile::render(void)
{
	
}