#ifndef TEXT
#define TEXT

#include "Component.h"
#include "Resources.h"
#include "Camera.h"
#include "Vec2.h"

class Text : public Component{

	public:
		typedef enum TextStyle {SOLID, SHADED, BLENDED} TextStyle;
		Text(GameObject* associated, string fontFile, int fontSize, TextStyle style, string text, SDL_Color color);
		~Text();
		
		void Update(float dt);
		void Render();
		bool Is(string type);

		void SetText(string text);
		void SetColor(SDL_Color color);
		void SetStyle(TextStyle style);
		void SetFontFile(string fontFile);
		void SetFontSize(int fontSize);
		void SetOffset(Vec2 newOffset);

	private:
		void RemakeTexture();
		TTF_Font* font;
		SDL_Texture* texture;
		string text;
		TextStyle style;
		string fontFile;
		int fontSize;
		SDL_Color color;
		Vec2 offset;	
};
#endif