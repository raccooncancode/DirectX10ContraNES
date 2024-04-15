#include "Sniper.h"
#include "SniperState.h"

void SniperShooting0::Enter() {
	this->holdTime = 0;
}
void SniperShooting0::Exit() {
	this->holdTime = 0;

}
void SniperShooting0::Update(float dt) {
	if (this->sniper->isInShootRange) {
		if (this->sniper->GetTarget()->GetBound()->y > this->sniper->GetBound()->y + this->sniper->GetBound()->h) {
			this->sniper->SetState("Shooting45", Helper::aXToString(this->sniper->ax) + "Shooting45");
		}
		if (this->sniper->GetTarget()->GetBound()->y < this->sniper->GetBound()->y - this->sniper->GetBound()->h) {
			this->sniper->SetState("Shooting315", Helper::aXToString(this->sniper->ax) + "Shooting315");
		}
	}
	if (this->holdTime<1000) {
		holdTime += dt;
	}
	else
	{
		this->sniper->SetAngle(D3DX_PI);
		float bx, by;
		Bound b = this->sniper->GetBound();
		bx = b->x - 3;
		by = b->y + b->h/2 + 3;
		if(this->sniper->isInShootRange)
			this->sniper->CreateBullet(bx, by);
		this->holdTime = 0;
	}
}
void SniperShooting0::OnKeyDown(int keyCode) {
}
void SniperShooting0::OnKeyUp(int keyCode) {

}
string SniperShooting0::GetStateName() {
	return "Shooting0";
}

void SniperShooting45::Enter() {
	this->holdTime = 0;
	this->sniper->isShooting = true;
}
void SniperShooting45::Exit() {
	this->holdTime = 0;
	this->sniper->isShooting = false;
}
void SniperShooting45::Update(float dt) {
	if (this->holdTime<1000) {
		holdTime += dt;
	}
	else
	{
		this->sniper->SetAngle(D3DX_PI-D3DX_PI/4);
		float bx, by;
		Bound b = this->sniper->GetBound();
		bx = b->x - 3;
		by = b->y + b->h + 3;
		if (this->sniper->isInShootRange)
			this->sniper->CreateBullet(bx, by);
		this->holdTime = 0;
	}
}
void SniperShooting45::OnKeyDown(int keyCode) {
}
void SniperShooting45::OnKeyUp(int keyCode) {

}
string SniperShooting45::GetStateName() {
	return "Shooting45";
}

void SniperShooting315::Enter() {
	this->holdTime = 0;
	this->sniper->isShooting = true;

}
void SniperShooting315::Exit() {
	this->holdTime = 0;
	this->sniper->isShooting = false;

}
void SniperShooting315::Update(float dt) {
	/*if (this->sniper->isInShootRange) {
		if (this->sniper->GetTarget()->GetBound()->y >= this->sniper->GetBound()->y + this->sniper->GetBound()->h) {
			this->sniper->SetState("Shooting45", Helper::aXToString(this->sniper->ax) + "Shooting45");
		}
		else {
			this->sniper->SetState("Shooting0", Helper::aXToString(this->sniper->ax) + "Shooting0");
		}
	}*/
	if (this->holdTime<1000) {
		holdTime += dt;
	}
	else
	{
		this->sniper->SetAngle(D3DX_PI + D3DX_PI / 4);
		float bx, by;
		Bound b = this->sniper->GetBound();
		bx = b->x - 3;
		by = b->y - 3;
		if (this->sniper->isInShootRange) {
			this->sniper->CreateBullet(bx, by);
		}
		this->holdTime = 0;
	}
}
void SniperShooting315::OnKeyDown(int keyCode) {
}
void SniperShooting315::OnKeyUp(int keyCode) {

}
string SniperShooting315::GetStateName() {
	return "Shooting315";
}

void SniperHidingShooting0::Enter() {
	this->holdTime = 0;
}
void SniperHidingShooting0::Exit() {
	this->holdTime = 0;


}
void SniperHidingShooting0::Update(float dt) {
	if (this->holdTime<1000) {
		holdTime += dt;
	}
	else
	{
		this->sniper->SetAngle(D3DX_PI);
		float bx, by;
		Bound b = this->sniper->GetBound();
		bx = b->x - 10;
		by = b->y + b->h / 2 + 3;
		if (this->sniper->GetTarget() != NULL) {

			auto targetBound = this->sniper->GetTarget()->GetBound();
			if (this->sniper->isInShootRange && targetBound->y + targetBound->h >= by)
				this->sniper->CreateBullet(bx, by);
		}
		this->holdTime = 0;
	}
}
void SniperHidingShooting0::OnKeyDown(int keyCode) {
}
void SniperHidingShooting0::OnKeyUp(int keyCode) {

}
string SniperHidingShooting0::GetStateName() {
	return "HidingShooting0";
}