#pragma once
#ifndef __ANIMATIONADDONMANAGER_H__
#define __ANIMATIONADDONMANAGER_H__

#include "Sprite.h"
#include "Animation.h"
#include "tinyxml2.h"
#include <unordered_map>

class AnimationAddOnManager {
private:
	std::unordered_map<std::string, LPANIMATION> animations;
	static AnimationAddOnManager* __instance;
public:
	static AnimationAddOnManager* GetInstance();
	void AddAnimation(std::string name, LPCSTR fileName,int texId);
	LPANIMATION GetAnimation(std::string name);
};


#endif // !__ANIMATIONADDONHELPER_H__
