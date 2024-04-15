#include "Cannon.h"
#include "CannonState.h"


void CannonHiding::Enter() {
}
void CannonHiding::Exit() {
}
void CannonHiding::Update(float dt) {
}
void CannonHiding::OnKeyDown(int keyCode) {
}
void CannonHiding::OnKeyUp(int keyCode) {

}
string CannonHiding::GetStateName() {
	return "CannonHiding";
}


void CannonShowing::Enter() {
	this->holdTime = 0;
	//this->cannon->isInShootRange = true;
	this->cannon->isOpened = true;
}
void CannonShowing::Exit() {
	this->holdTime = 0;
}
void CannonShowing::Update(float dt) {
	if (this->holdTime < 500) {
		this->holdTime += dt;
	}
	else
	{
		this->cannon->isInShootRange = true;
		this->cannon->SetState("CannonShooting", "CannonShooting");
		this->holdTime = 0;
	}
}
void CannonShowing::OnKeyDown(int keyCode) {
}
void CannonShowing::OnKeyUp(int keyCode) {

}
string CannonShowing::GetStateName() {
	return "CannonShowing";
}

void CannonShooting::Enter() {
}
void CannonShooting::Exit() {
}
void CannonShooting::Update(float dt) {
	if (this->holdTime < 1000) {
		holdTime += dt;
	}
	else
	{
		this->cannon->SetAngle(D3DX_PI);
		float bx, by;
		Bound b = this->cannon->GetBound();
		bx = b->x - 3;
		by = b->y +b->h/2 + 3;
		if (this->cannon->isInShootRange)
			this->cannon->CreateBullet(bx, by);
		this->holdTime = 0;
	}
}
void CannonShooting::OnKeyDown(int keyCode) {
}
void CannonShooting::OnKeyUp(int keyCode) {

}
string CannonShooting::GetStateName() {
	return "CannonShooting";
}

void CannonDead::Enter() {
	this->cannon->isDead = true;
}
void CannonDead::Exit() {
}
void CannonDead::Update(float dt) {
}
void CannonDead::OnKeyDown(int keyCode) {
}
void CannonDead::OnKeyUp(int keyCode) {

}
string CannonDead::GetStateName() {
	return "Dead";
}