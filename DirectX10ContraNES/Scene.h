#pragma once
#ifndef __SCENE_H__
#define __SCENE_H__

class Scene {
protected:
public:
	~Scene(){}
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
};
#endif // !__SCENE_H__
