#include "MainMenu.h"
#include "Options.h"

Options::Options()
{
	quitRequested = false;
	popRequested = false;

	//backgroundIntroOptions.Open(MAINMENU_BACKGROUNDMUSIC_INTRO);
	//backgroundLoopOptions.Open(MAINMENU_BACKGROUNDMUSIC_LOOP);
	//backgroundIntroOptions.Play(1);
}

Options::~Options()
{
	//backgroundLoopOptions.Stop();
	ObjectArray.clear();
}

void Options::LoadAssets()
{
	fstream myReadFile;
	myReadFile.open ("controlsCustom.txt", std::ios::in);

	if(myReadFile.is_open())
	{
		for(int i=0;i<9;++i)
		{
    	myReadFile >> configButtons[i];
		}
	}
	myReadFile.close();

	GameObject* aux = new GameObject();
	aux->Box.x = 0;
	aux->Box.y = 0;
	Sprite* bg = new Sprite(aux, OPTIONS_BACKGROUND);
	aux->AddComponent(bg);
	ObjectArray.emplace_back(aux);

	GameObject* aux2 = new GameObject();
	aux2->Box.x = 100;
	aux2->Box.y = 50;
	Sprite* bg2 = new Sprite(aux2, OPTIONS_PANEL);
	aux2->AddComponent(bg2);
	ObjectArray.emplace_back(aux2);

	GameObject* icon = new GameObject();
	icon->Box.x = 120;
	icon->Box.y = 70;
	Sprite* icon_sprite = new Sprite(icon, OPTIONS_UP_ICON);
	icon->AddComponent(icon_sprite);
	ObjectArray.emplace_back(icon);

	icon = new GameObject();
	icon->Box.x = 120;
	icon->Box.y = 140;
	icon_sprite = new Sprite(icon, OPTIONS_DOWN_ICON);
	icon->AddComponent(icon_sprite);
	ObjectArray.emplace_back(icon);

	icon = new GameObject();
	icon->Box.x = 120;
	icon->Box.y = 210;
	icon_sprite = new Sprite(icon, OPTIONS_LEFT_ICON);
	icon->AddComponent(icon_sprite);
	ObjectArray.emplace_back(icon);

	icon = new GameObject();
	icon->Box.x = 120;
	icon->Box.y = 280;
	icon_sprite = new Sprite(icon, OPTIONS_RIGHT_ICON);
	icon->AddComponent(icon_sprite);
	ObjectArray.emplace_back(icon);

	icon = new GameObject();
	icon->Box.x = 120;
	icon->Box.y = 350;
	icon_sprite = new Sprite(icon, OPTIONS_PUNCH_ICON);
	icon->AddComponent(icon_sprite);
	ObjectArray.emplace_back(icon);

	icon = new GameObject();
	icon->Box.x = 520;
	icon->Box.y = 70;
	icon_sprite = new Sprite(icon, HUD_SHIT_ICON);
	icon->AddComponent(icon_sprite);
	ObjectArray.emplace_back(icon);

	icon = new GameObject();
	icon->Box.x = 520;
	icon->Box.y = 140;
	icon_sprite = new Sprite(icon, HUD_DASH_ICON);
	icon->AddComponent(icon_sprite);
	ObjectArray.emplace_back(icon);

	icon = new GameObject();
	icon->Box.x = 520;
	icon->Box.y = 210;
	icon_sprite = new Sprite(icon, HUD_FLY_ICON);
	icon->AddComponent(icon_sprite);
	ObjectArray.emplace_back(icon);

	icon = new GameObject();
	icon->Box.x = 520;
	icon->Box.y = 280;
	icon_sprite = new Sprite(icon, HUD_ACID_ICON);
	icon->AddComponent(icon_sprite);
	ObjectArray.emplace_back(icon);

	GameObject* buttonBack = new GameObject();
	spriteButtonOptions = new Sprite(buttonBack, OPTIONS_BACK_BUTTON_NOTPRESSED);
	buttonBack->Box.x = 700 - (spriteButtonOptions->GetWidth()/2.0);
	buttonBack->Box.y = 520 - (spriteButtonOptions->GetHeight()/2.0);
	buttonBack->AddComponent(spriteButtonOptions);
	ObjectArray.emplace_back(buttonBack);

	GameObject* buttonChange = new GameObject();
	spriteButtonOptions = new Sprite(buttonChange, OPTIONS_CHANGE_BUTTON_NOTPRESSED);
	buttonChange->Box.x = 350 - (spriteButtonOptions->GetWidth()/2.0);
	buttonChange->Box.y = 520 - (spriteButtonOptions->GetHeight()/2.0);
	buttonChange->AddComponent(spriteButtonOptions);
	ObjectArray.emplace_back(buttonChange);

	cursorOptions = new GameObject();
	spriteCursorOptions = new Sprite(cursorOptions, MAINMENU_CURSOR, 6, 0.2, 0);
	cursorOptions->Box.x = 700 + (spriteCursorOptions->GetWidth()*1.8);
	cursorOptions->Box.y = 495;
	cursorOptions->AddComponent(spriteCursorOptions);
	ObjectArray.emplace_back(cursorOptions);

	GameObject* textIcon = new GameObject();
	SDL_Color color = {0,0,0,0};
	Text* inst = new Text(textIcon, FONT, 36, Text::TextStyle::SOLID,SDL_GetKeyName(configButtons[0]) + keyPrint, color);
	textIcon->Box.x = 200;
	textIcon->Box.y = 75;
	textIcon->AddComponent(inst);
	ObjectArray.emplace_back(textIcon);

	textIcon = new GameObject();
	inst = new Text(textIcon, FONT, 36, Text::TextStyle::SOLID,SDL_GetKeyName(configButtons[1]) + keyPrint, color);
	textIcon->Box.x = 200;
	textIcon->Box.y = 145;
	textIcon->AddComponent(inst);
	ObjectArray.emplace_back(textIcon);

	textIcon = new GameObject();
	inst = new Text(textIcon, FONT, 36, Text::TextStyle::SOLID,SDL_GetKeyName(configButtons[2]) + keyPrint, color);
	textIcon->Box.x = 200;
	textIcon->Box.y = 215;
	textIcon->AddComponent(inst);
	ObjectArray.emplace_back(textIcon);

	textIcon = new GameObject();
	inst = new Text(textIcon, FONT, 36, Text::TextStyle::SOLID,SDL_GetKeyName(configButtons[3]) + keyPrint, color);
	textIcon->Box.x = 200;
	textIcon->Box.y = 285;
	textIcon->AddComponent(inst);
	ObjectArray.emplace_back(textIcon);

	textIcon = new GameObject();
	inst = new Text(textIcon, FONT, 36, Text::TextStyle::SOLID,SDL_GetKeyName(configButtons[4]) + keyPrint, color);
	textIcon->Box.x = 200;
	textIcon->Box.y = 355;
	textIcon->AddComponent(inst);
	ObjectArray.emplace_back(textIcon);

	textIcon = new GameObject();
	inst = new Text(textIcon, FONT, 36, Text::TextStyle::SOLID,SDL_GetKeyName(configButtons[5]) + keyPrint, color);
	textIcon->Box.x = 600;
	textIcon->Box.y = 75;
	textIcon->AddComponent(inst);
	ObjectArray.emplace_back(textIcon);

	textIcon = new GameObject();
	inst = new Text(textIcon, FONT, 36, Text::TextStyle::SOLID,SDL_GetKeyName(configButtons[6]) + keyPrint, color);
	textIcon->Box.x = 600;
	textIcon->Box.y = 145;
	textIcon->AddComponent(inst);
	ObjectArray.emplace_back(textIcon);

	textIcon = new GameObject();
	inst = new Text(textIcon, FONT, 36, Text::TextStyle::SOLID,SDL_GetKeyName(configButtons[7]) + keyPrint, color);
	textIcon->Box.x = 600;
	textIcon->Box.y = 215;
	textIcon->AddComponent(inst);
	ObjectArray.emplace_back(textIcon);

	textIcon = new GameObject();
	inst = new Text(textIcon, FONT, 36, Text::TextStyle::SOLID,SDL_GetKeyName(configButtons[8]) + keyPrint, color);
	textIcon->Box.x = 600;
	textIcon->Box.y = 285;
	textIcon->AddComponent(inst);
	ObjectArray.emplace_back(textIcon);
}

