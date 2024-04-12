#include "SceneManager.h"

SceneManager::SceneManager() {
	this->scenes["intro"] = new IntroScene();
	SwitchScene("intro");
}

SceneManager* SceneManager::__instance = nullptr;

SceneManager* SceneManager::GetInstance() {
	if (__instance == nullptr)
		__instance = new SceneManager();
	return __instance;
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