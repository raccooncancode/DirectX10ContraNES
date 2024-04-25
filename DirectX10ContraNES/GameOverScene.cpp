#include "GameOverScene.h"
#include "SceneManager.h"
GameOverScene::GameOverScene() {
	this->LoadResource();
	this->w = this->preStageTexture->getWidth();
	this->h = this->preStageTexture->getHeight();
	this->time = 0;
	this->flashingTime = 0;
	this->isFlashed = false;
	this->preStageBackground = new CSprite(0, 0, 270, 240, this->preStageTexture);
}

void GameOverScene::Update(float dt) {
	if (this->preStageTexture != NULL && this->preStageBackground != NULL) {
		
		if (this->time <= 10000) {
			this->time += dt;
		}
		else {
			this->time = 0;
			//switch to credit scene
		}
		

		if (this->flashingTime <= 500) {
			this->flashingTime += dt;
		}
		else {
			this->flashingTime = 0;
			this->isFlashed = !this->isFlashed;
		}
	}
}

void GameOverScene::SetStatus(float score, float life) {
	this->score = score;
	this->life = life;
}

void GameOverScene::Render() {
	if (this->preStageTexture != NULL && this->preStageBackground != NULL) {

		this->preStageBackground->Draw(w / 2, h / 2);
		if (CGame::GetInstance()->IsKeyDown(DIK_P)) {
			SceneManager::GetInstance()->PlayAgain();
			SceneManager::GetInstance()->SwitchScene("ready1");
		}
		wchar_t scores[256];
		wchar_t lifes[256];
		wsprintfW(scores, L"%d", score);
		wsprintfW(lifes, L"%d", life);
		Font* f2 = new Font(lifes, 40, 13, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		Font* f1 = new Font(scores, 110, 35, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		Font* f3 = new Font(L"GAME OVER", 100, 100, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		Font* f4 = new Font(L"PRESS P TO PLAY AGAIN", 90, 120, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		Font* f5 = new Font(L"PRESS ENTER TO EXIT", 90, 140, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		if (isFlashed) {
			f1->Render();
			f2->Render();
		}
		f3->Render();
		f4->Render();
		f5->Render();
	}
}
void GameOverScene::LoadResource() {
	this->preStageTexture = CGame::GetInstance()->LoadTexture(L"textures\\PreStage.jpg");
}
