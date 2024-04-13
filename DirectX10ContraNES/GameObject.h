#pragma once
#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <string>
#include <vector>
#include "RectF.h"
#include "Game.h"
#include "TextureManager.h"
#include "Collision.h"
class BTree;
#include "BTree.h"
using namespace std;

class GameObject {
protected:
	int id;
	string name;
	string type;
	float angle;
	int nx,ny;
	float vx, vy;
	Bound objectBound;
	BTree* btree;
	vector<GameObject*> objects;
	LPTEXTURE boundTex;
	int isCollidable;
public:
	bool isDead;
	bool isDeleted;
	GameObject(int id, string name, string type, float x = 0, float y = 0, float w = 0, float h = 0) {
		this->id = id;
		this->name = name;
		this->type = type;
		this->nx = 0;
		this->ny = 0;
		this->vx = 0.0f;
		this->vy = 0.0f;
		this->angle = 0;
		this->isCollidable = 1;
		this->isDead = false;
		this->isDeleted = false;
		this->boundTex = TextureManager::GetInstance()->Get(-100);
		this->objectBound = new RectF(x, y, w, h);
	}
	float GetAngle() { return this->angle; }
	void SetAngle(float angle) { this->angle = angle; }
	string GetName() { return this->name; }
	string GetType() {
		return this->type;
	}
	void GetPosition(float& x, float& y) {
		x = this->objectBound->x;
		y = this->objectBound->y;
	}
	void SetPosition(float x, float y) {
		this->objectBound->x = x;
		this->objectBound->y = y;
	}
	void GetSpeed(float& vx, float& vy) {
		vx = this->vx*nx;
		vy = this->vy*ny;
	}
	void SetSpeed(float vx, float vy) {
		this->vx = vx;
		this->vy = vy;
	}
	
	void GetBoundingBox(float& l, float& t, float& r, float& b) {
		l = this->objectBound->x;
		r = this->objectBound->x + this->objectBound->w;
		b = this->objectBound->y;
		t = this->objectBound->y + this->objectBound->h;
	}
	Bound GetBound() { return this->objectBound; }
	void RenderBoundingBox() {
		CGame::GetInstance()->DrawBound(
			this->objectBound->x + this->objectBound->w / 2,
			this->objectBound->y + this->objectBound->h / 2,
			this->objectBound->w,
			this->objectBound->h,
			boundTex
		);
	}
	virtual void RetrieveBTree(BTree* btree) { this->btree = btree; }
	virtual void Update(float dt, vector<GameObject*>* coObjects = NULL) {};
	virtual void Render() = 0;
	virtual int IsCollidable() { return isCollidable; }

	virtual void OnNoCollision(float dt){}
	virtual void OnCollisionWith(CollisionEvent* e ,float dt){}
	static bool IsDeleted(const CollisionEvent*& o) { return o->isDeleted; }
	virtual void LoadAssets(){}
};

#endif // !__GAMEOBJECT_H__
