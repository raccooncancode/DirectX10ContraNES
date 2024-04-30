#include "SceneManager.h"
#include "Camera.h"
#include "SoundManager.h"
SceneManager::SceneManager() {
	isOpenIntro = false;
	isDoneIntro = false;
	scores = 0;
	holdTime = 0;
	bill = new Bill(0, "Bill", "Player");
	bill->LoadAssets();
	Camera::GetInstance()->SetFollowTarget(bill);
	this->currentSceneName = "intro";

	this->scenes["intro"] = new IntroScene();
	this->scenes["ready1"] = new PreStage1Scene();
	this->scenes["ready3"] = new PreStage3Scene();
	this->scenes["stage1"] = new Map(1);
	this->scenes["stage3"] = new Map(3,false);
	this->scenes["gameover"] = new GameOverScene();
	this->scenes["ending"] = new EndingScene();
	this->scenes["credit"] = new CreditScene();
	
	this->currentScene = this->scenes["intro"];
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
				this->bill->GetBound()->UpdateBoundLocation(3000, 200);
				SoundManager::GetInstance()->Play("stage1", true, 1);
			}
			else {
				this->bill->GetBound()->UpdateBoundLocation(70, 70);
				SoundManager::GetInstance()->Play("stage3", true, 1);
			}
		}
		if (sceneName == "ready1") {
			SoundManager::GetInstance()->Stop();
			PreStage1Scene* ready1 = (PreStage1Scene*)this->scenes["ready1"];
			ready1->SetStatus(this->scores, bill->respawnTimes);
		}
		if (sceneName == "ready3") {
			SoundManager::GetInstance()->Stop();
			PreStage3Scene* ready3 = (PreStage3Scene*)this->scenes["ready3"];
			ready3->SetStatus(this->scores, bill->respawnTimes);
		}
		if (sceneName == "gameover") {
			SoundManager::GetInstance()->Stop();
			GameOverScene* gameover = (GameOverScene*)this->scenes["gameover"];
			gameover->SetStatus(this->scores, 0);
			SoundManager::GetInstance()->Play("gameover",true,1);

		}
		if (sceneName == "ending") {
			SoundManager::GetInstance()->Stop();
			SoundManager::GetInstance()->Play("destroy_boss", true, 1);
		}
		if (sceneName == "ending") {
			SoundManager::GetInstance()->Stop();
			SoundManager::GetInstance()->Play("credit", true, 1);

		}
		this->currentSceneName = sceneName;
		this->currentScene = scenes[sceneName];
		if (this->currentSceneName != "ready1" ||
			this->currentSceneName != "ready3" ||
			this->currentSceneName != "gameover" ||
			this->currentSceneName != "ending" ||
			this->currentSceneName != "credit"
			) {
		this->currentScene->AddMovingObject(this->bill);

		}
	}
}

void SceneManager::Render() {
	this->currentScene->Render();
}
void SceneManager::Update(float dt) {
	if (!isOpenIntro && isDoneIntro) {
		SoundManager::GetInstance()->Play("intro", false, 1);
		this->isOpenIntro = true;
	}
	currentScene->Update(dt);
	if (this->bill->respawnTimes <= 0 && this->bill->isDeleted) {
		SwitchScene("gameover");
	}
	if (this->currentSceneName == "stage1") {
		if (this->bill->GetBound()->x >= 3300) {
			bill->boss = NULL;
			SwitchScene("ready3");
		}
	}
	if (this->currentSceneName == "stage3") {
		if (this->bill->boss != NULL) {
			if (this->bill->boss->GetName() == "BodyBoss3") {
				if (this->bill->boss->isDeleted) {
					if (this->holdTime <= 5000) {
						this->holdTime += dt;
					}
					else {
						SceneManager::GetInstance()->SwitchScene("ending");
					}
				}
			}
		}
	}
}