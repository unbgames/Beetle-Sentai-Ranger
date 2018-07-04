#include "MainMenu.h"
#include "Stage1.h"
#include "Options.h"

MainMenu::MainMenu()
{
	quitRequested = false;
	popRequested = false;

	backgroundIntro.Open(MAINMENU_BACKGROUNDMUSIC_INTRO);
	backgroundLoop.Open(MAINMENU_BACKGROUNDMUSIC_LOOP);
	backgroundIntro.Play(1);
}

MainMenu::~MainMenu()
{
	backgroundLoop.Stop();
	ObjectArray.clear();
}

void MainMenu::LoadAssets()
{
	GameObject* aux = new GameObject();
	aux->Box.x = 0;
	aux->Box.y = 0;
	Sprite* bg = new Sprite(aux, MAINMENU_BACKGROUND);
	aux->AddComponent(bg);
	ObjectArray.emplace_back(aux);

	GameObject* logo = new GameObject();
	Sprite* spriteLogo = new Sprite(logo, MAINMENU_LOGO);
	spriteLogo->SetScaleX(1.5, 1.5);
	logo->Box.x = 512 - (spriteLogo->GetWidth()/2.0);
	logo->Box.y = 100 - (spriteLogo->GetHeight()/2.0);
	logo->AddComponent(spriteLogo);
	ObjectArray.emplace_back(logo);

	GameObject* buttonPlay = new GameObject();
	spriteButton = new Sprite(buttonPlay, MAINMENU_PLAY_BUTTON_NOTPRESSED);
	buttonPlay->Box.x = 512 - (spriteButton->GetWidth()/2.0);
	buttonPlay->Box.y = 300 - (spriteButton->GetHeight()/2.0);
	buttonPlay->AddComponent(spriteButton);
	ObjectArray.emplace_back(buttonPlay);

	GameObject* buttonOptions = new GameObject();
	spriteButton = new Sprite(buttonOptions, MAINMENU_OPTIONS_BUTTON_NOTPRESSED);
	buttonOptions->Box.x = 512 - (spriteButton->GetWidth()/2.0);
	buttonOptions->Box.y = 400 - (spriteButton->GetHeight()/2.0);
	buttonOptions->AddComponent(spriteButton);
	ObjectArray.emplace_back(buttonOptions);

	GameObject* buttonExit = new GameObject();
	spriteButton = new Sprite(buttonExit, MAINMENU_EXIT_BUTTON_NOTPRESSED);
	buttonExit->Box.x = 512 - (spriteButton->GetWidth()/2.0);
	buttonExit->Box.y = 500 - (spriteButton->GetHeight()/2.0);
	buttonExit->AddComponent(spriteButton);
	ObjectArray.emplace_back(buttonExit);

	cursor = new GameObject();
	spriteCursor = new Sprite(cursor, MAINMENU_CURSOR, 6, 0.2, 0);
	cursor->Box.x = 512 + (spriteCursor->GetWidth()*1.8);
	cursor->Box.y = 275;
	cursor->AddComponent(spriteCursor);
	ObjectArray.emplace_back(cursor);
}

void MainMenu::Update(float dt)
{
	if (!backgroundIntro.IsPlaying())
	{
		//SDL_Log("chegou aqui");
		backgroundIntro.Stop(0);
		backgroundLoop.Play(-1);
	}

	InputManager& input = InputManager::GetInstance();

	if (input.KeyPress(SDLK_q)){
		Game* game = Game::GetInstance();
		game->Push(new CreditState(CREDIT_TEXT));
	}

	if(input.QuitRequested())
		quitRequested = true;

	if (input.KeyPress(SDLK_ESCAPE))
		popRequested = true;

	if(input.KeyPress(SDLK_DOWN))
		cursorIndex++;

	if(input.KeyPress(SDLK_UP))
		cursorIndex--;

	if(cursorIndex > CURSOR_INDEX_MAX)
		cursorIndex = 0;

	if(cursorIndex < 0)
		cursorIndex = CURSOR_INDEX_MAX;

	switch(cursorIndex)
	{
		case 0:
			cursor->Box.x = 512 + (spriteCursor->GetWidth()*1.8);
			cursor->Box.y = 275;
			break;

		case 1:
			cursor->Box.x = 512 + (spriteCursor->GetWidth()*1.8);
			cursor->Box.y = 375;
			break;

		case 2:
			cursor->Box.x = 512 + (spriteCursor->GetWidth()*1.8);
			cursor->Box.y = 475;
			break;

		default:
			SDL_Log("Deu merda no cursor");
			break;
	}

	if (input.KeyPress(SDLK_RETURN) && cursorIndex == 0)
	{
		buttonPressed = new GameObject();
		spriteButton = new Sprite(buttonPressed, MAINMENU_PLAY_BUTTON_PRESSED);
		buttonPressed->Box.x = 512 - (spriteButton->GetWidth()/2.0);
		buttonPressed->Box.y = 300 - (spriteButton->GetHeight()/2.0);
		buttonPressed->AddComponent(spriteButton);
		ObjectArray.emplace_back(buttonPressed);

		Game* game = Game::GetInstance();
		backgroundLoop.Stop();
		game->Push(new Stage1(4));
		popRequested = true;
	}

	if (input.KeyPress(SDLK_RETURN) && cursorIndex == 1)
	{
		//SDL_Log("Options");

		buttonPressed = new GameObject();
		spriteButton = new Sprite(buttonPressed, MAINMENU_OPTIONS_BUTTON_PRESSED);
		buttonPressed->Box.x = 512 - (spriteButton->GetWidth()/2.0);
		buttonPressed->Box.y = 400 - (spriteButton->GetHeight()/2.0);
		buttonPressed->AddComponent(spriteButton);
		ObjectArray.emplace_back(buttonPressed);
		//ObjectArray.swap(ObjectArray[ObjectArray.size()-1], ObjectArray[ObjectArray.size()-2]);

		Game* game = Game::GetInstance();
		backgroundLoop.Stop();
		game->Push(new Options());
		popRequested = true;
	}

	if (input.KeyPress(SDLK_RETURN) && cursorIndex == 2)
	{
		buttonPressed = new GameObject();
		spriteButton = new Sprite(buttonPressed, MAINMENU_EXIT_BUTTON_PRESSED);
		buttonPressed->Box.x = 512 - (spriteButton->GetWidth()/2.0);
		buttonPressed->Box.y = 500 - (spriteButton->GetHeight()/2.0);
		buttonPressed->AddComponent(spriteButton);
		ObjectArray.emplace_back(buttonPressed);

		backgroundLoop.Stop();
		popRequested = true;
	}

	Camera::Update(dt);

	UpdateArray(dt);
}

void MainMenu::Render()
{
	RenderArray();
}

void MainMenu::Start()
{
	Camera::Unfollow();
	Camera::pos.x = 0;
	Camera::pos.y = 0;
	LoadAssets();
	StartArray();
}

void MainMenu::Pause(){}
void MainMenu::Resume(){}
