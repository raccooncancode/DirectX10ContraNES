#include "debug.h"
#include "Game.h"
#include "TextureManager.h"
TextureManager* TextureManager::__instance = NULL;

TextureManager::TextureManager()
{

}

TextureManager* TextureManager::GetInstance()
{
	if (__instance == NULL) __instance = new TextureManager();
	return __instance;
}

void TextureManager::Add(int id, LPCWSTR filePath)
{
	textures[id] = CGame::GetInstance()->LoadTexture(filePath);
}

LPTEXTURE TextureManager::Get(int i)
{
	return textures[i];
}
