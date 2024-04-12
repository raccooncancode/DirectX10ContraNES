#include "IntroScene.h"

IntroScene::IntroScene() {
	this->LoadResource();
	this->introBackGround = new CSprite(0, 0, 270, 240, this->introTexture);
}

void IntroScene::Update(float dt) {

}

void IntroScene::Render() {
	this->introBackGround->Draw(0+(float)270/2, 0+(float)240/2);
}
void IntroScene::LoadResource() {
	this->introTexture = CGame::GetInstance()->LoadTexture(L"textures\\intro.jpg");
}
