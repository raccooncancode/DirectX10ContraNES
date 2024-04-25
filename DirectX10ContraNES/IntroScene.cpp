#include "IntroScene.h"
#include "SceneManager.h"
IntroScene::IntroScene() {
	this->LoadResource();
	this->x = this->introTexture->getWidth();
	this->introBackGround = new CSprite(0, 0, 270, 240, this->introTexture);
}

void IntroScene::Update(float dt) {
	if (this->introTexture != NULL && this->introBackGround != NULL) {
		this->x -= 0.05 * dt;
		if (this->x < this->introTexture->getWidth() / 2) {
			this->x = this->introTexture->getWidth() / 2;
			this->isDoneAnimation = true;
		}
	}
}

void IntroScene::Render() {
	if (this->introTexture != NULL && this->introBackGround != NULL) {
		auto xDrawing = floor(x);
		this->introBackGround->Draw(xDrawing, 0 + (float)240 / 2);
		if (this->isDoneAnimation) {
			Font* f = new Font(L"Press ENTER To Play",30,110,DT_LEFT,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
			auto x = f;
			f->Render();
			if(CGame::GetInstance()->IsKeyDown(DIK_RETURN)) {
				SceneManager::GetInstance()->SwitchScene("ready1");
			}
		}
	}
}
void IntroScene::LoadResource() {
	this->introTexture = CGame::GetInstance()->LoadTexture(L"textures\\intro.jpg");
}
