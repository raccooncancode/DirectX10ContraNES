#include "RotatingGun.h"
#include "RotatingGunState.h"

void RotatingGunOpen::Enter() {
	this->rotatingGun->isInShootRange = true;
}
void RotatingGunOpen::Exit() {
	this->holdTime = 0;
}
void RotatingGunOpen::Update(float dt) {
	if (!this->rotatingGun->isOpened)
	{
		if (this->holdTime < 500) {
			holdTime += dt;
		}
		else
		{
			this->rotatingGun->isOpened = true;
			this->holdTime = 0;
		}
	}
}
void RotatingGunOpen::OnKeyDown(int keyCode) {
}
void RotatingGunOpen::OnKeyUp(int keyCode) {

}
string RotatingGunOpen::GetStateName() {
	return "GunOpen";
}



void RotatingGunClose::Enter() {
}
void RotatingGunClose::Exit() {
}
void RotatingGunClose::Update(float dt) {
	
}
void RotatingGunClose::OnKeyDown(int keyCode) {
}
void RotatingGunClose::OnKeyUp(int keyCode) {

}
string RotatingGunClose::GetStateName() {
	return "GunClose";
}

void RotatingGun0::Enter() {
}
void RotatingGun0::Exit() {
}
void RotatingGun0::Update(float dt) {
	if (this->holdTime < 1000) {
		holdTime += dt;
	}
	else
	{
		this->rotatingGun->SetAngle(0);
		float bx, by;
		Bound b = this->rotatingGun->GetBound();
		bx = b->x + b->w +  3;
		by = b->y + b->h / 2 + 3;
		if (this->rotatingGun->isInShootRange)
			this->rotatingGun->CreateBullet(bx, by);
		this->holdTime = 0;
	}
}
void RotatingGun0::OnKeyDown(int keyCode) {
}
void RotatingGun0::OnKeyUp(int keyCode) {

}
string RotatingGun0::GetStateName() {
	return "GunRotate0";
}

void RotatingGun45::Enter() {
}
void RotatingGun45::Exit() {
}
void RotatingGun45::Update(float dt) {
	if (this->holdTime < 1000) {
		holdTime += dt;
	}
	else
	{
		this->rotatingGun->SetAngle(D3DX_PI/4);
		float bx, by;
		Bound b = this->rotatingGun->GetBound();
		bx = b->x + b->w + 3;
		by = b->y + b->h  + 3;
		if (this->rotatingGun->isInShootRange)
			this->rotatingGun->CreateBullet(bx, by);
		this->holdTime = 0;
	}
}
void RotatingGun45::OnKeyDown(int keyCode) {
}
void RotatingGun45::OnKeyUp(int keyCode) {

}
string RotatingGun45::GetStateName() {
	return "GunRotate45";
}

void RotatingGun90::Enter() {
}
void RotatingGun90::Exit() {
}
void RotatingGun90::Update(float dt) {
	if (this->holdTime < 1000) {
		holdTime += dt;
	}
	else
	{
		this->rotatingGun->SetAngle(D3DX_PI/2);
		float bx, by;
		Bound b = this->rotatingGun->GetBound();
		bx = b->x + b->w/2;
		by = b->y + b->h + 3;
		if (this->rotatingGun->isInShootRange)
			this->rotatingGun->CreateBullet(bx, by);
		this->holdTime = 0;
	}
}
void RotatingGun90::OnKeyDown(int keyCode) {
}
void RotatingGun90::OnKeyUp(int keyCode) {

}
string RotatingGun90::GetStateName() {
	return "GunRotate90";
}

void RotatingGun135::Enter() {
}
void RotatingGun135::Exit() {
}
void RotatingGun135::Update(float dt) {
	if (this->holdTime < 1000) {
		holdTime += dt;
	}
	else
	{
		this->rotatingGun->SetAngle(D3DX_PI - D3DX_PI / 4);
		float bx, by;
		Bound b = this->rotatingGun->GetBound();
		bx = b->x -3;
		by = b->y + b->h + 3;
		if (this->rotatingGun->isInShootRange)
			this->rotatingGun->CreateBullet(bx, by);
		this->holdTime = 0;
	}
}
void RotatingGun135::OnKeyDown(int keyCode) {
}
void RotatingGun135::OnKeyUp(int keyCode) {

}
string RotatingGun135::GetStateName() {
	return "GunRotate135";
}

