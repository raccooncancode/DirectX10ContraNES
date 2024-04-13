#pragma once
#ifndef __SNIPERSTATE_H__
#define __SNIPERSTATE_H__
class Sniper;

#include <string>
#include "GameObject.h"
using namespace std;

class SniperState {
protected:
	Sniper* sniper;
	float holdTime;
	float maxYCanReach;
public:
	SniperState(Sniper* s) { this->sniper = s; }
	virtual void Enter() {};
	virtual void Exit() {};
	virtual void OnKeyDown(int keyCode) {};
	virtual void OnKeyUp(int keyCode) {};
	virtual void Update(float dt) {}
	virtual string GetStateName() { return ""; };
};

class SniperShooting0:public SniperState {
private:
public:
	SniperShooting0(Sniper* Sniper) :SniperState(Sniper) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class SniperShooting45:public SniperState {
private:
public:
	SniperShooting45(Sniper* Sniper) :SniperState(Sniper) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class SniperShooting315:public SniperState {
private:
public:
	SniperShooting315(Sniper* Sniper) :SniperState(Sniper) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class SniperHidingShooting0 :public SniperState {
private:
public:
	SniperHidingShooting0(Sniper* Sniper) :SniperState(Sniper) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};


class SniperDead :public SniperState {
private:
public:
	SniperDead(Sniper* Sniper) :SniperState(Sniper) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float) override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

#endif // !__SNIPERSTATE_H__
