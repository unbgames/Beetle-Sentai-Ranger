#ifndef RESOURCES
#define RESOURCES

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include <unordered_map>
#include <string>
#include "SDL_include.h"
#include "Game.h"

using namespace std;

class Resources{
	public:
		Resources();
		~Resources();
		static SDL_Texture* GetImage(string file);
		static void ClearImages();
		static Mix_Music* GetMusic(string file);
		static void ClearMusics();
		static Mix_Chunk* GetSound(string file); 
		static void ClearSounds();
		static TTF_Font* GetFont(string file, int ptsize); 
		static void ClearFonts();

	private:
		static unordered_map<string, SDL_Texture*> imageTable;
		static unordered_map<string, Mix_Music*> musicTable;
		static unordered_map<string, Mix_Chunk*> soundTable;
		static unordered_map<string, TTF_Font*> fontTable;
};

#endif