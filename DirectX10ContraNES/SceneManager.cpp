#include "SceneManager.h"

SceneManager::SceneManager() {
	bill = new Bill(0, "Bill", "Player");
	bill->LoadAssets();
	bill->GetBound()->UpdateBoundLocation(2900, 240);
	Camera::GetInstance()->SetFollowTarget(bill);
	this->scenes["intro"] = new IntroScene();

	auto map1 = new Map(1);
	map1->AddMovingObject(bill);
	this->scenes["playscene"] = map1;
	//auto map3 = new Map(3,false);
	//map3->AddMovingObject(bill);
	//this->scenes["playscene"] = map3;

	SwitchScene("playscene");
}



SceneManager* SceneManager::__instance = nullptr;

SceneManager* SceneManager::GetInstance() {
	if (__instance == nullptr)
		__instance = new SceneManager();
	return __instance;
}

void SceneManager::ChangeMap(int stage) {

	if (stage == 3) {
		auto nextMap = new Map(3, false);

		nextMap->AddMovingObject(bill);
		this->scenes["playscene"]->Clear();
		this->scenes["playscene"] = nextMap;
	}
}

Scene* SceneManager::GetCurrentScene() {
	return this->currentScene;
}

void SceneManager::SwitchScene(std::string sceneName) {
	this->currentScene = scenes[sceneName];
}

void SceneManager::Render() {
	this->currentScene->Render();
}
void SceneManager::Update(float dt) {
	this->currentScene->Update(dt);
}