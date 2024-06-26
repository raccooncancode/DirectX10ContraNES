#pragma once
#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "Sprite.h"
#include <vector>
#include "GameObject.h"
class CAnimation
{
private:
	bool isDone;
	float pAnimationDuration;
	int pCurrentFrameIndex;
	int pTotalFrame;
	float pTime;
	bool canAnimate = true;
	bool isLoop = true;
	std::vector<LPSPRITE> pFrames;
public:
	CAnimation(int totalFrame, float animationDuration, bool isLoop)
	{
		this->pCurrentFrameIndex = 0;
		this->pTotalFrame = totalFrame;
		this->pTime = 0;
		this->isDone = false;
		this->pAnimationDuration = animationDuration;
		this->isLoop = isLoop;
	}
	void AddFrame(LPSPRITE spriteFrame)
	{
		pFrames.push_back(spriteFrame);
	}

	void GetFrameResolution(float& w, float& h)
	{
		pFrames[pCurrentFrameIndex]->GetSpriteResolution(w, h);
	}
	void Update(float dt ,GameObject* o , bool isDead)
	{
		pTime += dt;
		if (pTime >= pAnimationDuration)
		{
			if (isLoop)
			{
				pCurrentFrameIndex++;
				if (isDead == true)
					DebugOut(L"\nIndex: %d", pCurrentFrameIndex);
				if (isDead && pCurrentFrameIndex == pTotalFrame) {
					DebugOut(L"\nDone Dead Ani");
					o->isDeleted = true;
				}
				if (pCurrentFrameIndex == pTotalFrame) {
					this->isDone = true;
				}
				pCurrentFrameIndex %= (pTotalFrame);
			}
			else if(!isLoop && isDead) {
				o->isDeleted = true;
				return;
			}
			pTime -= pAnimationDuration;
		}
	}
	bool IsDone() {
		return this->isDone;
	}
	void Render(float x, float y)
	{
		pFrames[pCurrentFrameIndex]->Draw(x, y);
	}
	LPSPRITE GetCurrentSprite() {
		return pFrames[pCurrentFrameIndex];
	}
	D3DX10_SPRITE getSpriteStruct() { return this->pFrames[pCurrentFrameIndex]->getSpriteStruct(); }
};
typedef CAnimation* LPANIMATION;
#endif // !__ANIMATION_H__
