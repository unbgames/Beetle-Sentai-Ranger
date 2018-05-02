#ifndef SOUND
#define SOUND

#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "GameObject.h"
#include "Resources.h"
#include <string>
#include <vector>


class Sound : public Component{

public:
	Sound(GameObject* associated);
	Sound(GameObject* associated, string file);
	~Sound();

	void Play (int times);
	void Stop ();
	void Open (string file);
	bool IsOpen ();
	void Update(float dt);
	void Render();
	bool Is(string type);

private:
	Mix_Chunk* chunk;
	int channel;
};

#endif