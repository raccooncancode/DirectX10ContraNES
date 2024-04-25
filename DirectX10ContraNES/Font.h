#pragma once
#ifndef __FONT_H__
#define __FONT_H__

#include <D3DX10.h>
#include <D3D10.h>
#include"Game.h"
#include <string>

using namespace std;
class Font {
private:
	RECT rc;
	LPCWSTR content;
	UINT display;
	D3DXCOLOR color;
public:
	void GetFontRectangle(LPCWSTR content, RECT* rect,UINT display);
	Font(LPCWSTR content,float x=0,float y=0, UINT display = DT_LEFT, D3DXCOLOR color = D3DXCOLOR(1.0f, 0.4f, 1.0f, 1.0f));
	void Render();
};

#endif // !__FONT_H__
