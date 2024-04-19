#pragma once
#ifndef __StoneSTATE_H__
#define __StoneSTATE_H__

class Stone;

#include <string>
#include "GameObject.h"
using namespace std;

class StoneState {
protected:
	Stone* stone;
	float holdTime;
	float maxYCanReach;
public:
	StoneState(Stone* bH) { this->stone = bH; }
	virtual void Enter() {};
	virtual void Exit() {};
	virtual void OnKeyDown(int keyCode) {};
	virtual void OnKeyUp(int keyCode) {};
	virtual void Update(float dt) {}
	virtual string GetStateName() { return ""; };
};

class StoneDefault :public StoneState {
private:
public:
	StoneDefault(Stone* bH) :StoneState(bH) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class StoneRuin :public StoneState {
private:
public:
	StoneRuin(Stone* bH) :StoneState(bH) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class StoneDead :public StoneState {
private:
public:
	StoneDead(Stone* bH) :StoneState(bH) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

#endif // !__StoneSTATE_H__
