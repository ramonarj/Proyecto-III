#include "GameState.h"
#include <iostream>


GameState::GameState()
{
}

void GameState::start()
{
}

GameState::~GameState()
{
	for (Component* c : scene) 
		delete c;
}


void GameState::update(unsigned int time)
{
	physicSystem::instance()->stepSimulation(time); //F�SICA

	for (Component* c : scene)
		if(c->isActive())
			c->update(time); 
}

void GameState::render(unsigned int time)
{
	for (Component* c : scene)
		if (c->isActive())
			c->render(time);
}

void GameState::handleInput(unsigned int time)
{
	bool handled = false;
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			//EXIT = true;
		}
		//LLama al handleInput de todos los componentes 
		else 
		{
			std::vector<Component*>::iterator it = scene.begin();
			while (it != scene.end() && !handled)
			{
				if ((*it)->isActive())
					handled = (*it)->handleEvent(&event, time);
				it++;
			}
		}
	}
}

void GameState::addEntity(Entity* e)
{
	for (Component* c : e->getComponents()) 
		scene.push_back(c);
}

bool GameState::removeEntity(std::string name)
{
	bool found = false;

	std::vector<Component*>::iterator it = scene.begin();
	//Eliminamos todos los componentes con esa entidad
	while (it != scene.end())
	{
		if ((*it)->getEntity()->getName() == name)
		{
			it = scene.erase(it);
			found = true;
		}
			
		else
			it++;
	}
	return found;
}

Entity* GameState::getEntity(std::string name)
{
	Entity* e = nullptr;
	std::vector<Component*>::iterator it = scene.begin();
	//Buscamos al primer componente que tenga esa entidad
	while (it != scene.end() && e == nullptr)
	{
		if ((*it)->getEntity()->getName() == name)
			e = (*it)->getEntity();
		it++;
	}

	return e;
}