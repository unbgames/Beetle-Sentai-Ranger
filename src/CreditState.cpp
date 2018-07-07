#include "CreditState.h"

CreditState::CreditState(string File) : State(){
	file.open(File);
	if (!file.is_open()){
		SDL_Log("falha ao abrir o arquivo de texto");
	}
	wait.Restart();
	wait.Update(2.0);

	GameObject* go = new GameObject();

	Sprite* img = new Sprite(go, CREDIT_SCENE);
	go->AddComponent(img);

	go->Box.x = 0;
	go->Box.y = 0;
	go->Box.w = img->GetWidth();
	go->Box.h = img->GetHeight();

	ObjectArray.emplace_back(go);
	SceneTimer.Restart();


	backgroundMusic.Open(CREDIT_MUSIC);
	backgroundMusic.Play(-1);
}
CreditState::~CreditState(){
	backgroundMusic.Stop();
	ObjectArray.clear();
	file.close();
}

void CreditState::LoadAssets(){}
void CreditState::Update(float dt){

	InputManager& input = InputManager::GetInstance();

	if(input.QuitRequested()){
		quitRequested = true;
	}

	if (input.KeyPress(SDLK_SPACE) || input.KeyPress(SDLK_ESCAPE)){
		popRequested = true;
	}

	if (SceneTimer.Get() < 4){
		SceneTimer.Update(dt);
		return;
	}

	string linha = " ";
	wait.Update(dt);

	if (wait.Get() >= 2.0){
		if(getline(file,linha)){/*Problema com linhas vazias*/
			wait.Restart();

			char type = linha.back();
			if (type == ':'){
				linha.pop_back();
				AddText(linha);
			}
			else if(type == '#'){
				linha.pop_back();
				AddImage(linha);
			}

		}
	}



	for (int i = 0; i < ObjectArray.size(); ++i){
		ObjectArray[i]->Box.y -= 50*dt;
		if ((ObjectArray[i]->Box.y+ObjectArray[i]->Box.h) < -100){
			ObjectArray[i]->RequestDelete();
		}
	}

	if (ObjectArray.size() == 0){
		popRequested = true;
	}

	UpdateArray(dt);
	//SDL_Log("obj: %d", ObjectArray.size());
}
void CreditState::Render(){
	SDL_SetRenderDrawColor(Game::GetInstance()->GetRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(Game::GetInstance()->GetRenderer());
	RenderArray();
}

void CreditState::Start(){
}
void CreditState::Pause(){}
void CreditState::Resume(){
	Camera::pos.x = 0;
	Camera::pos.y = 0;
}


void CreditState::AddText(string text){
	GameObject* go = new GameObject();

	SDL_Color color = {255,255,255,0};
	Text* inst = new Text(go, FONT, 42, Text::TextStyle::SOLID,text, color);
	go->AddComponent(inst);

	go->Box.Centralize(512,300);
	go->Box.y = 800;

	ObjectArray.emplace_back(go);
	
}
void CreditState::AddImage(string file){
	GameObject* go = new GameObject();

	Sprite* img = new Sprite(go, file);
	go->AddComponent(img);

	go->Box.w = img->GetWidth();
	go->Box.h = img->GetHeight();

	go->Box.Centralize(512,300);
	go->Box.y = 800;

	ObjectArray.emplace_back(go);
}