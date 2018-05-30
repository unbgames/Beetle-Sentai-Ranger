#ifndef SPRITE
#define SPRITE

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "Component.h"
#include "SDL_include.h"
#include <string>
#include "Sound.h"
#include "Vec2.h"
#include "Timer.h"
#include "Camera.h"

class Component;

using namespace std;

class Sprite : public Component{
    public:
        Sprite(GameObject* associated);
        Sprite(GameObject* associated, string file, int frameCount = 1, float frameTime = 1, float secondsToSelfDestruct = 0);
        ~Sprite();
        void Open(string file);
        void SetClip(int x, int y, int w, int h);
        void Render();
        void Render(int x, int y);
        void Update(float dt);
        int GetWidth();
        int GetHeight();
        bool IsOpen();
        bool Is(string type);
        void SetScaleX(float scaleX, float scaleY);
        Vec2 GetScale();
        void SetFrame(int frame);
        void SetFrameCount(int frameCount);
        void SetFrameTime(float frameTime);
        void SetFlip(bool Flip);
        bool IsAnimationOver();

    private:
        SDL_Texture* texture;
        int width;
        int height;
        Vec2 scale;
        double angle;
        SDL_Rect ClipRect;
        int frameCount;
        int currentFrame;
        float timeElapsed = 0;
        float frameTime;
        float secondsToSelfDestruct;
        Timer selfDestructCount;
        bool flip;
};

#endif