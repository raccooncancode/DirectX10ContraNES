#include "HeadBoss3.h"
#include "HeadBoss3State.h"
#include "SceneManager.h"
#include "Camera.h"
#include "SoundManager.h"
void HeadBoss3Default::Enter() {
	this->holdTime = 0;
}
void HeadBoss3Default::Exit() {
	this->holdTime = 0;
}
void HeadBoss3Default::Update(float dt) {
	if (this->headBoss3->GetParent() != NULL) {
		if (this->headBoss3->GetParent()->isSeeTarget && this->headBoss3->GetParent()->IsDoneMoveTo()) {
			if (this->holdTime <= 5000) {
				this->holdTime += dt;
			}
			else {
				this->holdTime = 0;
				this->headBoss3->SetState("HeadBoss3Shooting", "HeadBoss3Shooting");
			}
		}
	}
}
void HeadBoss3Default::OnKeyDown(int keyCode) {
}
void HeadBoss3Default::OnKeyUp(int keyCode) {

}
string HeadBoss3Default::GetStateName() {
	return "HeadBoss3Default";
}

void HeadBoss3Shooting::Enter() {
	this->holdTime = 0;
	this->shootingTime = 0;
}
void HeadBoss3Shooting::Exit() {
	this->holdTime = 0;
	this->shootingTime = 0;
}
void HeadBoss3Shooting::Update(float dt) {
	if (this->holdTime <= 5000) {
		this->holdTime += dt;
		if (this->shootingTime <= 1500) {
			this->shootingTime += dt;
		}else{
			this->shootingTime = 0;
			float bx, by;
			bx = this->headBoss3->GetBound()->GetMiddleXOffset()-10;
			by = this->headBoss3->GetBound()->y;
			this->headBoss3->CreateBullet(bx,by);
		}
	}
	else {
		this->holdTime = 0;
		this->headBoss3->SetState("HeadBoss3Default", "HeadBoss3Default");
	}
}
void HeadBoss3Shooting::OnKeyDown(int keyCode) {
}
void HeadBoss3Shooting::OnKeyUp(int keyCode) {

}
string HeadBoss3Shooting::GetStateName() {
	return "HeadBoss3Shooting";
}

void HeadBoss3Ruin::Enter() {
}
void HeadBoss3Ruin::Exit() {
}
void HeadBoss3Ruin::Update(float dt) {
}
void HeadBoss3Ruin::OnKeyDown(int keyCode) {
}
void HeadBoss3Ruin::OnKeyUp(int keyCode) {

}
string HeadBoss3Ruin::GetStateName() {
	return "HeadBoss3Ruin";
}

void HeadBoss3Dead::Enter() {
	SoundManager::GetInstance()->Stop();
	SoundManager::GetInstance()->Play("destroy_boss", false, 1);
	SoundManager::GetInstance()->Play("finish_stage", false, 1);
	SceneManager::GetInstance()->scores += this->headBoss3->GetScore();
	this->headBoss3->isDead = true;
	this->headBoss3->GetParent()->isDead = true;
	this->headBoss3->isCollidable = 0;
	this->headBoss3->SetSpeed(0, 0);
}
void HeadBoss3Dead::Exit() {
}
void HeadBoss3Dead::Update(float dt) {
}
void HeadBoss3Dead::OnKeyDown(int keyCode) {
}
void HeadBoss3Dead::OnKeyUp(int keyCode) {

}
string HeadBoss3Dead::GetStateName() {
	return "Dead";
}