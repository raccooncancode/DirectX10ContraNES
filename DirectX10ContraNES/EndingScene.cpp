#include "EndingScene.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "tinyxml2.h"
EndingScene::EndingScene() {
	this->LoadResource();
}



void EndingScene::Update(float dt) {
	if (this->endingTexture != NULL &&  this->endingAnimation!= NULL) {
		this->endingAnimation->Update(dt,NULL,false);
	}
}

void EndingScene::Render() {
	if (this->endingTexture != NULL && this->endingAnimation != NULL) {
		auto test = endingAnimation->GetCurrentSprite();
		this->endingAnimation->Render(150,(float)225/2);
		if (this->endingAnimation->IsDone()) {
			SceneManager::GetInstance()->SwitchScene("credit");
		}
	}
}
void EndingScene::LoadResource() {
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError eResult = xmlDoc.LoadFile("Textures\\EndingScene.xml");
	if (eResult != tinyxml2::XML_SUCCESS) {
		return;
	}
	tinyxml2::XMLElement* root = xmlDoc.FirstChildElement("Animations");
	if (root == nullptr) {
		return;
	}
	tinyxml2::XMLElement* animation = nullptr;
	tinyxml2::XMLElement* frame = nullptr;
	LPANIMATION ani;
	std::string name;
	int totalFrame = 0;
	bool isLoop;
	int duration = 0;
	float x, y, w, h;
	LPTEXTURE tex = TextureManager::GetInstance()->Get(-999);
	this->endingTexture = tex;
	for (animation = root->FirstChildElement(); animation != NULL; animation = animation->NextSiblingElement()) {
		animation->QueryIntAttribute("duration", &duration);
		animation->QueryIntAttribute("totalFrame", &totalFrame);
		animation->QueryBoolAttribute("isLoop", &isLoop);
		name = animation->Attribute("name");
		ani = new CAnimation(totalFrame, duration, isLoop);
		for (frame = animation->FirstChildElement(); frame != NULL; frame = frame->NextSiblingElement()) {
			frame->QueryFloatAttribute("x", &x);
			frame->QueryFloatAttribute("y", &y);
			frame->QueryFloatAttribute("w", &w);
			frame->QueryFloatAttribute("h", &h);
			ani->AddFrame(new CSprite(x, y, w, h, tex));
		}
		this->endingAnimation = ani;
	}
}
