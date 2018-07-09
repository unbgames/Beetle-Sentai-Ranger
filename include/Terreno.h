#ifndef TERRENO
#define TERRENO

#include "Component.h"
#include "TileMap.h"
#include "Collider.h"

class Terreno : public Component{
	public:
		Terreno(GameObject* associated, string TileFile, string MapFile);
		~Terreno();
		void Start();
		void Update(float dt);
		void Render();
		bool Is(string type);
		void NotifyCollision();

	private:
		TileMap* mapa = nullptr;
		Collider* colisor = nullptr;
		TileSet* set = nullptr;

};

#endif
