#include "MeshRenderer.h"

#include "Entity.h"
#include "Transform.h"


#include "OgreIncludes.h"
#include "OgreManager.h"
#include <iostream>


MeshRenderer::MeshRenderer(): node_(nullptr), transform_(nullptr)
{
}

MeshRenderer::MeshRenderer(std::string meshName, bool visible)
{
	Ogre::Entity* ogreEntity = OgreManager::instance()->getSceneManager()->createEntity(meshName);
	node_ = OgreManager::instance()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
	node_->attachObject(ogreEntity);
	node_->setVisible(visible);
}

void MeshRenderer::load(json file)
{
	std::string meshName = file["mesh"];
	Ogre::Entity* ogreEntity = OgreManager::instance()->getSceneManager()->createEntity(meshName);
	node_ = OgreManager::instance()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
	if (file["material"] != "")
		ogreEntity->setMaterialName(file["material"]);
	node_->attachObject(ogreEntity);
	node_->setVisible(file["visible"]);
}

MeshRenderer::~MeshRenderer()
{
	
}

void MeshRenderer::start()
{
	transform_ = entity_->getComponent<Transform>();
	if (transform_ == nullptr)
		std::cout << "ERROR: ENTITY " + entity_->getName() + " IS LACKING TRANSFORM COMPONENT" << std::endl;
}

void MeshRenderer::update(unsigned int time)
{
	if(transform_ != nullptr)
	{
		node_->setPosition(transform_->getPosition());
		node_->setOrientation(transform_->getOrientation());
		node_->setScale(transform_->getScale());
	}
}

Ogre::SceneNode * MeshRenderer::getNode()
{
	 return node_; 
}

void MeshRenderer::setVisible(bool b)
{
	node_->setVisible(b);
}
