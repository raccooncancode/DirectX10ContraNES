#pragma once
#ifndef __BodyBoss1STATE_H__
#define __BodyBoss1STATE_H__

class BodyBoss1;

#include <string>
#include "GameObject.h"
using namespace std;

class BodyBoss1State {
protected:
	BodyBoss1* bodyBoss1;
	float holdTime;
	float maxYCanReach;
public:
	BodyBoss1State(BodyBoss1* bH) { this->bodyBoss1 = bH; }
	virtual void Enter() {};
	virtual void Exit() {};
	virtual void OnKeyDown(int keyCode) {};
	virtual void OnKeyUp(int keyCode) {};
	virtual void Update(float dt) {}
	virtual string GetStateName() { return ""; };
};

class BodyBoss1Default :public BodyBoss1State {
private:
public:
	BodyBoss1Default(BodyBoss1* bH) :BodyBoss1State(bH) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class BodyBoss1Ruin :public BodyBoss1State {
private:
public:
	BodyBoss1Ruin(BodyBoss1* bH) :BodyBoss1State(bH) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class BodyBoss1Dead :public BodyBoss1State {
private:
public:
	BodyBoss1Dead(BodyBoss1* bH) :BodyBoss1State(bH) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

#endif // !__BodyBoss1STATE_H__
