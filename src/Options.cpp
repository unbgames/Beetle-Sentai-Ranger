#include "MainMenu.h"
#include "Options.h"

Options::Options()
{
	quitRequested = false;
	popRequested = false;

	backgroundIntroOptions.Open(MAINMENU_BACKGROUNDMUSIC_INTRO);
	backgroundLoopOptions.Open(MAINMENU_BACKGROUNDMUSIC_LOOP);
	backgroundIntroOptions.Play(1);
}

Options::~Options()
{
	backgroundLoopOptions.Stop();
	ObjectArray.clear();
}

void Options::LoadAssets()
{
	GameObject* aux = new GameObject();
	aux->Box.x = 0;
	aux->Box.y = 0;
	Sprite* bg = new Sprite(aux, OPTIONS_BACKGROUND);
	aux->AddComponent(bg);
	ObjectArray.emplace_back(aux);

	GameObject* buttonBack = new GameObject();
	spriteButtonOptions = new Sprite(buttonBack, OPTIONS_BACK_BUTTON_NOTPRESSED);
	buttonBack->Box.x = 512 - (spriteButtonOptions->GetWidth()/2.0);
	buttonBack->Box.y = 450 - (spriteButtonOptions->GetHeight()/2.0);
	buttonBack->AddComponent(spriteButtonOptions);
	ObjectArray.emplace_back(buttonBack);

	cursorOptions = new GameObject();
	spriteCursorOptions = new Sprite(cursorOptions, MAINMENU_CURSOR);
	cursorOptions->Box.x = 512 + (spriteCursorOptions->GetWidth()*1.8);
	cursorOptions->Box.y = 470;
	cursorOptions->AddComponent(spriteCursorOptions);
	ObjectArray.emplace_back(cursorOptions);
}

void Options::Update(float dt)
{
	if (!backgroundIntroOptions.IsPlaying())
	{
		//SDL_Log("chegou aqui");
		backgroundIntroOptions.Stop(0);
		backgroundLoopOptions.Play(-1);
	}

	InputManager& input = InputManager::GetInstance();

	if(input.QuitRequested())
		quitRequested = true;

	if (input.KeyPress(SDLK_ESCAPE))
		popRequested = true;

	if(input.KeyPress(SDLK_DOWN))
		cursorIndexOptions++;

	if(input.KeyPress(SDLK_UP))
		cursorIndexOptions--;

	if(cursorIndexOptions > CURSOR_INDEX_OPTIONS_MAX)
		cursorIndexOptions = 0;

	if(cursorIndexOptions < 0)
		cursorIndexOptions = CURSOR_INDEX_OPTIONS_MAX;

	switch(cursorIndexOptions)
	{
		case 0:
			cursorOptions->Box.x = 512 + (spriteCursorOptions->GetWidth()*1.8);
			cursorOptions->Box.y = 470;
			break;

		default:
			SDL_Log("Deu merda no cursor");
			break;
	}

	if (input.KeyPress(SDLK_RETURN) && cursorIndexOptions == 0)
	{
		buttonPressedOptions = new GameObject();
		spriteButtonOptions = new Sprite(buttonPressedOptions, OPTIONS_BACK_BUTTON_PRESSED);
		buttonPressedOptions->Box.x = 512 - (spriteButtonOptions->GetWidth()/2.0);
		buttonPressedOptions->Box.y = 450 - (spriteButtonOptions->GetHeight()/2.0);
		buttonPressedOptions->AddComponent(spriteButtonOptions);
		ObjectArray.emplace_back(buttonPressedOptions);

		Game* game = Game::GetInstance();
		backgroundLoopOptions.Stop();
		game->Push(new MainMenu());
		popRequested = true;
	}

	Camera::Update(dt);

	UpdateArray(dt);
}

void Options::Render()
{
	RenderArray();
}

void Options::Start()
{
	Camera::Unfollow();
	Camera::pos.x = 0;
	Camera::pos.y = 0;
	LoadAssets();
	StartArray();
}

void Options::Pause(){}
void Options::Resume(){}
