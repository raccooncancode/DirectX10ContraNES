#pragma once
#ifndef __DynamicPlatformSTATE_H__
#define __DynamicPlatformSTATE_H__

class DynamicPlatform;

#include <string>
#include "GameObject.h"
using namespace std;

class DynamicPlatformState {
protected:
	DynamicPlatform* dynamicPlatform;
	float holdTime;
	float maxYCanReach;
public:
	DynamicPlatformState(DynamicPlatform* bH) { this->dynamicPlatform = bH; }
	virtual void Enter() {};
	virtual void Exit() {};
	virtual void OnKeyDown(int keyCode) {};
	virtual void OnKeyUp(int keyCode) {};
	virtual void Update(float dt) {}
	virtual string GetStateName() { return ""; };
};

class DynamicPlatformDefault :public DynamicPlatformState {
private:
public:
	DynamicPlatformDefault(DynamicPlatform* bH) :DynamicPlatformState(bH) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class DynamicPlatformRuin :public DynamicPlatformState {
private:
public:
	DynamicPlatformRuin(DynamicPlatform* bH) :DynamicPlatformState(bH) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class DynamicPlatformDead :public DynamicPlatformState {
private:
public:
	DynamicPlatformDead(DynamicPlatform* bH) :DynamicPlatformState(bH) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

#endif // !__DynamicPlatformSTATE_H__
