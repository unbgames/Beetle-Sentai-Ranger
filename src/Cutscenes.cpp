#include "Cutscenes.h"
#include "Stage1.h"

Cutscenes::Cutscenes()
{
	quitRequested = false;
	popRequested = false;
}

Cutscenes::~Cutscenes()
{
	//cutsceneMusic.Stop();
	ObjectArray.clear();
}

void Cutscenes::PrintScene()
{
	switch(cutsceneIndex)
	{
		case 0:
			SDL_Log("cutsceneIndex = 0");
			break;

		case 1:
			SDL_Log("cutsceneIndex = 1");

			cutsceneMusic.Stop(0);
			cutsceneMusic.Open(CUTSCENES_MUSIC_2);
			cutsceneMusic.Play(1);

			cutscene = new GameObject();
			cutscene->Box.x = 0;
			cutscene->Box.y = 0;
			spriteCutscene = new Sprite(cutscene, CUTSCENES_2);
			cutscene->AddComponent(spriteCutscene);
			ObjectArray.emplace_back(cutscene);

			cutscenePanel = new GameObject();
			cutscenePanel->Box.x = 12;
			cutscenePanel->Box.y = 5;
			spriteCutscenePanel = new Sprite(cutscenePanel, CUTSCENES_PANEL);
			cutscenePanel->AddComponent(spriteCutscenePanel);
			ObjectArray.emplace_back(cutscenePanel);

			cutsceneDialog = new GameObject();
			textCutsceneDialog = new Text(cutsceneDialog, FONT, 36, Text::TextStyle::SOLID,"However, during the mating season, the village was attacked by the Great Frog!", color);
			cutsceneDialog->Box.x = 50;
			cutsceneDialog->Box.y = 30;
			cutsceneDialog->AddComponent(textCutsceneDialog);
			ObjectArray.emplace_back(cutsceneDialog);

			cutsceneDialog = new GameObject();
			textCutsceneDialog = new Text(cutsceneDialog, FONT, 36, Text::TextStyle::SOLID,"Putting fire on every house, his minions quickly got their eggs.", color);
			cutsceneDialog->Box.x = 50;
			cutsceneDialog->Box.y = 60;
			cutsceneDialog->AddComponent(textCutsceneDialog);
			ObjectArray.emplace_back(cutsceneDialog);

			/*
			However, during the mating season, the village was attacked by the Great Frog!
			Putting fire on every house, his minions quickly got their eggs.
			*/
			break;

		case 2:
			SDL_Log("cutsceneIndex = 2");

			cutsceneMusic.Stop(0);
			cutsceneMusic.Open(CUTSCENES_MUSIC_3);
			cutsceneMusic.Play(1);

			cutscene = new GameObject();
			cutscene->Box.x = 0;
			cutscene->Box.y = 0;
			spriteCutscene = new Sprite(cutscene, CUTSCENES_3);
			cutscene->AddComponent(spriteCutscene);
			ObjectArray.emplace_back(cutscene);

			cutscenePanel = new GameObject();
			cutscenePanel->Box.x = 12;
			cutscenePanel->Box.y = 451;
			spriteCutscenePanel = new Sprite(cutscenePanel, CUTSCENES_PANEL);
			cutscenePanel->AddComponent(spriteCutscenePanel);
			ObjectArray.emplace_back(cutscenePanel);

			cutsceneDialog = new GameObject();
			textCutsceneDialog = new Text(cutsceneDialog, FONT, 36, Text::TextStyle::SOLID,"This is what you deserve, you little insects! Your eggs are mine now!", color);
			cutsceneDialog->Box.x = 50;
			cutsceneDialog->Box.y = 30 + 450;
			cutsceneDialog->AddComponent(textCutsceneDialog);
			ObjectArray.emplace_back(cutsceneDialog);

			cutsceneDialog = new GameObject();
			textCutsceneDialog = new Text(cutsceneDialog, FONT, 36, Text::TextStyle::SOLID,"I am gonna eat them all! Mwahahahahahahahahahahahaha!", color);
			cutsceneDialog->Box.x = 50;
			cutsceneDialog->Box.y = 60 + 450;
			cutsceneDialog->AddComponent(textCutsceneDialog);
			ObjectArray.emplace_back(cutsceneDialog);

			/*
			“This is what you deserve, you little insects! Your eggs are mine now!
			I’m gonna eat them all! Mwahahahahahahahahahahahaha!”
			*/

			break;

		case 3:
			SDL_Log("cutsceneIndex = 3");

			cutsceneMusic.Stop(0);
			cutsceneMusic.Open(CUTSCENES_MUSIC_4);
			cutsceneMusic.Play(1);

			cutscene = new GameObject();
			cutscene->Box.x = 0;
			cutscene->Box.y = 0;
			spriteCutscene = new Sprite(cutscene, MAINMENU_BACKGROUND);
			cutscene->AddComponent(spriteCutscene);
			ObjectArray.emplace_back(cutscene);

			cutscenePanel = new GameObject();
			cutscenePanel->Box.x = 12;
			cutscenePanel->Box.y = 451;
			spriteCutscenePanel = new Sprite(cutscenePanel, CUTSCENES_PANEL);
			cutscenePanel->AddComponent(spriteCutscenePanel);
			ObjectArray.emplace_back(cutscenePanel);

			cutsceneDialog = new GameObject();
			textCutsceneDialog = new Text(cutsceneDialog, FONT, 36, Text::TextStyle::SOLID,"I will not let you get away with this!", color);
			cutsceneDialog->Box.x = 50;
			cutsceneDialog->Box.y = 30 + 450;
			cutsceneDialog->AddComponent(textCutsceneDialog);
			ObjectArray.emplace_back(cutsceneDialog);

			cutsceneDialog = new GameObject();
			textCutsceneDialog = new Text(cutsceneDialog, FONT, 36, Text::TextStyle::SOLID,"You are going to pay, you monster! Time to make use of my powers!", color);
			cutsceneDialog->Box.x = 50;
			cutsceneDialog->Box.y = 60 + 450;
			cutsceneDialog->AddComponent(textCutsceneDialog);
			ObjectArray.emplace_back(cutsceneDialog);

			/*
			I will not let you get away with this!
			You are going to pay, you monster! Time to make use of my powers!
			*/

			break;

		case 4:
			SDL_Log("cutsceneIndex = 4");
			break;

		default:
			SDL_Log("Deu merda no cutsceneIndex");
			break;
	}
}

