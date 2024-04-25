#pragma once
#ifndef __GameOverScene_H__
#define __GameOverScene_H__

#include "Scene.h"
#include "Game.h"
#include "Sprite.h"
class GameOverScene :public Scene {
private:
	LPTEXTURE preStageTexture;
	LPSPRITE preStageBackground;
	float w, h;
	int score, life;
	float time;
	float flashingTime;
	bool isFlashed;
public:
	bool isDoneAnimation;
	GameOverScene();
	void SetStatus(float score, float life);
	void Update(float dt) override;
	void Render() override;
	void LoadResource();
};

#endif // !__GameOverScene_H__
