#pragma once
#ifndef __BodyBoss3STATE_H__
#define __BodyBoss3STATE_H__

class BodyBoss3;

#include <string>
#include "GameObject.h"
using namespace std;

class BodyBoss3State {
protected:
	BodyBoss3* bodyBoss3;
	float holdTime;
	float maxYCanReach;
public:
	BodyBoss3State(BodyBoss3* bH) { this->bodyBoss3 = bH; }
	virtual void Enter() {};
	virtual void Exit() {};
	virtual void OnKeyDown(int keyCode) {};
	virtual void OnKeyUp(int keyCode) {};
	virtual void Update(float dt) {}
	virtual string GetStateName() { return ""; };
};

class BodyBoss3Default :public BodyBoss3State {
private:
public:
	BodyBoss3Default(BodyBoss3* bH) :BodyBoss3State(bH) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class BodyBoss3Ruin :public BodyBoss3State {
private:
public:
	BodyBoss3Ruin(BodyBoss3* bH) :BodyBoss3State(bH) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class BodyBoss3Dead :public BodyBoss3State {
private:
public:
	BodyBoss3Dead(BodyBoss3* bH) :BodyBoss3State(bH) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

#endif // !__BodyBoss3STATE_H__
