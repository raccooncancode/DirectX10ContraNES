#pragma once
#ifndef __HeadBoss3STATE_H__
#define __HeadBoss3STATE_H__

class HeadBoss3;

#include <string>
#include "GameObject.h"
using namespace std;

class HeadBoss3State {
protected:
	HeadBoss3* headBoss3;
	float holdTime;
	float maxYCanReach;
public:
	HeadBoss3State(HeadBoss3* bH) { this->headBoss3 = bH; }
	virtual void Enter() {};
	virtual void Exit() {};
	virtual void OnKeyDown(int keyCode) {};
	virtual void OnKeyUp(int keyCode) {};
	virtual void Update(float dt) {}
	virtual string GetStateName() { return ""; };
};

class HeadBoss3Default :public HeadBoss3State {
private:
public:
	HeadBoss3Default(HeadBoss3* bH) :HeadBoss3State(bH) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class HeadBoss3Shooting :public HeadBoss3State {
private:
	float shootingTime;
public:
	HeadBoss3Shooting(HeadBoss3* bH) :HeadBoss3State(bH) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class HeadBoss3Ruin :public HeadBoss3State {
private:
public:
	HeadBoss3Ruin(HeadBoss3* bH) :HeadBoss3State(bH) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class HeadBoss3Dead :public HeadBoss3State {
private:
public:
	HeadBoss3Dead(HeadBoss3* bH) :HeadBoss3State(bH) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

#endif // !__HeadBoss3STATE_H__
