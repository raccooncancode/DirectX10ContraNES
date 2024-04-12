#include "Sprite.h"

CSprite::CSprite(int left, int top, int width, int height, LPTEXTURE tex)
{
	this->left = left;
	this->top = top;
	this->width = width;
	this->height = height;
	this->texture = tex;

	// Set the sprite’s shader resource view
	sprite.pTexture = tex->getShaderResourceView();

	sprite.TexCoord.x = this->left / (float)tex->getWidth();
	sprite.TexCoord.y = this->top / (float)tex->getHeight();


	sprite.TexSize.x = this->width / (float)tex->getWidth();
	sprite.TexSize.y = this->height / (float)tex->getHeight();

	sprite.ColorModulate = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	sprite.TextureIndex = 0;

	D3DXMatrixScaling(&this->matScaling, (FLOAT)this->width, (FLOAT)this->height, 1.0f);
}

void CSprite::Draw(float x, float y)
{
	CGame* g = CGame::GetInstance();
	Camera* camera = Camera::GetInstance();
	Bound cameraBound = camera->GetCameraBound();
	D3DXMATRIX matTranslation;
	float cx, cy;
	x = (FLOAT)floor(x);
	y = (FLOAT)floor(y);
	cx = (FLOAT)floor(cameraBound->x);
	cy = (FLOAT)floor(cameraBound->y);
	D3DXMatrixTranslation(&matTranslation, (FLOAT)x - cx, (FLOAT)y - cy, 0.1f);

	this->sprite.matWorld = this->matScaling * matTranslation;
	g->GetSpriteHandler()->DrawSpritesImmediate(&sprite, 1, 0, 0);
}

