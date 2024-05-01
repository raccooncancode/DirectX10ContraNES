#include "Map.h"

Map::Map(int stage , bool isSplitVertical) {
	this->isFinish = false;
	this->isSplitVertical = isSplitVertical;
	this->mapStage = stage;
	this->tile = new Tile();
	ReadMapFile();
}

Map::~Map() {
	this->staticObjects.clear();
	this->movingObjects.clear();
	this->allObjects.clear();
	delete this->tile;
}

void Map::Clear() {
	this->staticObjects.clear();
	this->movingObjects.clear();
	this->allObjects.clear();
	delete this->btree;
	delete this->mapBound;
	delete this->tile;
}

void Map::ReadMapFile() {
	tinyxml2::XMLDocument xmlDoc;
	std::string stageString = to_string(this->mapStage);
	std::string filePath = "map\\stage" + stageString + ".tmx";
	const char* filePathToRead = filePath.c_str();
	tinyxml2::XMLError eResult = xmlDoc.LoadFile(filePathToRead);
	if (eResult != tinyxml2::XML_SUCCESS) {
		DebugOut(L"\nCan't Load Xml File: %s", filePathToRead);
		return;
	}
	this->xmlRoot = xmlDoc.FirstChildElement("map");
	if (xmlRoot == nullptr) {
		DebugOut(L"\nXml File Has No Root: %s", filePathToRead);
		return;
	}
	xmlRoot->QueryIntAttribute("width", &mapColumns);
	xmlRoot->QueryIntAttribute("height", &mapRows);
	xmlRoot->QueryIntAttribute("tilewidth", &tileSize);
	tinyxml2::XMLElement* xmlTileSetImg = xmlRoot->FirstChildElement()->FirstChildElement();
	std::string tileSetName = xmlTileSetImg->Attribute("source");
	std::string tileSetFilePath = "textures\\" + tileSetName;
	wstring textureFilePath = wstring(tileSetFilePath.begin(), tileSetFilePath.end());
	LPCWSTR textureFilePathToLoad = textureFilePath.c_str();
	LPTEXTURE tex = CGame::GetInstance()->LoadTexture(textureFilePathToLoad);

	tile->LoadTileSetTexture(tex);
	tile->LoadTiles(this->tileSize);
	tile->LoadAnimationTiles(xmlTileSetImg);
	this->btree = new BTree(0, 0, 0, mapColumns * tileSize, mapRows * tileSize, isSplitVertical);
	this->mapBound = new RectF(0, 0, mapColumns * tileSize, mapRows * tileSize);
	LoadMap2D(xmlRoot->FirstChildElement("layer")->FirstChildElement("data"));
	LoadObjects(xmlRoot);
}
void Map::LoadMap2D(tinyxml2::XMLElement* e) {
	std::string decodedMapDataString;
	std::vector<int> row(mapColumns); // row full 0 value
	std::vector<std::vector<int>> originMap2D;
	for (int r = 0; r < mapRows; r++) {
		this->map2D.push_back(row); //create 2D array filled by 0 value
		originMap2D.push_back(row);
	}
	int cellValue;
	std::vector<int> tempCellValueList;
	tinyxml2::XMLElement* xmlCell = nullptr;
	for (xmlCell = e->FirstChildElement(); xmlCell != NULL; xmlCell = xmlCell->NextSiblingElement()) {
		xmlCell->QueryIntAttribute("gid", &cellValue);
		tempCellValueList.push_back(cellValue);
	}
	int index = 0;
	for (int r = 0; r < mapRows; r++) {
		for (int c = 0; c < mapColumns; c++) {
			originMap2D[r][c] = tempCellValueList[index] - 1;
			index++;
		}
	}
	int reverseRow, column;
	for (int r = 0; r < map2D.size(); r++) {
		for (int c = 0; c < map2D[r].size(); c++) {
			reverseRow = std::abs((float)r - map2D.size() + 1);
			column = c;
			map2D[r][c] = originMap2D[reverseRow][column];
		}
	}
	this->tile->LoadMap2D(this->map2D);
}
void Map::LoadObjects(tinyxml2::XMLElement* root) {
	tinyxml2::XMLElement* xmlObjectGroup = NULL;
	tinyxml2::XMLElement* xmlObject = NULL;

	int id;
	float x, y, w, h, worldX,worldY;
	std::string groupObjectType;
	std::string objectName;
	std::string objectType;
	Boss1* boss1 = new Boss1();
	Boss3* boss3 = new Boss3();
	for (xmlObjectGroup = root->FirstChildElement("objectgroup"); xmlObjectGroup != NULL; xmlObjectGroup = xmlObjectGroup->NextSiblingElement()) {
		groupObjectType = xmlObjectGroup->Attribute("name");
		if (groupObjectType.compare("CollisionRect") == 0) {
			//platform
			for (xmlObject = xmlObjectGroup->FirstChildElement(); xmlObject != NULL; xmlObject = xmlObject->NextSiblingElement()) {
				xmlObject->QueryIntAttribute("id", &id);
				xmlObject->QueryFloatAttribute("x", &x);
				xmlObject->QueryFloatAttribute("y", &y);
				xmlObject->QueryFloatAttribute("width", &w);
				xmlObject->QueryFloatAttribute("height", &h);
				objectType = xmlObject->Attribute("type");
				worldX = x;
				worldY = ((this->mapRows) * this->tileSize) - (y+h);
				Platform* platform =  new Platform(id,"Platform", objectType);
				platform->GetBound()->UpdateBoundLocation(worldX, worldY);
				platform->GetBound()->UpdateBoundSize(w, h);
 				AddStaticObject(platform);
			}
		}
		else {
			//GameObjects
			for (xmlObject = xmlObjectGroup->FirstChildElement(); xmlObject != NULL; xmlObject = xmlObject->NextSiblingElement()) {
				xmlObject->QueryIntAttribute("id", &id);
				xmlObject->QueryFloatAttribute("x", &x);
				xmlObject->QueryFloatAttribute("y", &y);
				xmlObject->QueryFloatAttribute("width", &w);
				xmlObject->QueryFloatAttribute("height", &h);
				objectName = xmlObject->Attribute("name");
				objectType = xmlObject->Attribute("type");
				worldX = x;
				worldY = ((this->mapRows) * this->tileSize) - (y + h);
				string s =objectName;
				wstring temp = wstring(s.begin(), s.end());
				LPCWSTR wideString = temp.c_str();
				DebugOut(L"\n");
				DebugOut(wideString);
				if (objectType == "enemy") {
					if (objectName == "Soldier") {
						GameObject* s = new Soldier(1, "Soldier", "Enemy", 1);
						s->LoadAssets();
						s->GetBound()->UpdateBoundLocation(worldX, worldY);
						AddMovingObject(s);

					}
					if (objectName == "Sniper") {
						GameObject* s = new Sniper(2, "Sniper", "Enemy", 1);
						s->LoadAssets();
						s->GetBound()->UpdateBoundLocation(worldX, worldY);
						AddMovingObject(s);
					}
					if (objectName == "SniperH") {
						GameObject* s = new Sniper(2, "Sniper", "Enemy", 1,true);
						s->LoadAssets();
						s->GetBound()->UpdateBoundLocation(worldX, worldY);
						AddMovingObject(s);
					}
					if (objectName == "GunRotating") {
						GameObject* s = new RotatingGun(3,"GunRotating","Enemy",4);
						s->LoadAssets();
						s->GetBound()->UpdateBoundLocation(worldX, worldY);
						AddMovingObject(s);
					}
					if (objectName == "Cannon") {
						GameObject* s = new Cannon(4, "Cannon", "Enemy", 4);
						s->LoadAssets();
						s->GetBound()->UpdateBoundLocation(worldX, worldY);
						AddMovingObject(s);
					}
					if (objectName == "Blazer") {
						GameObject* s = new Blazer(15, "Blazer", "Enemy", 4);
						s->LoadAssets();
						s->GetBound()->UpdateBoundLocation(worldX, worldY);
						AddMovingObject(s);
					}
					if (objectName == "Stone") {
						GameObject* s = new Stone(15, "Stone", "Enemy", 1);
						s->LoadAssets();
						s->GetBound()->UpdateBoundLocation(worldX, worldY);
						AddMovingObject(s);
					}
					if (objectName == "Scuba") {
						GameObject* s = new Scuba(16, "Scuba", "Enemy", 1);
						s->LoadAssets();
						s->GetBound()->UpdateBoundLocation(worldX, worldY);
						AddMovingObject(s);
					}
					if (objectName == "GunBoss1") {
						GunBoss1* s = new GunBoss1(13, "GunBoss1", "Enemy", 12);
						s->LoadAssets();
						s->GetBound()->UpdateBoundLocation(worldX, worldY);
						boss1->AddGun(s);
						s->SetParent(boss1);
						AddMovingObject(s);
					}
					if (objectName == "BodyBoss1") {
						BodyBoss1* s = new BodyBoss1(13, "BodyBoss1", "Enemy", 12);
						s->LoadAssets();
						s->GetBound()->UpdateBoundLocation(worldX, worldY);
						s->SetParent(boss1);
						AddMovingObject(s);
					}
					if (objectName == "Boss3Body") {
						BodyBoss3* s = new BodyBoss3(17, "BodyBoss3", "Enemy", 1);
						s->LoadAssets();
						s->GetBound()->UpdateBoundLocation(worldX, worldY);
						s->SetParent(boss3);
						AddMovingObject(s);
					}
					if (objectName == "Boss3Head") {
						HeadBoss3* s = new HeadBoss3(17, "HeadBoss3", "Enemy", 30);
						s->LoadAssets();
						s->GetBound()->UpdateBoundLocation(worldX, worldY);
						boss3->AddHead(s);
						s->SetParent(boss3);
						AddMovingObject(s);
					}
					if (objectName == "Boss3ArmLeft") {
						ArmJoint* s = new ArmJoint(15, "ArmLeft", "Enemy", 12,true);
						s->LoadAssets();
						s->GetBound()->UpdateBoundLocation(worldX, worldY);
						ArmJoint* armLeftJoint1 = new ArmJoint(15, "ArmJoint", "Enemy", 14,true);
						ArmJoint* armLeftJoint2 = new ArmJoint(15, "ArmJoint", "Enemy", 14,true);
						ArmJoint* armLeftJoint3 = new ArmJoint(15, "ArmJoint", "Enemy", 14,true);
						ArmJoint* armLeftJoint4 = new ArmJoint(15, "ArmJoint", "Enemy", 14,true,true);

						float x, y;
						x = worldX;
						y = worldY;

						armLeftJoint1->LoadAssets();
						armLeftJoint1->GetBound()->UpdateBoundLocation(x, y);
						armLeftJoint2->LoadAssets();
						armLeftJoint2->GetBound()->UpdateBoundLocation(x, y);
						armLeftJoint3->LoadAssets();
						armLeftJoint3->GetBound()->UpdateBoundLocation(x, y);
						armLeftJoint4->LoadAssets();
						armLeftJoint4->GetBound()->UpdateBoundLocation(x, y);
						
						armLeftJoint1->SetAngularSpeed(D3DX_PI/60);
						armLeftJoint2->SetAngularSpeed(D3DX_PI/60);
						armLeftJoint3->SetAngularSpeed(D3DX_PI/60);
						armLeftJoint4->SetAngularSpeed(D3DX_PI/60);

						//trick to make some delay on the joint outside
						armLeftJoint1->SetAngle(-D3DX_PI);
						armLeftJoint2->SetAngle(-D3DX_PI - D3DX_PI *6/ 60);
						armLeftJoint3->SetAngle(-D3DX_PI - D3DX_PI *12/ 60);
						armLeftJoint4->SetAngle(-D3DX_PI - D3DX_PI *24/ 60);

						armLeftJoint1->SetRadius(16);
						armLeftJoint2->SetRadius(16);
						armLeftJoint3->SetRadius(16);
						armLeftJoint4->SetRadius(16);

						armLeftJoint1->SetMoveToPos(x - 16 * 1, y);
						armLeftJoint2->SetMoveToPos(x - 16 * 2, y);
						armLeftJoint3->SetMoveToPos(x - 16 * 3, y);
						armLeftJoint4->SetMoveToPos(x - 16 * 4, y);

						boss3->AddArmLeft(s);
						boss3->AddArmLeftJoint(armLeftJoint1);
						boss3->AddArmLeftJoint(armLeftJoint2);
						boss3->AddArmLeftJoint(armLeftJoint3);
						boss3->AddArmLeftJoint(armLeftJoint4);

						armLeftJoint1->SetParent(boss3);
						armLeftJoint2->SetParent(boss3);
						armLeftJoint3->SetParent(boss3);
						armLeftJoint4->SetParent(boss3);

						armLeftJoint1->SetFrontSibling(boss3->armLeft);
						armLeftJoint2->SetFrontSibling(armLeftJoint1);
						armLeftJoint3->SetFrontSibling(armLeftJoint2);
						armLeftJoint4->SetFrontSibling(armLeftJoint3);

						AddMovingObject(s);
						AddMovingObject(armLeftJoint1);
						AddMovingObject(armLeftJoint2);
						AddMovingObject(armLeftJoint3);
						AddMovingObject(armLeftJoint4);
					}
					if (objectName == "Boss3ArmRight") {
						ArmJoint* s = new ArmJoint(15, "ArmRight", "Enemy", 12);
						s->LoadAssets();
						s->GetBound()->UpdateBoundLocation(worldX, worldY);
						ArmJoint* armRightJoint1 = new ArmJoint(15, "ArmJoint", "Enemy", 14);
						ArmJoint* armRightJoint2 = new ArmJoint(15, "ArmJoint", "Enemy", 14);
						ArmJoint* armRightJoint3 = new ArmJoint(15, "ArmJoint", "Enemy", 14);
						ArmJoint* armRightJoint4 = new ArmJoint(15, "ArmJoint", "Enemy", 14,false,true);

						float x, y;
						x = worldX;
						y = worldY;

						armRightJoint1->LoadAssets();
						armRightJoint1->GetBound()->UpdateBoundLocation(x, y);
						armRightJoint2->LoadAssets();
						armRightJoint2->GetBound()->UpdateBoundLocation(x, y);
						armRightJoint3->LoadAssets();
						armRightJoint3->GetBound()->UpdateBoundLocation(x, y);
						armRightJoint4->LoadAssets();
						armRightJoint4->GetBound()->UpdateBoundLocation(x, y);

						boss3->AddArmLeft(s);
						boss3->AddArmLeftJoint(armRightJoint1);
						boss3->AddArmLeftJoint(armRightJoint2);
						boss3->AddArmLeftJoint(armRightJoint3);
						boss3->AddArmLeftJoint(armRightJoint4);

						armRightJoint1->SetAngularSpeed(D3DX_PI / 60);
						armRightJoint2->SetAngularSpeed(D3DX_PI / 60);
						armRightJoint3->SetAngularSpeed(D3DX_PI / 60);
						armRightJoint4->SetAngularSpeed(D3DX_PI / 60);

						//trick to make some delay on the joint outside
						armRightJoint2->SetAngle(D3DX_PI * 6 / 60);
						armRightJoint3->SetAngle(D3DX_PI * 12 / 60);
						armRightJoint4->SetAngle(D3DX_PI * 24 / 60);

						armRightJoint1->SetRadius(16);
						armRightJoint2->SetRadius(16);
						armRightJoint3->SetRadius(16);
						armRightJoint4->SetRadius(16);

						armRightJoint1->SetMoveToPos(x + 16 * 1, y);
						armRightJoint2->SetMoveToPos(x + 16 * 2, y);
						armRightJoint3->SetMoveToPos(x + 16 * 3, y);
						armRightJoint4->SetMoveToPos(x + 16 * 4, y);

						armRightJoint1->SetParent(boss3);
						armRightJoint2->SetParent(boss3);
						armRightJoint3->SetParent(boss3);
						armRightJoint4->SetParent(boss3);

						armRightJoint1->SetFrontSibling(boss3->armLeft);
						armRightJoint2->SetFrontSibling(armRightJoint1);
						armRightJoint3->SetFrontSibling(armRightJoint2);
						armRightJoint4->SetFrontSibling(armRightJoint3);

						AddMovingObject(s);
						AddMovingObject(armRightJoint1);
						AddMovingObject(armRightJoint2);
						AddMovingObject(armRightJoint3);
						AddMovingObject(armRightJoint4);
					}

				}
				else if(objectType =="object")
				{
					if (objectName == "Bridge") {
						Bridge* s = new Bridge(-1, "Bridge", "Bridge",worldX,worldY);
						s->Init(worldX, worldY);
						AddMovingObject(s);
						AddMovingObject(s->bH);
						AddMovingObject(s->bB1);
						AddMovingObject(s->bB2);
						AddMovingObject(s->bB3);
					}
					if (objectName.find("StaticWeapon") != std::string::npos) {
						GameObject* s = new StaticWeapon(8, objectName, "StaticWeapon");
						s->LoadAssets();
						s->GetBound()->UpdateBoundLocation(worldX, worldY);
						AddMovingObject(s);
					}
					if (objectName.find("CapsuleWeapon") != std::string::npos) {
						GameObject* s = new Capsule(9, objectName, "CapsuleWeapon");
						s->LoadAssets();
						s->GetBound()->UpdateBoundLocation(worldX, worldY);
						AddMovingObject(s);
					}
					if (objectName == "DynamicPlatform") {
						GameObject* s = new DynamicPlatform(15, "DynamicPlatform", "Platform");
						s->LoadAssets();
						s->GetBound()->UpdateBoundLocation(worldX, worldY);
						AddMovingObject(s);
					}
				}
				
			}
		}
	}

}

