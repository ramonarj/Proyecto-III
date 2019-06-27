#include "SceneManager.h"
#include "ResourceManager.h"
#include "HUDManager.h"

std::unique_ptr<SceneManager> SceneManager::instance_;


void SceneManager::initInstance(bool* ex)
{
	if (instance_.get() == nullptr)
		instance_.reset(new SceneManager(ex));
}

SceneManager* SceneManager::instance()
{
	assert(instance_.get() != nullptr);
	return instance_.get();
}

SceneManager::SceneManager(bool* ex)
{
	exit = ex;
}


void SceneManager::disableOtherStatesNodes()
{
	for (auto s = states.begin(); s != states.end(); s++) {
		(*s).second->getStateNode()->setVisible((*s).second == currentState_);
	}
}

SceneManager::~SceneManager()
{
	auto it = states.begin();
	while (it != states.end())
	{
		delete (*it).second;
		(*it).second = nullptr;
		++it;
	}
	
	//it = states.erase(it);
		
	states.clear();
	instance_.release();
}
			

GameState* SceneManager::currentState()
{
	return currentState_;
}

void SceneManager::resetBuildStatePointer() {
	//BuildingState es un puntero auxiliar para que
	//los componentes se cargen sobre el nuevo estado
	//Que esta generando el EntityFactory
	//Tenemos que reiniciarlo cuando acabe de crearse el nuevo estado
	if (buildingState_ != nullptr) {
		//IMPORTANTE! No borramos lo apuntado por el puntero (delete)
		//Eso borrar�a la informaci�n que se guarda en la variable
		//local STATE de SceneManager::addState()
		buildingState_ = nullptr;
	}
}

void SceneManager::buildingStateType(GameState* state)
{
	//Apunta al estado que esta generandose y al EntityFactory que lo rellena.
	buildingState_ = state;
}

GameState* SceneManager::buildingState()
{
	return buildingState_;
}

GameState* SceneManager::addState(std::string stateID)
{
	//State es una variable local de este m�todo, para hacerlo accesible desde fuera
	//tenemos un puntero no local apuntara a cada nuevo state que deseemos crear
	//se inicializar� en la constructora de GameState y liberar� al final del addState
	GameState* state = nullptr;

	//Solo lo a�adimos si no est� ya
	auto it = states.find(stateID);
	if(it == states.end())
	{
		//Primero a�adimos una ventana y creamos el estado
		HUDManager::instance()->addWindow(stateID);
		HUDManager::instance()->changeWindow(stateID);
		//Importante: Al crear un nuevo estado su constructora
		//inicializara la variable buildingState_ del SceneManager.
		state = new GameState(stateID);

		//A�adimos el estado a nuestro mapa de estados
		states.insert(std::pair<std::string, GameState*>(stateID, state));

		//Volvemos a la ventana en la que est�bamos
		if(currentState_ != nullptr)
			HUDManager::instance()->changeWindow(currentState_->getID());
	}

	//Limpiamos informaci�n del puntero auxiliar una vez creado
	//el estado y cargado sobre el los componentes
	resetBuildStatePointer();

	//devolvemos el nuevo estado creado
	return state;
}

void SceneManager::changeState(std::string stateID)
{
	HUDManager::instance()->changeWindow(stateID);

	auto it = states.find(stateID);
	assert(it != states.end());
	currentState_ = it->second;
	currentState_->start();

	disableOtherStatesNodes();
}

bool SceneManager::removeState(std::string stateID) {
	//Generamos un iterador para que busque el estado deseado
	auto it = states.find(stateID);

	//Si no lo ha encontrado (Posici�n final)
	if (it == states.end())
		return false;
	else {
		delete it->second;
		states.erase(it);
		return true;
	}

}
