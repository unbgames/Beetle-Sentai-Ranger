#include "Component.h"

Component::Component(GameObject* associated){

	this->associated = associated;
}
Component::~Component(){}
void Component::Start(){}
void Component::Update(float dt){}
void Component::Render(){}
bool Component::Is(string type){}
void Component::NotifyCollision(GameObject* other){}
GameObject* Component::GetAssociated(){
	return(associated);
}

bool Component::IsEnabled(){
	return(enabled);
}
void Component::SetEnabled(bool enable){
	enabled = enable;
}
string Component::GetTag(){
	return(tag);
}
void Component::SetTag(string tag){
	this->tag = tag;
}