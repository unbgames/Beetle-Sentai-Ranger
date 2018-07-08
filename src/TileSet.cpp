#include "TileSet.h"

TileSet::TileSet(GameObject* associated, int tileWidth, int tileHeight, string file) : Component(associated){

	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	SDL_Log("tileset nao aberto");
	tileSet.Open(file);
	SDL_Log("tileset aberto");
	columns = (tileSet.GetWidth() / tileWidth);
	rows = (tileSet.GetHeight() / tileHeight);
	SDL_Log("tileset construido");
}
TileSet::~TileSet(){}

void TileSet::RenderTile(unsigned index, float x, float y){

	int coordX;
	int coordY;

	if (index >= 0 && index < ((columns*rows)-1) ){
		coordX = index%columns;
		coordY = floor((float)index/(float)columns);

		tileSet.SetClip(coordX*tileWidth, coordY*tileHeight, tileWidth, tileHeight);
		tileSet.Render(x, y);
	}
}
int TileSet::GetTileWidth (){
	return(tileWidth);
}
int TileSet::GetTileHeight(){
	return(tileHeight);
}

void TileSet::Update(float dt){}
void TileSet::Render(){}
bool TileSet::Is(string type){
	return(type == "TileSet");
}
void TileSet::Start(){}