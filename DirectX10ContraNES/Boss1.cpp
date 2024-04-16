#include "Boss1.h"

void Boss1::AddGun(GunBoss1* gun) {
	this->guns.push_back(gun);
}

bool Boss1::IsAllGunsRuined() {
	//check if all guns is ruined , so the body can be collided
	bool isAllRuined = true;
	for (GunBoss1* gun : guns) {
		if (!gun->isDeleted)
			isAllRuined = false;
	}
	//if (isAllRuined) {
	//	DebugOut(L"\nIs all ruined");
	//}
	//else {

	//	DebugOut(L"\nNO all ruined");
	//}
	return isAllRuined;
}

bool Boss1::IsSiblingShooting(GunBoss1* sib1) {
	bool res = false;
	for (GunBoss1* gun : guns) {
		if (!gun->isDeleted && gun != sib1) {
			if(gun->isInShootRange)
				res = true;
		}
	}
	return res;
}