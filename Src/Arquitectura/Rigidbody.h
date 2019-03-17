#pragma once
#include "Component.h""
#include <iostream>
#include "physicSystem.h"
#include <OgreSceneNode.h>
#include "Transform.h"

class Rigidbody : public Component
{
public:
	Rigidbody();

	//Especifica el nodo (masa = 0 significa que el rigidbody es est�tico)
	Rigidbody(Shape shape, btScalar dimensions, btScalar mass = 1);

	~Rigidbody();

	//Generic methods
	virtual void render(unsigned int time) {};
	virtual void update(unsigned int time);
	virtual bool handleEvent(SDL_Event* e, unsigned int time);
	virtual void receive(Message* msg) {};

	//Add a force to the rigidBody
	virtual void addForce(btVector3 force) { rigid_->applyCentralImpulse(force); };

protected:
	btRigidBody* rigid_;
	Transform* transform_;
};

