#pragma once
#ifndef __ItemANIMATION_H__
#define __ItemANIMATION_H__

class Item;

#include "GameAnimation.h"

class ItemAnimation :public GameAnimation {
private:
	Item* item;
public:
	ItemAnimation(Item* i) { this->item = i; }
	void Update(float dt, GameObject* o = NULL, bool isDead = false);
};

#endif // !__ItemANIMATION_H__
