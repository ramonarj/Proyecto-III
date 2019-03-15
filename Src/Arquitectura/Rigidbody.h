#pragma once
#include "Component.h""
#include <iostream>
#include "physicSystem.h"
#include <OgreSceneNode.h>

class Rigidbody : public Component
{
public:
	//Especifica el nodo (masa = 0 significa que el rigidbody es est�tico)
	Rigidbody(Ogre::SceneNode* node, Shape shape, btScalar dimensions, btScalar mass = 1);
	//Rigidbody invisible (se especifica la posici�n)
	Rigidbody(Ogre::Vector3 position, Shape shape, btScalar dimensions, btScalar mass = 1);

	~Rigidbody();

	virtual void render(unsigned int time) {};
	virtual void update(unsigned int time);
	virtual bool handleEvent(SDL_Event* e, unsigned int time);
	virtual void receive(Message* msg) {};

	virtual bool hasNode() { return (rigid_->getUserPointer() != nullptr); };
	virtual void* getNode() { return rigid_->getUserPointer(); };
	virtual void getTransform(btTransform* trans) { return rigid_->getMotionState()->getWorldTransform(*trans); };

protected:
	btRigidBody* rigid_;

};

