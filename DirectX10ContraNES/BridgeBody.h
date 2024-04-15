#pragma once
#ifndef __BridgeBody_H__
#define __BridgeBody_H__

class Bridge;

#include "GameObject.h"
#include "BridgeBodyAnimation.h"
#include "BridgeBodyState.h"
#include <unordered_map>
#include "tinyxml2.h"
class BridgeBody :public GameObject {
private:
	BridgeBodyAnimation* bridgeBodyAnimation;
	BridgeBodyState* currentBridgeBodyState;
	std::unordered_map<std::string, BridgeBodyState*> stateDict;
	Bridge* parent;
public:
	BridgeBody(int id, string name, string type) :GameObject(id, name, type) {
		this->nx = -1;
		this->ny = 1;
		this->SetSpeed(0.1, 0.1);
		this->bridgeBodyAnimation = new BridgeBodyAnimation(this);
		this->currentBridgeBodyState = new BridgeBodyState(this);
		stateDict["BridgeBodyDefault"] = new BridgeBodyDefault(this);
		stateDict["Dead"] = new BridgeBodyDead(this);
		this->SetState("BridgeBodyDefault", "BridgeBodyDefault");
	}
	void SetParent(Bridge* b);
	void Update(float dt, vector<GameObject*>* objects = NULL);
	void Render();
	void LoadAssets();
	void SetState(std::string stateName, std::string animationName);
	void OnNoCollision(float dt) override;
	void OnCollisionWith(CollisionEvent* e, float dt) override;
	void OnCollisionWithPlayer(CollisionEvent* e, float dt);
};

#endif // !__BridgeBody_H__