void RotatingGun180::Enter() {
}
void RotatingGun180::Exit() {
}
void RotatingGun180::Update(float dt) {
	if (this->holdTime < 1000) {
		holdTime += dt;
	}
	else
	{
		this->rotatingGun->SetAngle(D3DX_PI);
		float bx, by;
		Bound b = this->rotatingGun->GetBound();
		bx = b->x - 3;
		by = b->y + b->h/2;
		if (this->rotatingGun->isInShootRange)
			this->rotatingGun->CreateBullet(bx, by);
		this->holdTime = 0;
	}
}
void RotatingGun180::OnKeyDown(int keyCode) {
}
void RotatingGun180::OnKeyUp(int keyCode) {

}
string RotatingGun180::GetStateName() {
	return "GunRotate180";
}

void RotatingGun225::Enter() {
}
void RotatingGun225::Exit() {
}
void RotatingGun225::Update(float dt) {
	if (this->holdTime < 1000) {
		holdTime += dt;
	}
	else
	{
		this->rotatingGun->SetAngle(D3DX_PI + D3DX_PI / 4);
		float bx, by;
		Bound b = this->rotatingGun->GetBound();
		bx = b->x - 3;
		by = b->y  - 3;
		if (this->rotatingGun->isInShootRange)
			this->rotatingGun->CreateBullet(bx, by);
		this->holdTime = 0;
	}
}
void RotatingGun225::OnKeyDown(int keyCode) {
}
void RotatingGun225::OnKeyUp(int keyCode) {

}
string RotatingGun225::GetStateName() {
	return "GunRotate225";
}

void RotatingGun270::Enter() {
}
void RotatingGun270::Exit() {
}
void RotatingGun270::Update(float dt) {
	if (this->holdTime < 1000) {
		holdTime += dt;
	}
	else
	{
		this->rotatingGun->SetAngle(D3DX_PI + D3DX_PI / 2);
		float bx, by;
		Bound b = this->rotatingGun->GetBound();
		bx = b->x + b->w / 2;
		by = b->y - 3;
		if (this->rotatingGun->isInShootRange)
			this->rotatingGun->CreateBullet(bx, by);
		this->holdTime = 0;
	}
}
void RotatingGun270::OnKeyDown(int keyCode) {
}
void RotatingGun270::OnKeyUp(int keyCode) {

}
string RotatingGun270::GetStateName() {
	return "GunRotate270";
}

void RotatingGun315::Enter() {
}
void RotatingGun315::Exit() {
}
void RotatingGun315::Update(float dt) {
	if (this->holdTime < 1000) {
		holdTime += dt;
	}
	else
	{
		this->rotatingGun->SetAngle(-D3DX_PI / 4);
		float bx, by;
		Bound b = this->rotatingGun->GetBound();
		bx = b->x + b->w + 3;
		by = b->y - 3;
		if (this->rotatingGun->isInShootRange)
			this->rotatingGun->CreateBullet(bx, by);
		this->holdTime = 0;
	}
}
void RotatingGun315::OnKeyDown(int keyCode) {
}
void RotatingGun315::OnKeyUp(int keyCode) {

}
string RotatingGun315::GetStateName() {
	return "GunRotate315";
}

void RotatingGunDead::Enter() {
	this->rotatingGun->isDead = true;
}
void RotatingGunDead::Exit() {
}
void RotatingGunDead::Update(float dt) {
}
void RotatingGunDead::OnKeyDown(int keyCode) {
}
void RotatingGunDead::OnKeyUp(int keyCode) {

}
string RotatingGunDead::GetStateName() {
	return "Dead";
}