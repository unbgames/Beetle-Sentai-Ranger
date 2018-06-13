class Terrain : public Component{
	public:
		Terrain();
		~Terrain();
		Start();
		Update(float dt);
		Render();
		void NotifyCollision();

	private:
		TileMap* mapa;
		Collider* colisor;
	
};