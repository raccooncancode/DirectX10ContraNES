#include "GameObject.h"
#include "Camera.h"
Camera* Camera::__instance = nullptr;

Camera::Camera() {
	this->cameraBound = new RectF(0,0, 0, 0);
	this->isReachBossArea = false;
	this->isAllowVerticalMove = true;
}

Camera* Camera::GetInstance() {
	if (__instance == nullptr)
		__instance = new Camera();
	return __instance;
}

Bound Camera::GetCameraBound() { return this->cameraBound; }

void Camera::UpdateCameraSize(float w, float h) {
	this->cameraBound->UpdateBoundSize(w, h);
}

void Camera::Update(float dt, float stage) {
	if (this->target != NULL) {
		float cx = this->target->GetBound()->x;
		float cy = this->target->GetBound()->y;


		cx -= this->GetCameraBound()->w / 2;
		cy -= this->GetCameraBound()->h / 2 ;

		if (cx < 0) cx = 0;
		if (cy < 0)	cy = 0;

		if(stage==1)
			this->cameraBound->UpdateBoundLocation(cx, 15);
		else
			this->cameraBound->UpdateBoundLocation(0, cy);
	}
}

void Camera::SetFollowTarget(GameObject* target) {
	this->target = target;
}