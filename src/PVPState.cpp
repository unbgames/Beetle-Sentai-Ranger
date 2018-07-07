#include "PVPState.h"

PVPState::PVPState(){
    quitRequested = false;
    popRequested = false;

    backgroundIntro.Open(STAGE1_BACKGROUNDMUSIC_INTRO);
    backgroundLoop.Open(STAGE1_BACKGROUNDMUSIC_LOOP);
    backgroundIntro.Play(1);
}
PVPState::~PVPState(){
    //if (backgroundLoop.IsOpen())
        //backgroundLoop.Stop();
    ObjectArray.clear();
}

void PVPState::LoadAssets(){
    GameObject* backobj2 = new GameObject();

    backobj2->Box.x = 0;
    backobj2->Box.y = 0;

    Sprite* bg2 = new Sprite(backobj2, STAGE1_BOSS_BACKGROUND);

    backobj2->AddComponent(bg2);

    ObjectArray.emplace_back(backobj2);

    limit = Rect(0, 0, bg2->GetWidth(), bg2->GetHeight());

    GameObject* aux2 = new GameObject();
    aux2->Box.x = 200;
    aux2->Box.y = 500;
    Player1* jogador1 = new Player1(aux2);
    //aux2->AddComponent(ranger);
    ObjectArray.emplace_back(aux2);

    GameObject* aux3 = new GameObject();
    aux3->Box.x = 800;
    aux3->Box.y = 500;
    Player2* jogador2 = new Player2(aux3);
    //aux2->AddComponent(ranger);
    ObjectArray.emplace_back(aux3);
}
void PVPState::Update(float dt){

    if (!backgroundIntro.IsPlaying()){
        backgroundIntro.Stop(0);
        backgroundLoop.Play(-1);
    }

    InputManager& input = InputManager::GetInstance();

    if(input.QuitRequested())
        quitRequested = true;

    if (input.KeyPress(SDLK_ESCAPE)){
        Game* game = Game::GetInstance();
        backgroundLoop.Stop();
        game->Push(new MainMenu());
        popRequested = true;
    }

    Camera::Update(dt);

    UpdateArray(dt);

    for(int i = 0; i < ObjectArray.size(); i++){
        Collider* colisorI = (Collider*) ObjectArray[i]->GetComponent("Collider");

        for (int j=i+1; j < ObjectArray.size(); j++){
            Collider* colisorJ = (Collider*) ObjectArray[j]->GetComponent("Collider");

            if ((i != j) && (colisorI != nullptr) && (colisorJ != nullptr)){
                if(Collision::IsColliding(colisorI->Box, colisorJ->Box , ObjectArray[i]->angleDeg*(PI/180.0), ObjectArray[j]->angleDeg*(PI/180.0))){


                    ObjectArray[i]->NotifyCollision(ObjectArray[j].get());
                    ObjectArray[j]->NotifyCollision(ObjectArray[i].get());
                }
            }
        }
    }

    //SDL_Log("obj: %d", ObjectArray.size());
    //SDL_Log("enemy: %d", GroundEnemy::nEnemy);
}
void PVPState::Render(){
    RenderArray();
}

void PVPState::Start(){
    LoadAssets();
    StartArray();
}
void PVPState::Pause(){}
void PVPState::Resume(){}