#pragma once
#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "Texture.h"
#include "Game.h"

class CSprite
{
	int left;
	int top;
	int width;
	int height;

	LPTEXTURE texture;
	D3DX10_SPRITE sprite;
	D3DXMATRIX matScaling;
public:
	CSprite(int left, int top, int width, int height, LPTEXTURE tex);

	void Draw(float x, float y);

	void GetSpriteResolution(float& w, float& h)
	{
		w = this->width;
		h = this->height;
	}
	D3DX10_SPRITE getSpriteStruct() { return this->sprite; }
};

typedef CSprite* LPSPRITE;
#endif // !__SPRITE_H__