void Options::Update(float dt)
{
	/*if (!backgroundIntroOptions.IsPlaying())
	{
		//SDL_Log("chegou aqui");
		backgroundIntroOptions.Stop(0);
		backgroundLoopOptions.Play(-1);
	}*/

	InputManager& input = InputManager::GetInstance();

	if(input.QuitRequested())
		quitRequested = true;

	if(input.KeyPress(SDLK_LEFT) && !configStart)
		cursorIndexOptions++;

	if(input.KeyPress(SDLK_RIGHT) && !configStart)
		cursorIndexOptions--;

	if(cursorIndexOptions > CURSOR_INDEX_OPTIONS_MAX)
		cursorIndexOptions = 0;

	if(cursorIndexOptions < 0)
		cursorIndexOptions = CURSOR_INDEX_OPTIONS_MAX;

	switch(cursorIndexOptions)
	{
		case 0:
			cursorOptions->Box.x = 700 + (spriteCursorOptions->GetWidth()*1.8);
			cursorOptions->Box.y = 495;
			break;

		case 1:
			cursorOptions->Box.x = 350 + (spriteCursorOptions->GetWidth()*1.8);
			cursorOptions->Box.y = 495;
			break;

		default:
			SDL_Log("Deu merda no cursor");
			break;
	}

	if (input.KeyPress(SDLK_RETURN) && cursorIndexOptions == 0 && !configStart)
	{

		Sound* noise = new Sound(cursorOptions, MAINMENU_CURSOR_SOUND);
		noise->Play(1);
		cursorOptions->AddComponent(noise);

		buttonPressedOptions = new GameObject();
		spriteButtonOptions = new Sprite(buttonPressedOptions, OPTIONS_BACK_BUTTON_PRESSED);
		buttonPressedOptions->Box.x = 700 - (spriteButtonOptions->GetWidth()/2.0);
		buttonPressedOptions->Box.y = 520 - (spriteButtonOptions->GetHeight()/2.0);
		buttonPressedOptions->AddComponent(spriteButtonOptions);
		ObjectArray.emplace_back(buttonPressedOptions);

		Game* game = Game::GetInstance();
		//backgroundLoopOptions.Stop();
		//game->Push(new MainMenu());
		popRequested = true;
	}

	if(configStart)
	{
		switch(indexConfig)
		{
			case 0:
				if(!iconChangeOnScreen)
				{
					iconChange = new GameObject();
					iconChange->Box.x = 800;
					iconChange->Box.y = 350;
					spriteIconChange = new Sprite(iconChange, OPTIONS_UP_ICON);
					iconChange->AddComponent(spriteIconChange);
					ObjectArray.emplace_back(iconChange);
					iconChangeOnScreen = true;
				}

				if(input.GetKeyPressed() == -1){break;}
				configButtons[indexConfig] = input.GetKeyPressed();
				indexConfig++;
				iconChangeOnScreen = false;
				//std::cout << configButtons[0] << std::endl;
				//SDL_Log("Tecla 1");
				break;

			case 1:
				if(!iconChangeOnScreen)
				{
					iconChange = new GameObject();
					iconChange->Box.x = 800;
					iconChange->Box.y = 350;
					spriteIconChange = new Sprite(iconChange, OPTIONS_DOWN_ICON);
					iconChange->AddComponent(spriteIconChange);
					ObjectArray.emplace_back(iconChange);
					iconChangeOnScreen = true;
				}
				if(input.GetKeyPressed() == -1){break;}
				configButtons[indexConfig] = input.GetKeyPressed();
				indexConfig++;
				iconChangeOnScreen = false;
				//std::cout << configButtons[1] << std::endl;
				//SDL_Log("Tecla 2");
				break;

			case 2:
				if(!iconChangeOnScreen)
				{
					iconChange = new GameObject();
					iconChange->Box.x = 800;
					iconChange->Box.y = 350;
					spriteIconChange = new Sprite(iconChange, OPTIONS_LEFT_ICON);
					iconChange->AddComponent(spriteIconChange);
					ObjectArray.emplace_back(iconChange);
					iconChangeOnScreen = true;
				}
				if(input.GetKeyPressed() == -1){break;}
				configButtons[indexConfig] = input.GetKeyPressed();
				indexConfig++;
				iconChangeOnScreen = false;
				//std::cout << configButtons[2] << std::endl;
				//SDL_Log("Tecla 3");
				break;

			case 3:
				if(!iconChangeOnScreen)
				{
					iconChange = new GameObject();
					iconChange->Box.x = 800;
					iconChange->Box.y = 350;
					spriteIconChange = new Sprite(iconChange, OPTIONS_RIGHT_ICON);
					iconChange->AddComponent(spriteIconChange);
					ObjectArray.emplace_back(iconChange);
					iconChangeOnScreen = true;
				}
				if(input.GetKeyPressed() == -1){break;}
				configButtons[indexConfig] = input.GetKeyPressed();
				indexConfig++;
				iconChangeOnScreen = false;
				//std::cout << configButtons[3] << std::endl;
				//SDL_Log("Tecla 4");
				break;

			case 4:
				if(!iconChangeOnScreen)
				{
					iconChange = new GameObject();
					iconChange->Box.x = 800;
					iconChange->Box.y = 350;
					spriteIconChange = new Sprite(iconChange, OPTIONS_PUNCH_ICON);
					iconChange->AddComponent(spriteIconChange);
					ObjectArray.emplace_back(iconChange);
					iconChangeOnScreen = true;
				}
				if(input.GetKeyPressed() == -1){break;}
				configButtons[indexConfig] = input.GetKeyPressed();
				indexConfig++;
				iconChangeOnScreen = false;
				//std::cout << configButtons[4] << std::endl;
				//SDL_Log("Tecla 5");
				break;

			case 5:
				if(!iconChangeOnScreen)
				{
					iconChange = new GameObject();
					iconChange->Box.x = 800;
					iconChange->Box.y = 350;
					spriteIconChange = new Sprite(iconChange, HUD_SHIT_ICON);
					iconChange->AddComponent(spriteIconChange);
					ObjectArray.emplace_back(iconChange);
					iconChangeOnScreen = true;
				}
				if(input.GetKeyPressed() == -1){break;}
				configButtons[indexConfig] = input.GetKeyPressed();
				indexConfig++;
				iconChangeOnScreen = false;
				//std::cout << configButtons[5] << std::endl;
				//SDL_Log("Tecla 6");
				break;

			case 6:
				if(!iconChangeOnScreen)
				{
					iconChange = new GameObject();
					iconChange->Box.x = 800;
					iconChange->Box.y = 350;
					spriteIconChange = new Sprite(iconChange, HUD_DASH_ICON);
					iconChange->AddComponent(spriteIconChange);
					ObjectArray.emplace_back(iconChange);
					iconChangeOnScreen = true;
				}
				if(input.GetKeyPressed() == -1){break;}
				configButtons[indexConfig] = input.GetKeyPressed();
				indexConfig++;
				iconChangeOnScreen = false;
				//std::cout << configButtons[6] << std::endl;
				//SDL_Log("Tecla 7");
				break;

			case 7:
				if(!iconChangeOnScreen)
				{
					iconChange = new GameObject();
					iconChange->Box.x = 800;
					iconChange->Box.y = 350;
					spriteIconChange = new Sprite(iconChange, HUD_FLY_ICON);
					iconChange->AddComponent(spriteIconChange);
					ObjectArray.emplace_back(iconChange);
					iconChangeOnScreen = true;
				}
				if(input.GetKeyPressed() == -1){break;}
				configButtons[indexConfig] = input.GetKeyPressed();
				indexConfig++;
				iconChangeOnScreen = false;
				//std::cout << configButtons[7] << std::endl;
				//SDL_Log("Tecla 8");
				break;

			case 8:
				if(!iconChangeOnScreen)
				{
					iconChange = new GameObject();
					iconChange->Box.x = 800;
					iconChange->Box.y = 350;
					spriteIconChange = new Sprite(iconChange, HUD_ACID_ICON);
					iconChange->AddComponent(spriteIconChange);
					ObjectArray.emplace_back(iconChange);
					iconChangeOnScreen = true;
				}
				if(input.GetKeyPressed() == -1){break;}
				configButtons[indexConfig] = input.GetKeyPressed();
				indexConfig++;
				iconChangeOnScreen = false;
				//std::cout << configButtons[8] << std::endl;
				//SDL_Log("Tecla 9");
				break;

			case 9:

				break;

			default:
				SDL_Log("Deu merda no ConfigControl");
				break;
		}

		if(indexConfig >= 9)
		{
			ofstream myfile;
			myfile.open ("controlsCustom.txt", std::ios::trunc);

			for(int i=0;i<9;++i)
			{
				myfile << configButtons[i] << std::endl;
			}
			myfile.close();
			indexConfig = 0;

			configStart = false;
			Game* game = Game::GetInstance();
			//backgroundLoopOptions.Stop();
			//game->Push(new MainMenu());
			popRequested = true;
		}
	}

	if (input.KeyPress(SDLK_RETURN) && cursorIndexOptions == 1 && !configStart)
	{
		Sound* noise = new Sound(cursorOptions, MAINMENU_CURSOR_SOUND);
		noise->Play(1);
		cursorOptions->AddComponent(noise);

		buttonPressedOptions = new GameObject();
		spriteButtonOptions = new Sprite(buttonPressedOptions, OPTIONS_CHANGE_BUTTON_PRESSED);
		buttonPressedOptions->Box.x = 350 - (spriteButtonOptions->GetWidth()/2.0);
		buttonPressedOptions->Box.y = 520 - (spriteButtonOptions->GetHeight()/2.0);
		buttonPressedOptions->AddComponent(spriteButtonOptions);
		ObjectArray.emplace_back(buttonPressedOptions);

		GameObject* textChangeControls = new GameObject();
		SDL_Color color = {0,0,0,0};
		Text* insta = new Text(textChangeControls, FONT, 36, Text::TextStyle::SOLID,"Press the key you want for this icon: ", color);
		textChangeControls->Box.x = 370;
		textChangeControls->Box.y = 355;
		textChangeControls->AddComponent(insta);
		ObjectArray.emplace_back(textChangeControls);

		configStart = true;
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
