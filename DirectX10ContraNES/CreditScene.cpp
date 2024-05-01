#include "CreditScene.h"
#include "SceneManager.h"
#include "SoundManager.h"
CreditScene::CreditScene() {
	this->y = 0;
}

void CreditScene::Update(float dt) {
	this->y += 0.01 * dt;

}

void CreditScene::Render() {
	Font* f1 = new Font(L"CONGRATULATIONS !\nYOU'VE DESTROYED THE VILE RED FALCON \nAND SAVED THE UNIVERSE \nCONSIDER YOURSELF A HERO",0,110 - y,DT_LEFT,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
	Font* f2 = new Font(L"-- CLASS --",90,260 - y,DT_LEFT,D3DXCOLOR(0.4f,0.6f,1.0f,1.0f));
	Font* f3 = new Font(L"SE102.O22",90,280 - y,DT_LEFT,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
	Font* f4 = new Font(L"-- PROGRAMMER --",68,300 - y,DT_LEFT,D3DXCOLOR(0.4f,0.6f,1.0f,1.0f));
	Font* f5 = new Font(L"Ngo Duc Loc - 22520790",50,320 - y,DT_LEFT,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
	Font* f6 = new Font(L"-- GVHD --",90,350 - y,DT_LEFT,D3DXCOLOR(0.4f,0.6f,1.0f,1.0f));
	Font* f7 = new Font(L"Huynh Ho Thi Mong Trinh",50,370 - y,DT_LEFT,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
	f1->Render();
	f2->Render();
	f3->Render();
	f4->Render();
	f5->Render();
	f6->Render();
	f7->Render();

}
void CreditScene::LoadResource() {
}
