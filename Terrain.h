#ifndef TERRAIN
#define TERRAIN

#include "Component.h"
#include "TileMap.h"
#include "Collider.h"

class Terrain : public Component{
	public:
		Terrain(GameObject* associated, string TileFile, string MapFile);
		~Terrain();
		void Start();
		void Update(float dt);
		void Render();
		bool Is(string type);
		void NotifyCollision();

	private:
		TileMap* mapa;
		Collider* colisor;
	
};

#endif