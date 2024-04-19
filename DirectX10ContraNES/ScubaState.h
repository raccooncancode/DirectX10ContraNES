#pragma once
#ifndef __ScubaSTATE_H__
#define __ScubaSTATE_H__

class Scuba;

#include <string>
#include "GameObject.h"
using namespace std;

class ScubaState {
protected:
	Scuba* scuba;
	float holdTime;
	float maxYCanReach;
public:
	ScubaState(Scuba* c) { this->scuba = c; }
	virtual void Enter() {};
	virtual void Exit() {};
	virtual void OnKeyDown(int keyCode) {};
	virtual void OnKeyUp(int keyCode) {};
	virtual void Update(float dt) {}
	virtual string GetStateName() { return ""; };
};

class ScubaHiding :public ScubaState {
private:
public:
	ScubaHiding(Scuba* c) :ScubaState(c) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class ScubaShowing :public ScubaState {
private:
public:
	ScubaShowing(Scuba* c) :ScubaState(c) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class ScubaShooting :public ScubaState {
private:
public:
	ScubaShooting(Scuba* c) :ScubaState(c) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class ScubaDead :public ScubaState {
private:
public:
	ScubaDead(Scuba* c) :ScubaState(c) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};
#endif //!__ScubaSTATE_H__