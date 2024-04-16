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
				/*string s =objectName;
				wstring temp = wstring(s.begin(), s.end());
				LPCWSTR wideString = temp.c_str();
				DebugOut(L"\n");
				DebugOut(wideString);*/
				if (objectType == "enemy") {
					if (objectName == "Soldier") {
						GameObject* s = new Soldier(1, "Soldier", "Enemy", 1);
						s->LoadAssets();
						s->GetBound()->UpdateBoundLocation(worldX, worldY);
						//AddMovingObject(s);

					}
					if (objectName == "Sniper") {
						GameObject* s = new Sniper(2, "Sniper", "Enemy", 1);
						s->LoadAssets();
						s->GetBound()->UpdateBoundLocation(worldX, worldY);
						//AddMovingObject(s);
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
				}
				else if(objectType =="object")
				{
					if (objectName == "Bridge") {
						Bridge* s = new Bridge(-1, "Bridge", "Bridge",worldX,worldY);
						s->Init(worldX, worldY);
						//DebugOut(L"\ny: %f, worldY: %f", s->bH->GetBound()->y, worldY);
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
	this->tile->Render();
	
	for (GameObject* gO: this->allObjects) {
		if (!gO->isDeleted)
		{
			gO->Render();
		}
	}
}
void Map::Update(float dt) {
	this->tile->Update(dt);
	Camera::GetInstance()->Update(dt,this->mapStage);
	for (auto i = allObjects.begin(); i != allObjects.end(); ++i) {
		if (*i == NULL) {
			continue;
		}
		//this is secure that no enemy left behind can shoot player 
		if (Camera::GetInstance()->GetCameraBound()->x - 100 > (*i)->GetBound()->x && (*i) != NULL) {
			if (!(*i)->isDeleted && ((*i)->GetType()=="Enemy"|| (*i)->GetType()=="EnemyBullet"))
			{
				(*i)->isDeleted = true;
			}
		}
		if (Camera::GetInstance()->GetCameraBound()->y - 100 > (*i)->GetBound()->y && (*i) != NULL) {
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
			return obj->GetType() == "EnemyBullet" && obj->isDeleted;
			}), allObjects.end());
		allObjects.erase(std::remove_if(allObjects.begin(), allObjects.end(), [](GameObject* obj) {
			return obj->GetType() == "PlayerBullet" && obj->isDeleted;
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
