#include "Terreno.h"
#include <iostream>

Terreno::Terreno(GameObject* associated, string TileFile, string MapFile) : Component(associated){
	SDL_Log("chegou aqui0");
	set = new TileSet(associated, 32, 32, TileFile);
	SDL_Log("chegou aqui0.1");
	associated->AddComponent(set);
	SDL_Log("chegou aqui0.2");
	mapa = new TileMap(associated,MapFile, set);
	SDL_Log("chegou aqui0.3");
	associated->AddComponent(mapa);
	SDL_Log("chegou aqui2");
	associated->Box.w = set->GetTileWidth()* mapa->GetWidth();
	associated->Box.h = set->GetTileHeight()* mapa->GetHeight();
	SDL_Log("chegou aqui3");
	colisor = new Collider(associated);
	associated->AddComponent(colisor);
	SDL_Log("chegou aqui4");
}

Terreno::~Terreno(){
	SDL_Log("morreu");
}

void Terreno::Start(){}
void Terreno::Update(float dt){}
void Terreno::Render(){

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

	//SDL_Log("Passou na renderização do Terreno");
}
void Terreno::NotifyCollision(){}
bool Terreno::Is(string type){
	return(type == "Terreno");
}
