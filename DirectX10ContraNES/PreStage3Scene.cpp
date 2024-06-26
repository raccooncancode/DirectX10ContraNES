#include "PreStage3Scene.h"
#include "SceneManager.h"
PreStage3Scene::PreStage3Scene() {
	this->LoadResource();
	this->w = this->preStageTexture->getWidth();
	this->h = this->preStageTexture->getHeight();
	this->time = 0;
	this->flashingTime = 0;
	this->isFlashed = false;
	this->preStageBackground = new CSprite(0, 0, 270, 240, this->preStageTexture);
}

void PreStage3Scene::Update(float dt) {
	if (this->preStageTexture != NULL && this->preStageBackground != NULL) {
		if (this->time <= 4000) {
			this->time += dt;
		}
		else {
			this->time = 0;
			SceneManager::GetInstance()->SwitchScene("stage3");
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

void PreStage3Scene::SetStatus(int score,int highestScore, int life) {
	this->score = score;
	this->life = life;
	this->highestScore = highestScore;
}

void PreStage3Scene::Render() {
	if (this->preStageTexture != NULL && this->preStageBackground != NULL) {

		this->preStageBackground->Draw(w / 2, h / 2);
		wchar_t scores[256];
		wchar_t highestScore[256];
		wchar_t lifes[256];
		wsprintfW(scores, L"%d", score);
		wsprintfW(lifes, L"%d", life);
		wsprintfW(highestScore, L"%d", this->highestScore);
		Font* f2 = new Font(lifes, 40, 13, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		Font* f1 = new Font(highestScore, 110, 35, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		Font* f5 = new Font(scores, 40, 0, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		Font* f3 = new Font(L"STAGE 3", 100, 100, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		Font* f4 = new Font(L"WATER FALL", 100, 120, DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		if (isFlashed) {
			f1->Render();
			f5->Render();
		}
		f2->Render();
		f3->Render();
		f4->Render();
	}
}
void PreStage3Scene::LoadResource() {
	this->preStageTexture = CGame::GetInstance()->LoadTexture(L"textures\\PreStage.jpg");
}
