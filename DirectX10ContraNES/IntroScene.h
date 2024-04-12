#pragma once
#ifndef __INTROSCENE_H__
#define __INTROSCENE_H__

#include "Scene.h"
#include "Game.h"
#include "Sprite.h"
class IntroScene :public Scene {
private:
	LPTEXTURE introTexture;
	LPSPRITE introBackGround;
public:
	IntroScene();
	void Update(float dt) override;
	void Render() override;
	void LoadResource();
};

#endif // !__INTROSCENE_H__
