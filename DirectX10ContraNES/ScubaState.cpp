#include "Scuba.h"
#include "ScubaState.h"


void ScubaHiding::Enter() {
}
void ScubaHiding::Exit() {
}
void ScubaHiding::Update(float dt) {
}
void ScubaHiding::OnKeyDown(int keyCode) {
}
void ScubaHiding::OnKeyUp(int keyCode) {

}
string ScubaHiding::GetStateName() {
	return "ScubaHiding";
}


void ScubaShowing::Enter() {
	this->holdTime = 0;
	//this->Scuba->isInShootRange = true;
	this->scuba->isOpened = true;
}
void ScubaShowing::Exit() {
	this->holdTime = 0;
}
void ScubaShowing::Update(float dt) {
	if (this->holdTime < 500) {
		this->holdTime += dt;
	}
	else
	{
		this->scuba->isInShootRange = true;
		this->scuba->SetState("ScubaShooting", "ScubaShooting");
		this->holdTime = 0;
	}
}
void ScubaShowing::OnKeyDown(int keyCode) {
}
void ScubaShowing::OnKeyUp(int keyCode) {

}
string ScubaShowing::GetStateName() {
	return "ScubaShowing";
}

void ScubaShooting::Enter() {
}
void ScubaShooting::Exit() {
}
void ScubaShooting::Update(float dt) {
	if (this->holdTime < 1000) {
		holdTime += dt;
	}
	else
	{
		this->scuba->SetAngle(D3DX_PI/2);
		float bx, by;
		Bound b = this->scuba->GetBound();
		bx = b->x + b->w/2;
		by = b->y + b->h + 3 ;
		if (this->scuba->isInShootRange)
			this->scuba->CreateBullet(bx, by);
		this->holdTime = 0;
	}
}
void ScubaShooting::OnKeyDown(int keyCode) {
}
void ScubaShooting::OnKeyUp(int keyCode) {

}
string ScubaShooting::GetStateName() {
	return "ScubaShooting";
}

void ScubaDead::Enter() {
	this->scuba->isDead = true;
}
void ScubaDead::Exit() {
}
void ScubaDead::Update(float dt) {
}
void ScubaDead::OnKeyDown(int keyCode) {
}
void ScubaDead::OnKeyUp(int keyCode) {

}
string ScubaDead::GetStateName() {
	return "Dead";
}