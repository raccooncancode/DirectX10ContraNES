#pragma once
#ifndef __BULLET_H__
#define __BULLET_H__

#include "GameObject.h"
#include "Enemy.h"
#include "Sprite.h"
class Bullet: public GameObject {
protected:
	LPTEXTURE BulletTex;
	LPSPRITE BulletSprite;
public:
	Bullet(int id , string name , string type, float x, float y, float speed, float angle):GameObject(id,name,type,x,y) {
		this->BulletTex = TextureManager::GetInstance()->Get(id);
		float texW = BulletTex->getWidth();
		float texH = BulletTex->getHeight();
		this->BulletSprite = new CSprite(0, 0, texW, texH, BulletTex);
		this->objectBound->UpdateBoundSize(texW, texH);
		this->vx = speed;
		this->vy = speed;
		this->angle = angle;
	}
	virtual void OnNoCollision(float dt) {
		this->objectBound->x += vx * dt * cos(this->angle);
		this->objectBound->y += vy * dt * sin(this->angle);
	}
	virtual void OnCollisionWith(CollisionEvent* e, float dt) {
		
	}
	virtual void Update(float dt, vector<GameObject*>* objects = NULL) {
		if (!this->isDeleted) {
			this->objects.clear();
			this->btree->Retrieve(this->btree->root, this->objects, this->objectBound);
			Collision::GetInstance()->Proccess(this, &this->objects, dt);
		}
	}
	virtual void Render() {
		if(!this->isDeleted)
			this->BulletSprite->Draw(this->objectBound->x + this->objectBound->w / 2, this->objectBound->y + this->objectBound->h / 2);
	}
	void ClearUp() {
		delete BulletSprite;
		delete objectBound;
	}
};

#endif // !__BULLET_H__	;