#ifndef TERRAIN
#define TERRAIN

#include <fstream>
#include <string>
#include <string.h>
#include "TileSet.h"
#include "Component.h"
#include "Camera.h"
#include "Collider.h"

class Terrain : public Component{
	public:
		Terrain(GameObject* associated, string file, TileSet* tileSet);
		~Terrain();
		void Load(string file);
		void SetTileSet(TileSet* tileSet);
		void Update(float dt);
		void Render();
		void RenderTerrain(int cameraX = 0, int cameraY = 0);
		int GetTileNumber();
		bool Is(string type);
		void NotifyCollision(GameObject* other);

	private:
		vector<int> tileList;
		TileSet* tileSet;
		int tileNumber;
};

#endif
