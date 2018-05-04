#include "State.h"

State::State(){
	bool popRequested = false;
	bool quitRequested = false;
	bool started = false;
}
State::~State(){
	ObjectArray.clear();
}

void State::LoadAssets(){}
void State::Update(float dt){}
void State::Render(){}

void State::Start(){}
void State::Pause(){}
void State::Resume(){}

weak_ptr<GameObject> State::AddObject(GameObject* object){

	shared_ptr<GameObject> aux(object);

	ObjectArray.push_back(aux);

	if (started){
		object->Start();
	}

	weak_ptr<GameObject> ret(aux);

	return(ret);
}
weak_ptr<GameObject> State::GetObjectPtr(GameObject* object){

	weak_ptr<GameObject> ret;

	for (int i = 0; i < ObjectArray.size(); ++i){
		if(ObjectArray[i].get() == object)
			ret = ObjectArray[i];
	}
	return(ret);
}

bool State::PopRequested(){
	return(popRequested);
}
bool State::QuitRequested(){
	return(quitRequested);
}

void State::StartArray(){
	
	for (int i = 0; i < ObjectArray.size(); ++i){
		ObjectArray[i]->Start();
	}
	started = true;
}
void State::UpdateArray(float dt){
	for (int i = 0; i < ObjectArray.size(); ++i){
		ObjectArray[i]->Update(dt);
	}
	for (int i = 0; i < ObjectArray.size(); ++i){
		if(ObjectArray[i]->IsDead()){
			ObjectArray.erase(ObjectArray.begin()+i);
		}
	}
}
void State::RenderArray(){
	for (int i = 0; i < ObjectArray.size(); ++i){
		ObjectArray[i]->Render();
	}
}