#include "AnimationAddOnManager.h"

AnimationAddOnManager* AnimationAddOnManager::__instance = nullptr;

AnimationAddOnManager* AnimationAddOnManager::GetInstance() {
	if (__instance == nullptr) {
		__instance = new AnimationAddOnManager();
	}
	return __instance;
}

void AnimationAddOnManager::AddAnimation(std::string aniname ,LPCSTR fileName, int texId) {
	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError eResult = xmlDoc.LoadFile(fileName);
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
	LPTEXTURE tex = TextureManager::GetInstance()->Get(texId);

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
		this->animations[aniname] = ani;
	}
	//ani = new CAnimation(0, 0, false);//temp
	//delete ani;
}

LPANIMATION AnimationAddOnManager::GetAnimation(std::string name) {
	return this->animations[name];
}