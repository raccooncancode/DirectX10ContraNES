#include "SceneManager.h"
#include "Camera.h"
SceneManager::SceneManager() {
	scores = 0;
	bill = new Bill(0, "Bill", "Player");
	bill->LoadAssets();
	//bill->GetBound()->UpdateBoundLocation(3000, 200);
	Camera::GetInstance()->SetFollowTarget(bill);
	this->currentSceneName = "intro";

	this->scenes["intro"] = new IntroScene();
	this->scenes["ready1"] = new PreStage1Scene();
	this->scenes["ready3"] = new PreStage3Scene();
	this->scenes["stage1"] = new Map(1);
	this->scenes["stage3"] = new Map(3,false);
	this->scenes["gameover"] = new GameOverScene();
	

	//auto map1 = new Map(1);
	//map1->AddMovingObject(bill);
	//this->scenes["playscene"] = map1;
	//auto map3 = new Map(3,false);
	//map3->AddMovingObject(bill);
	//this->scenes["playscene"] = map3;
	
	this->currentScene = this->scenes["intro"];
	//SwitchScene("ready3");
}



SceneManager* SceneManager::__instance = nullptr;

SceneManager* SceneManager::GetInstance() {
	if (__instance == nullptr)
		__instance = new SceneManager();
	return __instance;
}

void SceneManager::PlayAgain() {
	bill = new Bill(0, "Bill", "Player");
	bill->LoadAssets();
	scores = 0;
	this->scenes["stage1"] = new Map(1);
	this->scenes["stage3"] = new Map(3);
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
	if (this->currentSceneName != sceneName) {
		if (this->currentSceneName.find("stage") != std::string::npos) {
			this->currentScene->Clear();
			bill->boss = NULL;
		}
		Camera::GetInstance()->ResetCamera();
		if (sceneName.find("stage") != std::string::npos) {
			if (sceneName == "stage1") {
				Camera::GetInstance()->GetCameraBound()->UpdateBoundLocation(0, 15);
				this->bill->GetBound()->UpdateBoundLocation(70, 200);
			}
			else {
				this->bill->GetBound()->UpdateBoundLocation(70, 70);
			}
		}
		if (sceneName == "ready1") {
			PreStage1Scene* ready1 = (PreStage1Scene*)this->scenes["ready1"];
			ready1->SetStatus(this->scores, bill->respawnTimes);
		}
		if (sceneName == "ready3") {
			PreStage3Scene* ready3 = (PreStage3Scene*)this->scenes["ready3"];
			ready3->SetStatus(this->scores, bill->respawnTimes);
		}
		if (sceneName == "gameover") {
			GameOverScene* gameover = (GameOverScene*)this->scenes["gameover"];
			gameover->SetStatus(this->scores, 0);
		}
		this->currentSceneName = sceneName;
		this->currentScene = scenes[sceneName];
		if (this->currentSceneName != "ready1" ||
			this->currentSceneName != "ready3" ||
			this->currentSceneName != "gameover"
			) {
		this->currentScene->AddMovingObject(this->bill);

		}
	}
}

void SceneManager::Render() {
	this->currentScene->Render();
}
void SceneManager::Update(float dt) {
	this->currentScene->Update(dt);
	if (this->bill->respawnTimes <= 0 && this->bill->isDeleted) {
		SwitchScene("gameover");
	}
	if (this->currentSceneName == "stage1") {
		if (this->bill->GetBound()->x >= 3300) {
			SwitchScene("ready3");
		}
	}
	if (this->currentSceneName == "stage3") {
		if (this->bill->boss != NULL) {
			if (this->bill->boss->GetName() == "BodyBoss3") {
				if (this->bill->boss->isDeleted) {
					SceneManager::GetInstance()->SwitchScene("gameover");
				}
			}
		}
	}
}