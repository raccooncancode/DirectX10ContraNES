#include "GameObject.h"
#include "Collision.h"
Collision* Collision::__instance = nullptr;
Collision* Collision::GetInstance() {
	if (__instance == nullptr)
		__instance = new Collision();
	return __instance;
}

void Collision::SweptAABB(
	float dx, float dy,
	float& t, float& nx, float& ny,
	GameObject* src,
	GameObject* dest)
{

	Bound other = dest->GetBound();
	Bound object = src->GetBound();
	float dx_entry, dx_exit, tx_entry, tx_exit;
	float dy_entry, dy_exit, ty_entry, ty_exit;

	float t_entry;
	float t_exit;

	t = -1.0f;			// no collision
	nx = ny = 0;
	//
	// Broad-phase test 
	//

	float x = dx > 0 ? object->x : object->x + dx;
	float y = dy > 0 ? object->y : object->y + dy;
	float w = object->w + abs(dx);
	float h = object->h + abs(dy);

	Bound bb = new RectF(x, y, w, h);
	if (!bb->IsOverlap(dest->GetBound())) {
		return;
	}

	//if (br < sl || bl > sr || bb < st || bt > sb)
	//	return;


	if (dx == 0 && dy == 0) 
		return;		// moving object is not moving > obvious no collision

	if (dx > 0)
	{
		dx_entry = other->x - (object->x + object->w);
		dx_exit = (other->x + other->w) - object->x;
	}
	else if (dx < 0)
	{
		dx_entry = (other->x + other->w) - object->x;
		dx_exit = other->x - (object->x + object->w);
	}


	if (dy > 0)
	{
		dy_entry = other->y - (object->y + object->h);
		dy_exit = (other->y + other->h) - object->y;
	}
	else if (dy < 0)
	{
		dy_entry = (other->y + other->h) - object->y;
		dy_exit = other->y - (object->y + object->h);
	}

	if (dx == 0.0f)
	{
		tx_entry = -9999999.0f;
		tx_exit = 99999999.0f;
	}
	else
	{
		tx_entry = dx_entry / dx;
		tx_exit = dx_exit / dx;
	}

	if (dy == 0.0f)
	{
		ty_entry = -99999999999.0f;
		ty_exit = 99999999999.0f;
	}
	else
	{
		ty_entry = dy_entry / dy;
		ty_exit = dy_exit / dy;
	}

	if ((tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f) {
		return;
	}

	t_entry = max(tx_entry, ty_entry);
	t_exit = min(tx_exit, ty_exit);

	if (t_entry > t_exit) 
		return;

	t = t_entry;

	if (tx_entry > ty_entry)
	{
		ny = 0.0f;
		dx > 0 ? nx = -1.0f : nx = 1.0f;
	}
	else
	{
		nx = 0.0f;
		dy > 0 ? ny = -1.0f : ny = 1.0f;
	}

}

CollisionEvent* Collision::SweptAABB(GameObject* src, GameObject* dest,float dt) {
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	float mvx, mvy;
	src->GetSpeed(mvx, mvy);
	float mdx = mvx * dt;
	float mdy = mvy * dt;

	float svx, svy;
	dest->GetSpeed(svx, svy);
	float sdx = svx * dt;
	float sdy = svy * dt;

	float dx = mdx - sdx;
	float dy = mdy - sdy;


	Bound srcBound = src->GetBound();
	ml = srcBound->x;
	mr = srcBound->x + srcBound->w;
	mt = srcBound->y + srcBound->h;
	mb = srcBound->y;
	Bound destBound = dest->GetBound();
	sl = destBound->x;
	sr = destBound->x + destBound->w;
	st = destBound->y + destBound->h;
	sb = destBound->y;
	SweptAABB(
		dx, dy,
		t, nx, ny,
		src,
		dest
	);

	CollisionEvent* e = new CollisionEvent(t, nx, ny, dx, dy, src, dest);
	return e;
}


void Collision::Filter(
	GameObject* objSrc,
	vector<CollisionEvent*>& coEvents,
	CollisionEvent*& colX,
	CollisionEvent*& colY,
	int filterBlock=1,
	int filterX=1,
	int filterY=1) {
	float min_tx, min_ty;

	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		CollisionEvent* c = coEvents[i];
		if (c->isDeleted) continue;
		//if (c->obj->IsDeleted()) continue;

		// ignore collision event with object having IsBlocking = 0 (like coin, mushroom, etc)
		/*if (filterBlock == 1 && !c->obj->IsBlocking())
		{
			continue;
		}*/

		if (c->t < min_tx && c->nx != 0 && filterX == 1) {
			min_tx = c->t; min_ix = i;
		}

		if (c->t < min_ty && c->ny != 0 && filterY == 1) {
			min_ty = c->t; min_iy = i;
		}
	}

	if (min_ix >= 0) colX = coEvents[min_ix];
	if (min_iy >= 0) colY = coEvents[min_iy];
}


