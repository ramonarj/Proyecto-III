#include "SceneManager.h"


PlayState::PlayState() : GameState()
{
	start();
}

PlayState::~PlayState()
{
}


void PlayState::start()
{
	// Inicializar componentes de la propia escena, as� como crear las escenas accesibles desde la misma (comprobar antes si est� ya creada)
}


void PlayState::update(unsigned int time)
{
	GameState::update(time);
}

void PlayState::render(unsigned int time)
{
	GameState::render(time);
}

void PlayState::handleInput()
{
	GameState::handleInput();
}