#pragma once
#ifndef __PreStage3Scene_H__
#define __PreStage3Scene_H__

#include "Scene.h"
#include "Game.h"
#include "Sprite.h"
class PreStage3Scene :public Scene {
private:
	LPTEXTURE preStageTexture;
	LPSPRITE preStageBackground;
	float w, h;
	int score, life, highestScore;
	float time;
	float flashingTime;
	bool isFlashed;
public:
	bool isDoneAnimation;
	PreStage3Scene();
	void SetStatus(int score,int highestScore, int life);
	void Update(float dt) override;
	void Render() override;
	void LoadResource();
};

#endif // !__PreStage3Scene_H__
