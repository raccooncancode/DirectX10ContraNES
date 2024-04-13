#pragma once
#ifndef __SCENE_H__
#define __SCENE_H__

#include "GameObject.h"

class Scene {
protected:
public:
	~Scene(){}
	virtual void AddMovingObject(GameObject* o){}
	virtual void AddStaticObject(GameObject* o){}
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual void Clear(){}
};
#endif // !__SCENE_H__
