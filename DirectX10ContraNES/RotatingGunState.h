#pragma once
#ifndef __ROTATINGGUNSTATE_H__
#define __ROTATINGGUNSTATE_H__

class RotatingGun;

#include <string>
#include "GameObject.h"
using namespace std;

class RotatingGunState {
protected:
	RotatingGun* rotatingGun;
	float holdTime;
	float maxYCanReach;
public:
	RotatingGunState(RotatingGun* r) { this->rotatingGun = r; }
	virtual void Enter() {};
	virtual void Exit() {};
	virtual void OnKeyDown(int keyCode) {};
	virtual void OnKeyUp(int keyCode) {};
	virtual void Update(float dt) {}
	virtual string GetStateName() { return ""; };
};

class RotatingGunOpen :public RotatingGunState {
private:
public:
	RotatingGunOpen(RotatingGun* r) :RotatingGunState(r) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class RotatingGunClose :public RotatingGunState {
private:
public:
	RotatingGunClose(RotatingGun* r) :RotatingGunState(r) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class RotatingGun0 :public RotatingGunState {
private:
public:
	RotatingGun0(RotatingGun* r) :RotatingGunState(r) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class RotatingGun45 :public RotatingGunState {
private:
public:
	RotatingGun45(RotatingGun* r) :RotatingGunState(r) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class RotatingGun90 :public RotatingGunState {
private:
public:
	RotatingGun90(RotatingGun* r) :RotatingGunState(r) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class RotatingGun135 :public RotatingGunState {
private:
public:
	RotatingGun135(RotatingGun* r) :RotatingGunState(r) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class RotatingGun180 :public RotatingGunState {
private:
public:
	RotatingGun180(RotatingGun* r) :RotatingGunState(r) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class RotatingGun225:public RotatingGunState {
private:
public:
	RotatingGun225(RotatingGun* r) :RotatingGunState(r) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class RotatingGun270 :public RotatingGunState {
private:
public:
	RotatingGun270(RotatingGun* r) :RotatingGunState(r) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class RotatingGun315 :public RotatingGunState {
private:
public:
	RotatingGun315(RotatingGun* r) :RotatingGunState(r) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class RotatingGunDead :public RotatingGunState {
private:
public:
	RotatingGunDead(RotatingGun* r) :RotatingGunState(r) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

#endif // !__ROTATINGGUNSTATE_H__
