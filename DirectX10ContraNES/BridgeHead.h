#pragma once
#ifndef __BRIDGEHEAD_H__
#define __BRIDGEHEAD_H__

class Bridge;

#include "GameObject.h"
#include "BridgeHeadAnimation.h"
#include "BridgeHeadState.h"
#include <unordered_map>
#include "tinyxml2.h"
class BridgeHead :public GameObject {
private:
	BridgeHeadAnimation* bridgeHeadAnimation;
	BridgeHeadState* currentBridgeHeadState;
	std::unordered_map<std::string, BridgeHeadState*> stateDict;
	GameObject* bill;
public:
	BridgeHead(int id, string name, string type) :GameObject(id, name, type) {
		this->nx = -1;
		this->ny = 1;
		this->SetSpeed(0.1, 0.1);
		this->bridgeHeadAnimation = new BridgeHeadAnimation(this);
		this->currentBridgeHeadState = new BridgeHeadState(this);
		stateDict["BridgeHeadDefault"] = new BridgeHeadDefault(this);
		stateDict["Dead"] = new BridgeHeadDead(this);
		this->SetState("BridgeHeadDefault", "BridgeHeadDefault");
	}
	void Update(float dt, vector<GameObject*>* objects = NULL);
	void Render();
	void LoadAssets();
	void SetState(std::string stateName, std::string animationName);
	void OnNoCollision(float dt) override;
	void OnCollisionWith(CollisionEvent* e, float dt) override;
	void OnCollisionWithPlayer(CollisionEvent* e, float dt);
};

#endif // !__BRIDGEHEAD_H__
