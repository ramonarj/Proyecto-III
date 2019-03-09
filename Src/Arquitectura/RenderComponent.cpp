#include "RenderComponent.h"



RenderComponent::RenderComponent(Ogre::SceneNode* node): node_(node)
{
	//TODO: que el tama�o del COllider se ajuste al tama�o de la malla de la entidad que tiene el nodo
	//Nombre del componente
	name_ = Name::RenderComp;

}


RenderComponent::~RenderComponent()
{
}

void RenderComponent::update(unsigned int time)
{

}

bool RenderComponent::handleEvent(SDL_Event* e, unsigned int time)
{
	if (e->type == SDL_KEYDOWN)
	{
		//El control 0 estar parado, el 1 izda, el 2 dcha, el 3 arriba y el 4 abajo
		if (e->key.keysym.sym == SDLK_SPACE)
		{
			//foo
		}
	}
	return false;
}
