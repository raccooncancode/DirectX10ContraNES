#pragma once
#ifndef __BILLANIMATION_H__
#define __BILLANIAMTION_H__

class Bill;
#include "GameAnimation.h"

class BillAnimation: public GameAnimation {
private:
	Bill* bill;
public:
	BillAnimation(Bill* b) { this->bill = b; }
	void Update(float dt,GameObject* o = NULL,bool isDead = false);
};

#endif // !__BILLANIMATION_H__
