#pragma once
#ifndef __SOLDIERSTATE_H__
#define __SOLDIERSTATE_H__

class Soldier;
#include <string>
#include "GameObject.h"
using namespace std;

class SoldierState {
protected:
	Soldier* soldier;
public:
	SoldierState(Soldier* s) { this->soldier = s; }
	virtual void Enter() {};
	virtual void Exit() {};
	virtual void OnKeyDown(int keyCode) {};
	virtual void OnKeyUp(int keyCode) {};
	virtual void Update(float dt) {}
	virtual string GetStateName() { return ""; };
};

class SoldierShooting :public SoldierState {
private:
public:
	SoldierShooting(Soldier* soldier) :SoldierState(soldier) {
	}
	void Enter()override;
	void Exit()override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class SoldierRunning :public SoldierState {
private:
public:
	SoldierRunning(Soldier* soldier) :SoldierState(soldier) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float) override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class SoldierJumping :public SoldierState {
private:
public:
	SoldierJumping(Soldier* soldier) :SoldierState(soldier) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float) override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class SoldierLaying :public SoldierState {
private:
public:
	SoldierLaying(Soldier* soldier) :SoldierState(soldier) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float) override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class SoldierDead :public SoldierState {
private:
public:
	SoldierDead(Soldier* soldier) :SoldierState(soldier) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float) override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};
#endif // !__SOLDIERSTATE_H__
