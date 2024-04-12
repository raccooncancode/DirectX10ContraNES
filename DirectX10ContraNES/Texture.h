#pragma once
#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <d3d10.h>
#include <D3DX10.h>

//
// Warpper class to simplify texture manipulation. See also CGame::LoadTexture
//
class CTexture
{
protected:
	ID3D10Texture2D* _tex;
	ID3D10ShaderResourceView* _rsview;
	int _width;
	int _height;
public:
	CTexture()
	{
		_tex = NULL;
		_rsview = NULL;
		_width = -1;
		_height = -1;
	}

	CTexture(ID3D10Texture2D* tex, ID3D10ShaderResourceView* rsview)
	{
		this->_tex = tex;
		this->_rsview = rsview;

		D3D10_TEXTURE2D_DESC desc;
		this->_tex->GetDesc(&desc);
		this->_width = desc.Width;
		this->_height = desc.Height;
	}

	ID3D10ShaderResourceView* getShaderResourceView() { return this->_rsview; }

	int getWidth() { return this->_width; }
	int getHeight() { return this->_height; }

	~CTexture()
	{
		if (_rsview != NULL) this->_rsview->Release();
		if (_tex != NULL) this->_tex->Release();
	}
};

typedef CTexture* LPTEXTURE;

#endif // !__TEXTURE_H__