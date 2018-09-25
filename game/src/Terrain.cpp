#include "Terrain.h"
#include <iostream>

Terrain::Terrain(GameObject* associated, string file, TileSet* tileSet) : Component(associated){
	this->tileSet = tileSet;
	Load(file);
	associated->Box.w = tileSet->GetTileWidth()*15;
	associated->Box.h = tileSet->GetTileHeight()*tileNumber;

	Collider* colisor = new Collider(associated);
	associated->AddComponent(colisor);
}

Terrain::~Terrain(){}

void Terrain::Load(string file){

	ifstream mapa(file);
	string aux;
	int ancora;
	tileNumber = 0;

	if (!mapa.good()){
		SDL_Log("problema ao carregar o mapa");
	}

	while(getline(mapa,aux,',')){
		ancora = atoi(aux.c_str());
		ancora--;
		tileList.push_back(ancora);
		tileNumber++;
	}
	mapa.close();
}

void Terrain::SetTileSet(TileSet* tileSet){
	this->tileSet = tileSet;
}

void Terrain::RenderTerrain(int cameraX, int cameraY){

	float x = associated->Box.x;
	float y = associated->Box.y;

	float aux_y = y;

	for(int j = 0; j < 15; ++j)
	{
		for (int i = 0; i < tileNumber; ++i)
	  {
			tileSet->RenderTile(tileList[i], x-cameraX, y-cameraY);
			y+= tileSet->GetTileHeight();
		}
		x+= tileSet->GetTileWidth();
		y = aux_y;
	}
}
void Terrain::Render()
{
	RenderTerrain(Camera::pos.x, Camera::pos.y);
}

int Terrain::GetTileNumber(){
	return(tileNumber);
}

void Terrain::Update(float dt){}

bool Terrain::Is(string type){
	return(type == "Terrain");
}

void Terrain::NotifyCollision(GameObject* other){}
