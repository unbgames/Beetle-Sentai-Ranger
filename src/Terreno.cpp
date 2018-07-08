#include "Terreno.h"
#include <iostream>

Terreno::Terreno(GameObject* associated, string TileFile, string MapFile) : Component(associated){

	set = new TileSet(associated, 32, 32, TileFile);
	associated->AddComponent(set);

	mapa = new TileMap(associated,MapFile, set);
	associated->AddComponent(mapa);

	associated->Box.w = set->GetTileWidth()* mapa->GetWidth();
	associated->Box.h = set->GetTileHeight()* mapa->GetHeight();

	colisor = new Collider(associated);
	associated->AddComponent(colisor);
}

Terreno::~Terreno(){}

void Terreno::Start(){}
void Terreno::Update(float dt){}
void Terreno::Render(){

	float x = associated->Box.x;
	float y = associated->Box.y;

	vector<int> aux_matriz = mapa->GetTileMatrix();

	float aux_x = x;

	for(int j = 0; j < mapa->GetHeight(); ++j)
	{
		for (int i = 0; i < mapa->GetWidth(); ++i)
		{
			set->RenderTile(aux_matriz[i+j*mapa->GetWidth()], x-Camera::pos.x, y-Camera::pos.y);
			x+= set->GetTileWidth();
			//std::cout << aux_matriz[i+j*mapa->GetWidth()] << "\t";
		}
		y+= set->GetTileHeight();
		x = aux_x;
		//std::cout << "\n";
	}
}
void Terreno::NotifyCollision(){}
bool Terreno::Is(string type){
	return(type == "Terreno");
}
