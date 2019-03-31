#pragma once
#include "Component.h"
#include <OISKeyboard.h>
#include <OISMouse.h>

class Transform;
class Ogre::Camera;
class Ogre::Viewport;
class Ogre::SceneNode;

class Camera : public Component
{
public:
	Camera();
	~Camera();

	virtual void start();

	virtual void render(unsigned int time) {};
	virtual void update(unsigned int time);
	virtual bool handleEvent(unsigned int time);
	virtual void receive(Message* msg) {};

	Ogre::SceneNode* getCameraNode() { return camNode_; }
	Ogre::Camera* getCamera() { return camera_; }
	Ogre::Viewport* getViewport() { return viewport_; }

	Ogre::SceneNode* camNode_;
	Ogre::Camera *camera_;
	Ogre::Viewport *viewport_;

	Transform* transform_;
};

REGISTER_TYPE(Camera)