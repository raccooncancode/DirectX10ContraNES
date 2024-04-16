#pragma once
#ifndef __GunBoss1STATE_H__
#define __GunBoss1STATE_H__

class GunBoss1;

#include <string>
#include "GameObject.h"
using namespace std;

class GunBoss1State {
protected:
	GunBoss1* gunBoss1;
	float holdTime;
	float maxYCanReach;
public:
	GunBoss1State(GunBoss1* bH) { this->gunBoss1 = bH; }
	virtual void Enter() {};
	virtual void Exit() {};
	virtual void OnKeyDown(int keyCode) {};
	virtual void OnKeyUp(int keyCode) {};
	virtual void Update(float dt) {}
	virtual string GetStateName() { return ""; };
};

class GunBoss1Default :public GunBoss1State {
private:
public:
	GunBoss1Default(GunBoss1* bH) :GunBoss1State(bH) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class GunBoss1Ruin :public GunBoss1State {
private:
public:
	GunBoss1Ruin(GunBoss1* bH) :GunBoss1State(bH) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class GunBoss1Dead :public GunBoss1State {
private:
public:
	GunBoss1Dead(GunBoss1* bH) :GunBoss1State(bH) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

#endif // !__GunBoss1STATE_H__
