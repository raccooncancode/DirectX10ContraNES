#include "Game.h"
#include "Font.h"

void Font::GetFontRectangle(LPCWSTR content, RECT* rect , UINT display) {
	CGame::GetInstance()->GetFontHandler()->DrawText(NULL,
		content,
		-1,
		rect,
		DT_CALCRECT | display,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)
	);
}
Font::Font(LPCWSTR content,float x,float y, UINT display, D3DXCOLOR color) {
	SetRectEmpty(&rc);
	rc.left = x;
	rc.top = y;
	this->content = content;
	GetFontRectangle(content, &rc,display);
	this->display = display;
	this->color = color;
}
void Font::Render() {
	auto fontSprite = CGame::GetInstance()->GetSpriteHandler();
	CGame::GetInstance()->GetFontHandler()->DrawText(fontSprite,content, -1, &rc, display, color);
}