void Cutscenes::LoadAssets()
{
	cutsceneMusic.Open(CUTSCENES_MUSIC_1);
	cutsceneMusic.Play(1);

	cutscene = new GameObject();
	cutscene->Box.x = 0;
	cutscene->Box.y = 0;
	spriteCutscene = new Sprite(cutscene, CUTSCENES_1);
	cutscene->AddComponent(spriteCutscene);
	ObjectArray.emplace_back(cutscene);

	cutscenePanel = new GameObject();
	cutscenePanel->Box.x = 12;
	cutscenePanel->Box.y = 5;
	spriteCutscenePanel = new Sprite(cutscenePanel, CUTSCENES_PANEL);
	cutscenePanel->AddComponent(spriteCutscenePanel);
	ObjectArray.emplace_back(cutscenePanel);

	cutsceneDialog = new GameObject();
	textCutsceneDialog = new Text(cutsceneDialog, FONT, 36, Text::TextStyle::SOLID,"Once upon a time, there was a small village, full of beetles. They lived peacefully,", color);
	cutsceneDialog->Box.x = 50;
	cutsceneDialog->Box.y = 30;
	cutsceneDialog->AddComponent(textCutsceneDialog);
	ObjectArray.emplace_back(cutsceneDialog);

	cutsceneDialog = new GameObject();
	textCutsceneDialog = new Text(cutsceneDialog, FONT, 36, Text::TextStyle::SOLID,"eating and drinking whatever they could find in the forest nearby.", color);
	cutsceneDialog->Box.x = 50;
	cutsceneDialog->Box.y = 60;
	cutsceneDialog->AddComponent(textCutsceneDialog);
	ObjectArray.emplace_back(cutsceneDialog);

	/*
	Once upon a time, there was a small village, full of beetles.
	They lived peacefully, eating and drinking whatever they could find in the forest nearby.
	*/
}

void Cutscenes::Update(float dt)
{
	InputManager& input = InputManager::GetInstance();

	if(input.QuitRequested())
		quitRequested = true;

	if(cutsceneIndex >= 4 || input.KeyPress(SDLK_SPACE))
	{
		cutsceneIndex = 0;
		Game* game = Game::GetInstance();
		cutsceneMusic.Stop();
		game->Push(new Stage1(4));
		popRequested = true;
	}

	if (input.KeyPress(SDLK_RETURN) || !cutsceneMusic.IsPlaying())
	{
		cutsceneIndex++;
		PrintScene();
	}

	Camera::Update(dt);

	UpdateArray(dt);
}

void Cutscenes::Render()
{
	RenderArray();
}

void Cutscenes::Start()
{
	Camera::Unfollow();
	Camera::pos.x = 0;
	Camera::pos.y = 0;
	LoadAssets();
	StartArray();
}

void Cutscenes::Pause(){}
void Cutscenes::Resume(){}
