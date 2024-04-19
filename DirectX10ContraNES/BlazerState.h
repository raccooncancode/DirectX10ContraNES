#pragma once
#ifndef __BlazerSTATE_H__
#define __BlazerSTATE_H__

class Blazer;

#include <string>
#include "GameObject.h"
using namespace std;

class BlazerState {
protected:
	Blazer* blazer;
	float holdTime;
	float maxYCanReach;
public:
	BlazerState(Blazer* bH) { this->blazer = bH; }
	virtual void Enter() {};
	virtual void Exit() {};
	virtual void OnKeyDown(int keyCode) {};
	virtual void OnKeyUp(int keyCode) {};
	virtual void Update(float dt) {}
	virtual string GetStateName() { return ""; };
};

class BlazerDefault :public BlazerState {
private:
public:
	BlazerDefault(Blazer* bH) :BlazerState(bH) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class BlazerRuin :public BlazerState {
private:
public:
	BlazerRuin(Blazer* bH) :BlazerState(bH) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class BlazerDead :public BlazerState {
private:
public:
	BlazerDead(Blazer* bH) :BlazerState(bH) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

#endif // !__BlazerSTATE_H__
