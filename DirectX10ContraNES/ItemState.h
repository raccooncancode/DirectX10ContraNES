#pragma once
#ifndef __ItemSTATE_H__
#define __ItemSTATE_H__

class Item;

#include <string>
#include "GameObject.h"
using namespace std;

class ItemState {
protected:
	Item* item;
	float holdTime;
	float maxYCanReach;
public:
	ItemState(Item* i) { this->item = i; }
	virtual void Enter() {};
	virtual void Exit() {};
	virtual void OnKeyDown(int keyCode) {};
	virtual void OnKeyUp(int keyCode) {};
	virtual void Update(float dt) {}
	virtual string GetStateName() { return ""; };
};

class ItemDefault :public ItemState {
private:
public:
	ItemDefault(Item* c) :ItemState(c) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class ItemHiding :public ItemState {
private:
public:
	ItemHiding(Item* c) :ItemState(c) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class ItemDead :public ItemState {
private:
public:
	ItemDead(Item* c) :ItemState(c) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

#endif // !__ItemSTATE_H__
