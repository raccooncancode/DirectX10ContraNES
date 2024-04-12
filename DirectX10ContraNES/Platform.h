#pragma once
#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include "GameObject.h"

class Platform :public GameObject {
private:

public:
	Platform(int id, string name, string type) :GameObject(id, name, type) {
	}
	void Render() override;
	void Update(float dt, vector<GameObject*>* objects = NULL) override;
};

#endif // !__PLATFORM_H__
