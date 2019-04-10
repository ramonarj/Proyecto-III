#include "Component.h"
#include "ResourceManager.h"
#include "Entity.h"

Component::Component() : active_(true), entity_(nullptr)
{
}

void Component::start()
{
	//Registramos a nuestros compa�eros
	for (Component* c : entity_->getComponents())
		if (c != this)
			registerListener(c);
}


void Component::releaseEntity()
{
	delete entity_;  
	entity_ = nullptr;
}


Component::~Component()
{
}
