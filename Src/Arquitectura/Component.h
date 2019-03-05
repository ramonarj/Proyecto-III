#pragma once
#include "Messages.h"

using namespace Architecture;

//No hacer #include "Entity.h" para evitar inclusi�n circular
class Entity;

enum  Name{NPC,GraphicComponent,LogicComponent,InputComponent,Building,PhysicsComponent, CameraComp, RigidComp}; //Algunos ejemplos de nombres
//Cada vez que se cree un Componente , se tiene que a�adir a la lista de nombres.

/*
Clase Componente:
-> Define un comportamiento espec�fico.
-> Contiene m�todos para pintarse, gestionar eventos y actualizar l�gica.
-> Tiene un flag de actividad y un puntero a la entidad a la que est� asociado.
-> Hereda de Listener y Emitter para que as� los componentes hijos puedan redefinirlos
* Esta clase padre es abstracta, ya que no define ning�n comportamiento.
*/
class Component:public Listener, public Emitter
{
public:
	//Constructora por defecto
	Component();

	//M�todos principales (renderizado, l�gica y eventos)
	virtual void render(unsigned int time) = 0;
	virtual void update(unsigned int time) = 0;
	virtual void handleEvent() = 0;

	//Getters y setters del flag de actividad
	bool isActive() { return active_; };
	void setActive(bool b) { active_ = b; };

	//Getters y setters de la entidad
	void setEntity(Entity* ent) { entity_ = ent; };
	Entity* getEntity() { return entity_; }
	
	Name getName() { return name_; }

	//Destructora
	virtual ~Component();

	
protected:
	//Flag de actividad
	bool active_;
	//Puntero a la entidad
	Entity* entity_;
	//TODO: Los componentes tendr�n un string con su nombre para poder identificarlos
	Name name_; //Nombre del componente para poder acceder a componenetes hermanos de la entidad	
};


