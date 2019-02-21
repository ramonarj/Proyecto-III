#pragma once

//No hacer #include "Entity.h" para evitar inclusi�n circular
class Entity;

/*
Clase Componente:
-> Define un comportamiento espec�fico.
-> Contiene m�todos para pintarse, gestionar eventos y actualizar l�gica.
-> Tiene un flag de actividad y un puntero a la entidad a la que est� asociado.
* Esta clase padre es abstracta, ya que no define ning�n comportamiento.
*/
class Component
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

	//Destructora
	virtual ~Component();
private:
	//Flag de actividad
	bool active_;
	//Puntero a la entidad
	Entity* entity_;
};


