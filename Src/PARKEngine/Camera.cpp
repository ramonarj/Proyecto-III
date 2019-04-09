#include "Camera.h"
#include "Entity.h"
#include "Transform.h"
#include <SDL_video.h>

#include "ResourceManager.h"
#include "InputManager.h"

#include "OgreIncludes.h"
#include "OgreManager.h"

#include <CEGUI/CEGUI.h>


Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::start()
{
	//Camera already created
	if (OgreManager::instance()->getCamera() != nullptr)
		camera_ = OgreManager::instance()->getCamera();
	//Create a new one
	else
		camera_ = OgreManager::instance()->createCamera("Camera", 5, 50000, true);


	camNode_ = (Ogre::SceneNode*)camera_->getParentNode();
	camera_->getViewport()->setClearEveryFrame(true);

	//Initialises it 
	transform_ = entity_->getComponent<Transform>();
	if (transform_ == nullptr)
		std::cout << "ERROR: ENTITY " + entity_->getName() + " IS LACKING TRANSFORM COMPONENT" << std::endl;
	//Initialise camNode
	else
	{
		Vector3 pos = transform_->getPosition();
		camNode_->setPosition(pos);
		camNode_->lookAt(Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
		transform_->setRotation(camNode_->getOrientation());
	}
}

void Camera::update(unsigned int time)
{
	camNode_->setPosition(transform_->getPosition());
	camNode_->setOrientation(transform_->getRotation());
}

bool Camera::handleEvent(unsigned int time)
{
		if (InputManager::getSingletonPtr()->isKeyDown("Avanzar"))
			transform_->translate({ 0, 0, -10 });
		if (InputManager::getSingletonPtr()->isKeyDown("Retroceder"))
			transform_->translate({ 0, 0, 10 });
		if (InputManager::getSingletonPtr()->isKeyDown("MoverIzquierda"))
			transform_->translate(transform_->right() * -10);
		if (InputManager::getSingletonPtr()->isKeyDown("MoverDerecha"))
			transform_->translate(transform_->right() * 10);
		if (InputManager::getSingletonPtr()->isKeyDown("Ampliar"))
			transform_->translate({ 0, -10, 0 });
		if (InputManager::getSingletonPtr()->isKeyDown("Desampliar"))
			transform_->translate({ 0, 10, 0 });
		if (InputManager::getSingletonPtr()->isKeyDown("Ray")) 
			OgreManager::instance()->raycast();

		//Rueda del rat�n para hacer zoom (no se como se pone esto en el archivo del input porque no son teclas como tales)
		//ZOOM OUT
		if (InputManager::getSingletonPtr()->getMouse()->getMouseState().Z.rel > 0)
		{
			transform_->translate(transform_->forward() * 50); //TODO: quitar el 50 y poner un par�metro de sensibilidad
;			
		//ZOOM OUT
		}
		else if (InputManager::getSingletonPtr()->getMouse()->getMouseState().Z.rel < 0)
		{
			transform_->translate(transform_->forward() * -50);
		}
			
		return false;
}
