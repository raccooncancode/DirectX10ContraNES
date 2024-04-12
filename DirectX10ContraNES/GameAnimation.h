#pragma once
#ifndef __GAMEANIMATION_H__
#define __GAMEANIMATION_H__

#include "Animation.h"
#include <map>
#include <string>

class GameAnimation {
protected:
	std::map<std::string, LPANIMATION> pAnimations;
	std::string pCurrentAnimation;
	std::string currentAnimationName;
public:
	virtual void GetFrameResolution(float& w, float& h) {
		pAnimations[pCurrentAnimation]->GetFrameResolution(w, h);
	}
	virtual void AddAnimation(std::string aniName, LPANIMATION ani) {
		pAnimations[aniName] = ani;
	}
	virtual void SetAnimation(std::string ani) {
		this->currentAnimationName = ani;
		this->pCurrentAnimation = currentAnimationName;
	}
	virtual std::string GetAnimation() {
		return this->currentAnimationName;
	}
	void Update(float dt, GameObject* o=NULL , bool isDead=false) {
		this->pAnimations[pCurrentAnimation]->Update(dt,o,isDead);
	}
	void Render(float x, float y) {
		this->pAnimations[pCurrentAnimation]->Render(x, y);
	}
};

#endif // !__GAMEANIMATION_H__
