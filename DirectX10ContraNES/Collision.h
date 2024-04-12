#pragma once
#ifndef __COLLISION_H__
#define __COLLISION_H__

class GameObject;

#include <vector>
using namespace std;
class CollisionEvent {
public:
	GameObject* src;
	GameObject* dest;
	float t;
	float ny, nx;
	float dx, dy;
	bool isDeleted;
	CollisionEvent(float t, float nx, float ny, float dx=0, float dy = 0, GameObject* src=NULL, GameObject* dest = NULL) {
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		this->src = src;
		this->dest = dest;
		this->isDeleted = false;
	}
	bool IsCollided() {
		return t >= 0.0f && t <= 1.0f;
	}
};

class Collision {
private:
	static Collision* __instance;
	int count = 0;
public:
	static Collision* GetInstance(); 
	void SweptAABB(
		float dx,			
		float dy,
		float& t,
		float& nx,
		float& ny,
		GameObject* src,
		GameObject* dest);
	CollisionEvent* SweptAABB(GameObject* src, GameObject* dest,float dt);
	void Filter(
		GameObject* objSrc,
		vector<CollisionEvent*>& coEvents,
		CollisionEvent*& colX,
		CollisionEvent*& colY,
		int filterBlock,
		int filterX,
		int filterY);

	void Proccess(GameObject* src, vector<GameObject*>* objects, float dt);
};

#endif // !__COLLISION_H__
