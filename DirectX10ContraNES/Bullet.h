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
		this->nx = cos(this->angle);
		this->ny = sin(this->angle);
	}
	virtual void OnNoCollision(float dt) {
		this->objectBound->x += vx * dt * cos(this->angle);
		this->objectBound->y += vy * dt * sin(this->angle);
	}
	virtual void OnCollisionWith(CollisionEvent* e, float dt) {
		if (dynamic_cast<Bullet*>(e->dest)) {
			return;
		}
		if (dynamic_cast<Enemy*>(e->dest)) {
			OnCollisionWithEnemy(e, dt);
		}
	}
	virtual void OnCollisionWithEnemy(CollisionEvent* e, float dt) {
		if (e->src->GetType() == "PlayerBullet") {
			auto enemy = (Enemy*)e->dest;
			DebugOut(L"\nnx: %d, ny: %d ", e->nx, e->ny);
			string s = enemy->GetName();
			wstring temp = wstring(s.begin(), s.end());
			LPCWSTR wideString = temp.c_str();
			DebugOut(L"\n");
			DebugOut(wideString);
			enemy->DecreaseHP(1);
			this->isDeleted = true;
		}
		else if (e->src->GetType() == "EnemyBullet") {
			this->isDeleted = true;
		}
		//this->vx = 0;
		//this->vy = 0;
		//this->isDeleted = true;
	}
	virtual void Update(float dt, vector<GameObject*>* objects = NULL) {
		if (!this->btree->root->bound->IsOverlap(this->objectBound) && this->isDeleted== false)
		{
			this->isDeleted = true;
			
		}
		if (!this->isDeleted)
		{

			this->objects.clear();
			this->btree->Retrieve(this->btree->root, this->objects, this->objectBound);
			this->collision->Proccess(this, &this->objects, dt);
			//DebugOut(L"\n bullet x: %f, bullet y: %f", this->objectBound->x, this->objectBound->y);
		}
		//Collision::GetInstance()->Proccess(this, &this->objects, dt);
	}
	virtual void Render() {
		this->BulletSprite->Draw(this->objectBound->x + this->objectBound->w / 2, this->objectBound->y + this->objectBound->h / 2);
		//RenderBoundingBox();
	}
	
};

#endif // !__BULLET_H__	;
