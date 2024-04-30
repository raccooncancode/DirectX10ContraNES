#pragma once
#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__
#include "Scene.h"
#include "IntroScene.h"
#include "PreStage1Scene.h"
#include "PreStage3Scene.h"
#include "GameOverScene.h"
#include "EndingScene.h"
#include "CreditScene.h"
#include "Map.h"
#include "Bill.h"
#include <unordered_map>
#include <string>

class SceneManager {
private:
	static SceneManager* __instance;
	std::unordered_map<std::string, Scene*> scenes;
	Scene* currentScene;
	SceneManager();
	bool isOpenIntro;
	float holdTime;
public:
	Bill* bill;
	int scores;
	bool isDoneIntro;
	std::string currentSceneName;
	static SceneManager* GetInstance();
	Scene* GetCurrentScene();
	void SwitchScene(std::string sceneName);
	void ChangeMap(int map);
	void Update(float dt);
	void Render();
	void PlayAgain();
};

#endif // !__SCENEMANAGER_H__
