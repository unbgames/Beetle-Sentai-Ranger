#include "Terrain.h"

Terrain::Terrain(GameObject* associated, string TileFile, string MapFile){

	TileSet* set = new TileSet(aux2, STAGE1_TILESET_WIDTH, STAGE1_TILESET_HEIGHT, TileFile);
	associated->AddComponent(colisor);
	
	mapa = new TileMap(aux2,MapFile, set);
	associated->AddComponent(mapa);

	associated->Box.w = tileSet->GetTileWidth()* mapa->GetWidth();
		
	associated->Box.h = tileSet->GetTileHeight()* mapa->GetHeight();

	colisor = new Collider(associated);
	associated->AddComponent(colisor);
}
Terrain::~Terrain(){}
void Terrain::Start(){}
void Terrain::Update(float dt){}
void Terrain::Render(){}
void Terrain::NotifyCollision(){}
bool Terrain::Is(string type){
	return(type == "Terrain");
}