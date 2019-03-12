#pragma once
#include <Scenes/SceneManager.h> //Esto tiene que ir lo primero porque tiene physicSystem
#include "initOgreApplication.h"
#include <OgreStringVector.h>
#include <Arquitectura/Entity.h>
#include <string>
#include <SDL.h>
#include <SDL_video.h>
#include <AudioSource/AudioSource.h>


class Game {
public:
	Game(std::string basicConfig);
	~Game();

	void start();
	void run();
private:
	SceneManager* ScnMng_;
	Ogre::Root* root;
	initOgreApplication* Ogreinit_; //Informaci�n inicial de Ogre
	AudioSource* audioSrc_;

	unsigned long hWnd; //Variable que toma la ventana de Ogre para aplicarla a la de SDL
	bool exit;
};