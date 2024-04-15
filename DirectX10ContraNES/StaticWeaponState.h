#pragma once
#ifndef __StaticWeaponSTATE_H__
#define __StaticWeaponSTATE_H__

class StaticWeapon;

#include <string>
#include "GameObject.h"
using namespace std;

class StaticWeaponState {
protected:
	StaticWeapon* staticWeapon;
	float holdTime;
	float maxYCanReach;
public:
	StaticWeaponState(StaticWeapon* sW) { this->staticWeapon = sW; }
	virtual void Enter() {};
	virtual void Exit() {};
	virtual void OnKeyDown(int keyCode) {};
	virtual void OnKeyUp(int keyCode) {};
	virtual void Update(float dt) {}
	virtual string GetStateName() { return ""; };
};

class StaticWeaponDefault :public StaticWeaponState {
private:
public:
	StaticWeaponDefault(StaticWeapon* sW) :StaticWeaponState(sW) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class StaticWeaponDead :public StaticWeaponState {
private:
public:
	StaticWeaponDead(StaticWeapon* sW) :StaticWeaponState(sW) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

#endif // !__StaticWeaponSTATE_H__
