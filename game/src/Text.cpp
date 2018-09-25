#include "Text.h"

Text::Text(GameObject* associated, string fontFile, int fontSize, TextStyle style, string text, SDL_Color color) : Component(associated){
	this->fontFile = fontFile;
	this->fontSize = fontSize;
	this->style = style;
	this->text = text;
	this->color = color;
	texture = nullptr;
	offset.x = 0;
	offset.y = 0;

	RemakeTexture();
}
Text::~Text(){
	if (texture != nullptr)
		SDL_DestroyTexture(texture);
}

void Text::Update(float dt){}
void Text::Render(){
	Game* game = Game::GetInstance();
	SDL_Rect dstrect, ClipRect;

	ClipRect.x = 0;
	ClipRect.y = 0;
	ClipRect.w = associated->Box.w;
	ClipRect.h = associated->Box.h;

	dstrect.x = associated->Box.x - Camera::pos.x + offset.x;
	dstrect.y = associated->Box.y - Camera::pos.y + offset.y;
	dstrect.w = ClipRect.w;
	dstrect.h = ClipRect.h;
	double angle = associated->angleDeg;

	int aux = SDL_RenderCopyEx(game->GetRenderer(), texture, &ClipRect, &dstrect, angle, nullptr, SDL_FLIP_NONE);
	if (aux < 0){
		SDL_Log("Unable to initialize texture: %s", SDL_GetError());
	}
}
bool Text::Is(string type){
	return(type == "Text");
}

void Text::SetText(string text){
	this->text = text;
	RemakeTexture();
}
void Text::SetColor(SDL_Color color){
	this->color = color;
	RemakeTexture();
}
void Text::SetStyle(TextStyle style){
	this->style = style;
	RemakeTexture();
}
void Text::SetFontFile(string fontFile){
	this->fontFile = fontFile;
	RemakeTexture();
}
void Text::SetFontSize(int fontSize){
	this->fontSize = fontSize;
	RemakeTexture();
}

void Text::RemakeTexture(){
	if (texture != nullptr)
		SDL_DestroyTexture(texture);

	Game* game = Game::GetInstance();
	SDL_Surface* surface;

	font = Resources::GetFont(fontFile, fontSize);

	if (style == TextStyle::SOLID)
		surface = TTF_RenderText_Solid(font, text.c_str(), color);

	if (style == TextStyle::SHADED){
		SDL_Color bg = {0,0,0,0};
		surface = TTF_RenderText_Shaded(font, text.c_str(), color, bg);
	}

	if (style == TextStyle::BLENDED)
		surface = TTF_RenderText_Blended(font, text.c_str(), color);

	texture = SDL_CreateTextureFromSurface(game->GetRenderer(), surface);

	associated->Box.w = surface->w;
	associated->Box.h = surface->h;

	SDL_FreeSurface(surface);
}

void Text::SetOffset(Vec2 newOffset){
	offset = newOffset;
}