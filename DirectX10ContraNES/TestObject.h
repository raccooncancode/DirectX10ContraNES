#pragma once
#ifndef __TESTOBJECT_H__
#define __TESTOBJECT_H__

#include "GameObject.h"
#include "IControlable.h"
#include "InputManager.h"
#include <vector>

using namespace std;
class TestObject : public GameObject , public IControlable{
private:
	bool allowMove = false;
public:
	bool isOnGround;
	TestObject(bool canControl) :GameObject(2, "2", "block") {
		if (canControl) {
			allowMove = canControl;
			SetSpeed(0.1f, 0.1f);
			InputManager::GetInstance()->RegisterListener(this);
		}
	}

	void Update(float dt,vector<GameObject*>* objects) override{
		Collision::GetInstance()->Proccess(this, objects, dt);
	}

	void OnNoCollision(float dt) {
		this->objectBound->x += vx *nx* dt;
		this->objectBound->y += vy *ny* dt;
	}
	void OnCollisionWith(CollisionEvent* e, float dt) {
		if (allowMove) {

			if (e->ny > 0) {
			DebugOut(L"\n From top");
			}
		}
	}
	void Render() override{
		RenderBoundingBox();
	}
	void OnKeyDown(int keyCode) override {
		allowMove = true;
		if (keyCode == DIK_LEFT) {
			nx = -1;
		}
		if (keyCode == DIK_RIGHT) {
			nx = 1;
		}
		if (keyCode == DIK_UP) {
			ny = 1;
		}
		if (keyCode == DIK_DOWN) {
			ny = -1;
		}
	}
	void OnKeyUp(int keyCode) override {
		if (keyCode == DIK_LEFT) {
			nx = 0;
		}
		if (keyCode == DIK_RIGHT) {
			nx = 0;
		}
		if (keyCode == DIK_UP) {
			ny = 0;
		}
		if (keyCode == DIK_DOWN) {
			ny = 0;
		}
	}
};

#endif // !__TESTOBJECT_H__