void Collision::Proccess(GameObject* src, vector<GameObject*>* objects, float dt) {
	vector<CollisionEvent*> coEvents;
	CollisionEvent* colX=NULL;
	CollisionEvent* colY=NULL;

	for (int i = 0; i < objects->size(); i++) {
		if (!objects->at(i)->isDeleted) {
			CollisionEvent* e = SweptAABB(src, objects->at(i), dt);
			if (e->IsCollided()) {
				coEvents.push_back(e);
			}
			else
				delete e;
		}
	}
	if (coEvents.size() == 0) {
		src->OnNoCollision(dt);
	}
	else{
		//count++;
		//DebugOut(L"\nHave Collision %d",count);
		Filter(src, coEvents, colX, colY, 1, 1, 1);
		float x, y, vx, vy, dx, dy;
		src->GetPosition(x, y);
		src->GetSpeed(vx, vy);
		dx = vx * dt;
		dy = vy * dt;
			
		if (colX != NULL && colY != NULL)
		{

			if (colY->t < colX->t)	// was collision on Y first ?
			{
				y += colY->t * dy + colY->ny * 0.4;
				src->SetPosition(x, y);
				src->OnCollisionWith(colY,dt);

				//
				// see if after correction on Y, is there still a collision on X ? 
				//
				CollisionEvent* colX_other = NULL;

				//
				// check again if there is true collision on X 
				//
				colX->isDeleted = true;		// remove current collision event on X

				// replace with a new collision event using corrected location 
				coEvents.push_back(SweptAABB(src, colX->dest,dt));

				// re-filter on X only
				Filter(src, coEvents, colX_other, colY, /*filterBlock = */ 1, 1, /*filterY=*/0);

				if (colX_other != NULL)
				{
					x += colX_other->t * dx + colX_other->nx * 0.4;
					src->OnCollisionWith(colX_other,dt);
				}
				else
				{
					x += dx;
				}
			}
			else // collision on X first
			{
				x += colX->t * dx + colX->nx * 0.4f;
				src->SetPosition(x, y);

				src->OnCollisionWith(colX,dt);

				//
				// see if after correction on X, is there still a collision on Y ? 
				//
				CollisionEvent* colY_other = NULL;

				//
				// check again if there is true collision on Y
				//
				colY->isDeleted = true;		// remove current collision event on Y

				// replace with a new collision event using corrected location 
				coEvents.push_back(SweptAABB(src,  colY->dest,dt));

				// re-filter on Y only
				Filter(src, coEvents, colX, colY_other, /*filterBlock = */ 1, /*filterX=*/0, /*filterY=*/1);

				if (colY_other != NULL)
				{
					y += colY_other->t * dy + colY_other->ny * 0.4f;
					src->OnCollisionWith(colY_other,dt);
				}
				else
				{
					y += dy;
				}
			}
		}
		else

			if (colX != NULL)
			{
				x += colX->t * dx + colX->nx * 0.4f;
				y += dy;
				src->OnCollisionWith(colX,dt);
			}
			else
				if (colY != NULL)
				{
					x += dx;
					if (colY->ny < 0) {
						if (colY->dest->GetType() == "throughable" && colY->src->GetType() == "Player")
						{
							y += vy * dt;
						}
						else {
							y += colY->t * dy + colY->ny * 0.04f;

						}
					}
					else  if (colY->ny > 0) {
						y += colY->t * dy + colY->ny * 0.04f;
					}
					src->OnCollisionWith(colY,dt);
				}
				else // both colX & colY are NULL 
				{
					x += dx;
					y += dy;
				}

		src->SetPosition(x, y);
	}
}