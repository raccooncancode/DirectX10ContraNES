#include "GameObject.h"
#include "Camera.h"
#include "Bill.h"
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

void Camera::ResetCamera() {
	this->target = NULL;
	this->cameraBound->x = 0;
	this->cameraBound->y = 0;
	this->isReachBossArea = false;
}

Bound Camera::GetCameraBound() { return this->cameraBound; }

void Camera::UpdateCameraSize(float w, float h) {
	this->cameraBound->UpdateBoundSize(w, h);
}

void Camera::Update(float dt, float stage) {
	this->currentStage = stage;
	if (this->target != NULL) {
		float cx, cy,destX,destY;
		if (this->target->GetType() == "Player") {
			cx = this->target->GetBound()->x;
			cy = this->target->GetBound()->y;


			cx -= this->GetCameraBound()->w / 2 - 30;
			cy -= this->GetCameraBound()->h / 2 - 30;

			if (cx < 0) cx = 0;
			if (cy < 0)	cy = 0;

			if (stage == 1)
				this->cameraBound->UpdateBoundLocation(cx, 15);
			else
				this->cameraBound->UpdateBoundLocation(0, cy);
		}
		else {
			destX = this->target->GetBound()->x - 170;
			destY = this->target->GetBound()->y-20;

			if (stage == 1) {
				if (this->cameraBound->x < destX)
					this->cameraBound->x += 0.05* dt;
				else
					this->cameraBound->x = destX;
			}
			else {
				if (this->cameraBound->y < destY)
					this->cameraBound->y += 0.05 * dt;
				else
					this->cameraBound->y = destY;
			}
			cx = this->cameraBound->x;
			cy = this->cameraBound->y;
			if (stage==3 && cy == destY) {
				this->isReachBossArea = true;
			}
			if (stage == 1 && cx == destX) {
				this->isReachBossArea = true;
			}
		}

		//DebugOut(L"\n camera X: %f , camera Y: %f", this->cameraBound->x, this->cameraBound->y);
	}
}

bool Camera::IsReachedBossArea() {
	return this->isReachBossArea;
}

void Camera::SetFollowTarget(GameObject* target) {
	this->target = target;
}