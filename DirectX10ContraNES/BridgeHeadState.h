#pragma once
#ifndef __BRIDGEHEADSTATE_H__
#define __BRIDGEHEADSTATE_H__

class BridgeHead;

#include <string>
#include "GameObject.h"
using namespace std;

class BridgeHeadState {
protected:
	BridgeHead* bridgeHead;
	float holdTime;
	float maxYCanReach;
public:
	BridgeHeadState(BridgeHead* bH) { this->bridgeHead = bH; }
	virtual void Enter() {};
	virtual void Exit() {};
	virtual void OnKeyDown(int keyCode) {};
	virtual void OnKeyUp(int keyCode) {};
	virtual void Update(float dt) {}
	virtual string GetStateName() { return ""; };
};

class BridgeHeadDefault :public BridgeHeadState {
private:
public:
	BridgeHeadDefault(BridgeHead* bH) :BridgeHeadState(bH) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class BridgeHeadDead :public BridgeHeadState {
private:
public:
	BridgeHeadDead(BridgeHead* bH) :BridgeHeadState(bH) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

#endif // !__BRIDGEHEADSTATE_H__
