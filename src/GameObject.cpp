#include "GameObject.h"

GameObject::GameObject(){
	isDead = false;
}

GameObject::~GameObject(){
	for (int i = components.size()-1; i >= 0; i--){
		delete components[i];
	}
	components.clear();
}

void GameObject::Start(){
	for (int i = 0; i < components.size(); ++i){
		components[i]->Start();
	}
	started = true;
}

void GameObject::Update(float dt){
	for (int i = 0; i < components.size(); ++i){
		components[i]->Update(dt);
	}
}

void GameObject::Render(){
	for (int i = 0; i < components.size(); ++i){
		components[i]->Render();
	}
}

void GameObject::NotifyCollision(GameObject* other){
	for (int i = 0; i < components.size(); ++i){
		components[i]->NotifyCollision(other);
	}
}

bool GameObject::IsDead(){
	return(isDead);
}

void GameObject::RequestDelete(){
	isDead = true;
}

void GameObject::AddComponent(Component* cpt){
	components.push_back(cpt);
	if (started){
		cpt->Start();
	}
}

void GameObject::RemoveComponent(Component* cpt){
	for (int i = 0; i < components.size(); ++i){
		if(components[i] == cpt)
			components.erase(components.begin()+i-1);
	}
}

Component* GameObject::GetComponent(string type){
	for (int i = 0; i < components.size(); ++i){
		if(components[i]->Is(type))
			return(components[i]);
	}
	return(nullptr);
}