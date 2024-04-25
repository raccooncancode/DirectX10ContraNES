#pragma once
#ifndef __PreStage1Scene_H__
#define __PreStage1Scene_H__

#include "Scene.h"
#include "Game.h"
#include "Sprite.h"
class PreStage1Scene :public Scene {
private:
	LPTEXTURE preStageTexture;
	LPSPRITE preStageBackground;
	float w,h;
	int score, life;
	float time;
	float flashingTime;
	bool isFlashed;
public:
	bool isDoneAnimation;
	PreStage1Scene();
	void SetStatus(float score, float life);
	void Update(float dt) override;
	void Render() override;
	void LoadResource();
};

#endif // !__PreStage1Scene_H__
