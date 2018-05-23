#ifndef PLATFORM
#define PLATFORM

#include <fstream>
#include <string>
#include <string.h>
#include "TileSet.h"
#include "Component.h"
#include "Camera.h"
#include "Collider.h"

class Platform : public Component{
	public:
		Platform(GameObject* associated, string file, TileSet* tileSet);
		~Platform();
		void Load(string file);
		void SetTileSet(TileSet* tileSet);
		void Update(float dt);
		void Render();
		void RenderRow(int cameraX = 0, int cameraY = 0);
		int GetTileNumber();
		bool Is(string type);
		void NotifyCollision(GameObject* other);

	private:
		vector<int> tileList;
		TileSet* tileSet;
		int tileNumber;
		
};

#endif