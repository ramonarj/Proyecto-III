#pragma once
#include "Messages.h"
#include "ComponentCreator.h"
#include <jsonParser.hpp>
#include <OgreVector3.h>

using namespace Architecture;

//enum  Name{ TransformComp, MeshRendererComp, RigidbodyComp, CameraComp, TerrainComp  }; 
//Cada vez que se cree un Componente , se tiene que a�adir a la lista de nombres.

/*
Clase Componente:
-> Define un comportamiento espec�fico.
-> Contiene m�todos para pintarse, gestionar eventos y actualizar l�gica.
-> Tiene un flag de actividad y un puntero a la entidad a la que est� asociado.
-> Hereda de Listener y Emitter para que as� los componentes hijos puedan redefinirlos
* Esta clase padre es abstracta, ya que no define ning�n comportamiento.
*/

class Entity;
using json = nlohmann::json;

class Component:public Listener, public Emitter
{
public:
	//Constructora por defecto
	Component();

	virtual void load(json file) {};

	//M�todo para que los componentes e inicialicen con informaci�n de sus componentes hermanos
	virtual void start() {};

	//M�todos principales (renderizado, l�gica y eventos)
	virtual void render(unsigned int time) {};
	virtual void update(unsigned int time) {};
	virtual bool handleEvent(unsigned int time) { return false; };

	//Getters y setters del flag de actividad
	bool isActive() { return active_; };
	void setActive(bool b) { active_ = b; };

	//Getters y setters de la entidad
	void setEntity(Entity* ent) { entity_ = ent; };
	Entity* getEntity() { return entity_; }
	void releaseEntity();
	
	//Destructora
	virtual ~Component();

	
protected:
	//Flag de actividad
	bool active_;
	//Puntero a la entidad
	Entity* entity_;
};


