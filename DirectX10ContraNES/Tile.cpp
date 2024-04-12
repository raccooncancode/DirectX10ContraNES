#include "Tile.h"

void Tile::LoadTileSetTexture(LPTEXTURE tex) {
	this->tileTexture = tex;
}
void Tile::LoadMap2D(std::vector<std::vector<int>>& data) {
	this->map2D = data;
}
void Tile::LoadTiles(int tileSize) {
	int tileCounted = 0;
	this->tileSize = tileSize;
	int tileSetColumns = this->tileTexture->getWidth() / tileSize;
	int tileSetRows = this->tileTexture->getHeight() / tileSize;
	for (int i = 0; i < tileSetRows; i++) {
		for (int j = 0; j < tileSetColumns; j++) {
			this->tiles[tileCounted] = new CSprite(j * tileSize, i * tileSize, tileSize, tileSize, tileTexture);
			this->animationTiles[tileCounted] = new CAnimation(1, 1000.0f, false);
			this->animationTiles[tileCounted]->AddFrame(this->tiles[tileCounted]);
			//just like tile but change to animtion class for animation case retrieve with id
			tileCounted++;
		}
	}
}
void Tile::LoadAnimationTiles(tinyxml2::XMLElement* e) {
	tinyxml2::XMLElement* xmlTile = nullptr;
	tinyxml2::XMLElement* xmlAnimationTile = nullptr;
	tinyxml2::XMLElement* xmlFrame = nullptr;

	int getId;
	std::vector<int> frameIds;
	int frameId;
	for (xmlTile = e->NextSiblingElement(); xmlTile != NULL; xmlTile = xmlTile->NextSiblingElement()) {

		xmlTile->QueryIntAttribute("id", &getId);
		int animatedTileId = getId;
		//DebugOut(L"\nTile ID: %d", animatedTileId);
		xmlAnimationTile = xmlTile->FirstChildElement();
		for (xmlFrame = xmlAnimationTile->FirstChildElement(); xmlFrame != NULL; xmlFrame = xmlFrame->NextSiblingElement()) {
			xmlFrame->QueryIntAttribute("tileid", &frameId);
			int temp = frameId;
			frameIds.push_back(temp);
		}
		this->animationTiles[animatedTileId] = new CAnimation(frameIds.size(), 300.0f, true);
		for (int i = 0; i < frameIds.size(); i++) {
			//DebugOut(L"\nFrame ID: %d", frameIds[i]);
			this->animationTiles[animatedTileId]->AddFrame(this->tiles[frameIds[i]]);
		}
		frameIds.clear();
	}
}

void Tile::Update(float dt) {
	for (auto i = animationTiles.begin(); i != animationTiles.end(); ++i) {
		i->second->Update(dt,NULL,false);
	}
}
void Tile::Render() {
	auto camera = Camera::GetInstance();
	Bound cameraBound = camera->GetCameraBound();
	//DebugOut(L"\nCamera X: %f, Y: %f , W: %f , H: %f", cameraBound->x, cameraBound->y, cameraBound->w, cameraBound->h);
	float worldY, worldX, drawingX, drawingY;
	for (int r = 0; r < map2D.size(); r++) {
		for (int c = 0; c < map2D[r].size(); c++) {
			worldY = r * tileSize;
			worldX = c * tileSize;
			if (cameraBound->IsOverlap(worldX, worldY, tileSize, tileSize)) {

			drawingX = worldX + (float)tileSize / 2;
			drawingY = worldY + (float)tileSize / 2;
			this->animationTiles[map2D[r][c]]->Render(
				drawingX,
				drawingY
			);
			}
		}
	}
}
