#pragma once
#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "RectF.h"
class GameObject;
class Camera {
private:
	static Camera* __instance;
	Bound cameraBound;
	bool isAllowVerticalMove;
	bool isReachBossArea;
	GameObject* target;
	Camera();
public:
	static Camera* GetInstance();
	Bound GetCameraBound();
	void ResetCamera();
	bool IsReachedBossArea();
	void UpdateCameraSize(float w, float h);
	void Update(float dt, float stage=1);
	void SetFollowTarget(GameObject* target);
};

#endif // !__CAMERA_H__
