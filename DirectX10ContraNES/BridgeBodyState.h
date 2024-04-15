#pragma once
#ifndef __BridgeBodySTATE_H__
#define __BridgeBodySTATE_H__

class BridgeBody;

#include <string>
#include "GameObject.h"
using namespace std;

class BridgeBodyState {
protected:
	BridgeBody* bridgeBody;
	float holdTime;
	float maxYCanReach;
public:
	BridgeBodyState(BridgeBody* bH) { this->bridgeBody = bH; }
	virtual void Enter() {};
	virtual void Exit() {};
	virtual void OnKeyDown(int keyCode) {};
	virtual void OnKeyUp(int keyCode) {};
	virtual void Update(float dt) {}
	virtual string GetStateName() { return ""; };
};

class BridgeBodyDefault :public BridgeBodyState {
private:
public:
	BridgeBodyDefault(BridgeBody* bH) :BridgeBodyState(bH) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class BridgeBodyDead :public BridgeBodyState {
private:
public:
	BridgeBodyDead(BridgeBody* bH) :BridgeBodyState(bH) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

#endif // !__BridgeBodySTATE_H__