void Map::AddMovingObject(GameObject* o) {
	this->btree->Insert(btree->root, o);
	o->RetrieveBTree(this->btree);
	this->movingObjects.push_back(o);
	this->allObjects.push_back(o);
}

void Map::AddStaticObject(GameObject* o) {
	o->RetrieveBTree(this->btree);
	this->btree->Insert(btree->root, o);
	this->staticObjects.push_back(o);
	this->allObjects.push_back(o);
}

void Map::Render() {
	if(this->tile!=NULL)
		this->tile->Render();
	for (GameObject* gO : this->allObjects) {
		if (!gO->isDeleted)
		{
			if(gO->GetName() == "BodyBoss3" || gO->GetName() == "HeadBoss3" || gO->GetName() == "BodyBoss1Ruined")
				gO->Render();
		}
	}
	for (GameObject* gO: this->allObjects) {
		if (!gO->isDeleted && gO->GetName()!="Platform")
		{
			if (gO->GetName() != "BodyBoss3" && gO->GetName() != "HeadBoss3" && gO->GetName()!="BodyBoss1Ruined")
				gO->Render();
		}
	}
}
void Map::Update(float dt) {
	if(this->tile != NULL)
		this->tile->Update(dt);
	Camera::GetInstance()->Update(dt,this->mapStage);
	//DebugOut(L"\nBtree Root Size, W: %f , H: %f", this->btree->root->bound->w, this->btree->root->bound->h);
	for (auto i = allObjects.begin(); i != allObjects.end(); ++i) {
		if (*i == NULL) {
			continue;
		}
		//this is secure that no enemy left behind can shoot player 
		if (Camera::GetInstance()->GetCameraBound()->x - 100 > (*i)->GetBound()->x && (*i) != NULL && this->mapStage == 1) {
			if (!(*i)->isDeleted && ((*i)->GetType()=="Enemy"|| (*i)->GetType()=="EnemyBullet"))
			{
				(*i)->isDeleted = true;
			}
		}
		if (Camera::GetInstance()->GetCameraBound()->y - 100 >  (*i)->GetBound()->y && (*i) != NULL && this->mapStage == 3) {
			if (!(*i)->isDeleted && ((*i)->GetType() == "Enemy" || (*i)->GetType() == "EnemyBullet"))
			{
				(*i)->isDeleted = true;
			}
		}
		if (!this->mapBound->IsOverlap((*i)->GetBound()) && (*i)->isDeleted==false && (*i)!=NULL) {
			if ((*i)->GetType() == "CapsuleWeapon") {

			}
			else {
				if ((*i)->GetType() == "Player") {
					auto billPointer = (Bill*)(*i);
					billPointer->DecreaseHP();
				}
				(*i)->isDeleted = true;
			}
		}
		if (!(*i)->isDeleted && (*i) != NULL) {
				btree->RemoveGameObjectForUpdate(btree->root, (*i));
				(*i)->Update(dt, &allObjects);
				btree->Insert(btree->root, (*i));
		}
		else if((*i) != NULL && (*i)->isDeleted) {
			if (dynamic_cast<Bill*>(*i)) {
				(*i)->Update(dt, &allObjects);
			}
		}
	}
	if (!allObjects.empty())
	{
		allObjects.erase(std::remove_if(allObjects.begin(), allObjects.end(), [](GameObject* obj) {
			return obj->GetType() == "EnemyBullet" && obj->isDeleted && obj!=NULL;
			}), allObjects.end());
		allObjects.erase(std::remove_if(allObjects.begin(), allObjects.end(), [](GameObject* obj) {
			return obj->GetType() == "PlayerBullet" && obj->isDeleted && obj != NULL;
			}), allObjects.end());
	}
	//for (GameObject* gO : allObjects) {
	//	if (gO->GetType() == "EnemyBullet" && gO->isDeleted) {

	//	}
	//	if (!this->mapBound->IsOverlap(gO->GetBound())) {
	//		gO->isDeleted = true;
	//		btree->RemoveGameObjectForUpdate(btree->root, gO);
	//	}
	//	/*if (gO->GetType() == "SniperBullet") {
	//		DebugOut(L"\nAdded sniper bullet");
	//	}*/
	//	if (gO->isDeleted == false) {
	//		btree->RemoveGameObjectForUpdate(btree->root, gO);
	//		gO->Update(dt,&allObjects);
	//		btree->Insert(btree->root, gO);
	//	}
	//	else {
	//		if (dynamic_cast<Bill*>(gO)) {
	//			gO->Update(dt, &allObjects);
	//		}
	//	}
	//}
	/*for (auto i = movingObjects.begin(); i != movingObjects.end(); ++i) {

		if (!this->mapBound->IsOverlap((*i)->GetBound())) {
			(*i)->isDeleted = true;
		}
		if ((*i)->isDeleted == false) {
				btree->RemoveGameObjectForUpdate(btree->root, (*i));
				btree->Insert(btree->root, (*i));
		}
		else {
			btree->RemoveGameObjectForUpdate(btree->root, (*i));
		}
	}*/
}
