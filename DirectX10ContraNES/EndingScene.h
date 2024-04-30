#pragma once
#ifndef __EndingScene_H__
#define __EndingScene_H__

#include "Scene.h"
#include "Game.h"
#include "Animation.h"
class EndingScene :public Scene {
private:
	LPTEXTURE endingTexture;
	LPANIMATION endingAnimation;
	float x,y;
public:
	bool isDoneAnimation;
	EndingScene();
	void Update(float dt) override;
	void Render() override;
	void LoadResource();
};

#endif // !__EndingScene_H__
