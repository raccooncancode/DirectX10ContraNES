#pragma once
#ifndef __creditSCENE_H__
#define __creditSCENE_H__

#include "Scene.h"
#include "Game.h"
#include "Sprite.h"
class CreditScene :public Scene {
private:
	float y;
public:
	bool isDoneAnimation;
	CreditScene();
	void Update(float dt) override;
	void Render() override;
	void LoadResource();
};

#endif // !__creditSCENE_H__
