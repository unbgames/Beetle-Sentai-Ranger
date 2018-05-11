#include "Sprite.h"

Sprite::Sprite(GameObject* associated) : Component(associated){
	texture = nullptr;
	scale.x = 1;
	scale.y = 1;
	angle = 0;
	this->secondsToSelfDestruct = 0;
	SetFrameCount(1);
	SetFrameTime(1);
	flip = false;
}

Sprite::Sprite(GameObject* associated, string file, int frameCount, float frameTime, float secondsToSelfDestruct) : Component(associated){
	texture = nullptr;
	scale.x = 1;
	scale.y = 1;
	angle = 0;
	this->secondsToSelfDestruct = secondsToSelfDestruct;
	this->frameCount = frameCount;
	this->frameTime = frameTime;
	Open(file);
	flip = false;
}

Sprite::~Sprite(){}

void Sprite::Open(string file){

	texture = Resources::GetImage(file);

	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	width = width/frameCount;
	SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h){

	ClipRect.x = x;
	ClipRect.y = y;
	ClipRect.w = w;
	ClipRect.h = h;
}

void Sprite::Render(){

	Game* game = Game::GetInstance();
	SDL_Rect dstrect;
	dstrect.x = associated->Box.x - Camera::pos.x;
	dstrect.y = associated->Box.y - Camera::pos.y;
	dstrect.w = ClipRect.w*scale.x;
	dstrect.h = ClipRect.h*scale.y;
	angle = associated->angleDeg;

	int aux;
	if (flip){
		aux = SDL_RenderCopyEx(game->GetRenderer(), texture, &ClipRect, &dstrect, angle, nullptr, SDL_FLIP_HORIZONTAL);
	}
	else{
		aux = SDL_RenderCopyEx(game->GetRenderer(), texture, &ClipRect, &dstrect, angle, nullptr, SDL_FLIP_NONE);
	}
	if (aux < 0){
		SDL_Log("Unable to initialize texture: %s", SDL_GetError());
	}

}	

void Sprite::Render(int x, int y){

	Game* game = Game::GetInstance();
	SDL_Rect dstrect;
	dstrect.x = x;
	dstrect.y = y;
	dstrect.w = ClipRect.w;
	dstrect.h = ClipRect.h;

	SDL_RenderCopy(game->GetRenderer(), texture, &ClipRect, &dstrect);
}

void Sprite::Update(float dt){
	selfDestructCount.Update(dt);
	timeElapsed +=dt;
	currentFrame = ((int)floor(timeElapsed/frameTime))%frameCount;
	//SDL_Log("TE:%f FT:%f FC:%f", timeElapsed, frameTime, frameCount);
	SetClip((currentFrame*GetWidth()) , 0, width, height);

	if (secondsToSelfDestruct > 0){
		if (secondsToSelfDestruct < selfDestructCount.Get()){
			associated->RequestDelete();
		}
	}
}


int Sprite::GetWidth(){
	return((width)*scale.x);
}
int Sprite::GetHeight(){
	return(height*scale.y);
}
bool Sprite::IsOpen(){
	if (texture == nullptr)
		return(false);
	else
		return(true);
}

bool Sprite::Is(string type){
	return(type == "sprite");
}

void Sprite::SetScaleX(float scaleX, float scaleY){
	if(scaleX != 0)
		scale.x = scaleX;
	if(scaleY != 0)
		scale.y = scaleY;

	Vec2 aux = associated->Box.GetCenter();
	associated->Box.w *= scaleX;
	associated->Box.h *= scaleY;
	associated->Box.Centralize(aux.x,aux.y);
}
Vec2 Sprite::GetScale(){
	return(scale);
}

void Sprite::SetFrame(int frame){
	currentFrame = frame;		
	timeElapsed = frame*frameTime;
	SetClip((currentFrame*GetWidth()) , 0, width, height);
}
void Sprite::SetFrameCount(int frameCount){
	this->frameCount = frameCount;
	currentFrame = 0;
	timeElapsed = 0;
	associated->Box.w = GetWidth();
}
void Sprite::SetFrameTime(float frameTime){
	this->frameTime = frameTime;

}

void Sprite::SetFlip(bool Flip){
	flip = Flip;
}

bool Sprite::IsAnimationOver(){
	if (currentFrame == frameCount-1){
		return(true);
	}
	return(false);
}