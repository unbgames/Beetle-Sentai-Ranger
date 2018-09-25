#ifndef COLUMN
#define COLUMN

#include <fstream>
#include <string>
#include <string.h>
#include "TileSet.h"
#include "Component.h"
#include "Camera.h"
#include "Collider.h"

class Column : public Component{
	public:
		Column(GameObject* associated, string file, TileSet* tileSet);
		~Column();
		void Load(string file);
		void SetTileSet(TileSet* tileSet);
		void Update(float dt);
		void Render();
		void RenderColumn(int cameraX = 0, int cameraY = 0);
		int GetTileNumber();
		bool Is(string type);
		void NotifyCollision(GameObject* other);

	private:
		vector<int> tileList;
		TileSet* tileSet;
		int tileNumber;
};

#endif
