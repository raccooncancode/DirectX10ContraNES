#pragma once
#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__

#include <unordered_map>
#include <d3dx10.h>

#include "Texture.h"

using namespace std;

class TextureManager
{
	static TextureManager* __instance;

	unordered_map<int, LPTEXTURE> textures;

public:
	TextureManager();
	void Add(int id, LPCWSTR filePath);
	LPTEXTURE Get(int i);
	static TextureManager* GetInstance();
};
#endif // !__TEXTURES_H__