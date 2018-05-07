#include "Platform.h"

Platform::Platform(GameObject* associated, string file, TileSet* tileSet) : Component(associated){
	this->tileSet = tileSet;
	Load(file);
}
Platform::~Platform(){}
void Platform::Load(string file){

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
void Platform::SetTileSet(TileSet* tileSet){
	this->tileSet = tileSet;
}

void Platform::RenderRow(int cameraX, int cameraY){

	float x = associated->Box.x;
	float y = associated->Box.y;

	for (int i = 0; i < tileNumber; ++i){

		tileSet->RenderTile(tileList[i], x+cameraX, y+cameraY);
		x+= tileSet->GetTileWidth();
	}
	
}
void Platform::Render(){

	RenderRow(-Camera::pos.x, -Camera::pos.y);
	
}
int Platform::GetTileNumber(){
	return(tileNumber);
}

void Platform::Update(float dt){}

bool Platform::Is(string type){
	return(type == "Platform");
}