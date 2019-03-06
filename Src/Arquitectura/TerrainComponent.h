#include "Component.h"
#include <GestorRecursos/gestorDeRecursos.h>
#include <iostream>

class TerrainComponent : public Component
{
public:
	TerrainComponent(Ogre::SceneManager* scnMgn, Ogre::Light* light, std::string terrainFile);
	~TerrainComponent();

	virtual void render(unsigned int time) {};
	virtual void update(unsigned int time) {};
	virtual void handleEvent(SDL_Event* e) {};
	virtual void receive(Message* msg) {};

	TerrainCreator* terrainCreator_;
};