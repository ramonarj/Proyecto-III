#pragma once

#include <map>
#include <vector>
#include <memory>

class GameState;
class Entity;
class Component;

class BaseCreator
{
public:
	virtual Component* createComponent() const = 0;
};


class EntityFactory
{
private:
	EntityFactory();
	static std::unique_ptr<EntityFactory> instance_;

	static std::map<std::string, BaseCreator*>& creators(); // Diccionario de las factor�as de componentes

	// �> Crea un componente seg�n su nombre
	Component* createComponent(std::string name);

	GameState* currentlyCreatingState = nullptr;
	
public:
	// �> Devuelve un puntero a la factor�a, o la crea si no lo estaba ya
	static EntityFactory* Instance();
	~EntityFactory();

	// �> Registra una factor�a de componentes en el diccionario
	static void registerType(std::string creatorName, BaseCreator* pCreator);

	// �> Crea las entidades de una escena leyendo de su archivo json correspondiente
	std::vector<Entity*> createEntities(GameState* currState);

	// �> Crea una entidad con los componentes correspondientes de su prefab
	Entity* createEntityFromBlueprint(std::string name);

	GameState* get_currentState();
};