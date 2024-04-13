#pragma once
#ifndef __BILLSTATE_H__
#define __BILLSTATE_H__

class Bill;
#include <string>
#include "GameObject.h"
using namespace std;
class BillState {
protected:
	Bill* bill;
	float holdingTime;
	float maxYCanReach;
public:
	BillState(Bill* b) {
		this->bill = b;
	}
	virtual void Enter() {};
	virtual void Exit() {};
	virtual void OnKeyDown(int keyCode){};
	virtual void OnKeyUp(int keyCode) {};
	virtual void Update(float dt){}
	virtual string GetStateName() { return ""; };
};

class BillStanding0:public BillState {
private:
public:
	BillStanding0(Bill* bill):BillState(bill) {
	}
	void Enter()override;
	void Exit()override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};
class BillStanding90:public BillState {
private:
public:
	BillStanding90(Bill* bill) :BillState(bill) {
	}
	void Enter()override;
	void Exit()override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};



class BillRunning0 :public BillState {
private:
public:
	BillRunning0(Bill* bill) :BillState(bill) {
	}
	void Enter()override;
	void Exit()override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};
class BillRunningShooting0 :public BillState {
private:

public:
	BillRunningShooting0(Bill* bill) :BillState(bill) {
	}
	void Enter()override;
	void Exit()override;
	void OnKeyDown(int keyCode)override;
	void Update(float dt)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};
class BillRunning45 :public BillState {
private:
public:
	BillRunning45(Bill* bill) :BillState(bill) {
	}
	void Enter()override;
	void Exit()override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};
class BillRunning315:public BillState {
private:
public:
	BillRunning315(Bill* bill) :BillState(bill) {
	}
	void Enter()override;
	void Exit()override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class BillJumping0:public BillState {
private:
public:
	BillJumping0(Bill* bill) :BillState(bill) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class BillFalling0:public BillState {
private:
public:
	BillFalling0(Bill* bill) :BillState(bill) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt) override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class BillLaying0:public BillState {
private:
public:
	BillLaying0(Bill* bill) :BillState(bill) {
	}
	void Enter()override;
	void Exit()override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class BillSwimming :public BillState {
private:
public:
	BillSwimming(Bill* bill) :BillState(bill) {
	}
	void Enter()override;
	void Exit()override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};
class BillSwimming0:public BillState {
private:
public:
	BillSwimming0(Bill* bill) :BillState(bill) {
	}
	void Enter()override;
	void Exit()override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};
class BillSwimming90:public BillState {
private:
public:
	BillSwimming90(Bill* bill) :BillState(bill) {
	}
	void Enter()override;
	void Exit()override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};
class BillSwimming45:public BillState {
private:
public:
	BillSwimming45(Bill* bill) :BillState(bill) {
	}
	void Enter()override;
	void Exit()override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};

class BillDead :public BillState {
private:
public:
	BillDead(Bill* bill) :BillState(bill) {
	}
	void Enter()override;
	void Exit()override;
	void Update(float dt)override;
	void OnKeyDown(int keyCode)override;
	void OnKeyUp(int keyCode)override;
	string GetStateName() override;
};


#endif // !__BILLSTATE_H__
