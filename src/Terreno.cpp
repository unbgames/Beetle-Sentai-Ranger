#include "Terreno.h"
#include <iostream>

Terreno::Terreno(GameObject* associated, string TileFile, string MapFile) : Component(associated){

	set = new TileSet(associated, 32, 32, TileFile);
	mapa = new TileMap(associated,MapFile, set);
	this->mapa = mapa;

	associated->Box.w = set->GetTileWidth()* mapa->GetWidth();
	associated->Box.h = set->GetTileHeight()* mapa->GetHeight();

	colisor = new Collider(associated);
	associated->AddComponent(colisor);
}

Terreno::~Terreno(){}

void Terreno::Start(){}
void Terreno::Update(float dt){}
void Terreno::Render()
{
	float x = associated->Box.x;
	float y = associated->Box.y;

	vector<int> aux_matriz = mapa->GetTileMatrix();

	float aux_y = y;

	for(int j = 0; j < mapa->GetWidth(); ++j)
	{
		for (int i = 0; i < mapa->GetHeight(); ++i)
		{
			set->RenderTile(aux_matriz[i+j], x-Camera::pos.x, y-Camera::pos.y);
			y+= set->GetTileHeight();
		}
		x+= set->GetTileWidth();
		y = aux_y;
	}

	SDL_Log("Passou na renderização do Terreno");
}
void Terreno::NotifyCollision(){}
bool Terreno::Is(string type){
	return(type == "Terreno");
}
