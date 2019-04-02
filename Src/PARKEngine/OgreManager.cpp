#include "OgreManager.h"

//NUESTRO
#include "ResourceManager.h""
#include "SceneManager.h"
#include "TerrainCreator.h"
#include "Utils.h"

//CEGUI
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

#include "InputManager.h"

//OIS
#include <OIS.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OISInputManager.h>

#include "SDL.h"
//OGRE
#include "OgreIncludes.h"
#include <iostream>

// Bootstrap CEGUI::System with an OgreRenderer object that uses the
// default Ogre rendering window as the default output surface, an Ogre based
// ResourceProvider, and an Ogre based ImageCodec.
   //CEGUI::OgreRenderer& myRenderer = CEGUI::OgreRenderer::bootstrapSystem();

std::unique_ptr<OgreManager> OgreManager::instance_;




OgreManager * OgreManager::instance(std::string initFileJson)
{
	//Devuelve la instancia si exise, si no crea una nueva
	if (instance_.get() == nullptr)
		instance_.reset(new OgreManager(initFileJson));

	return instance_.get();
}

OgreManager * OgreManager::instance()
{
	//Devuelve la instancia si exise, si no crea una nueva
	if (instance_.get() == nullptr)
		std::cout << "ERROR: OGRE INSTANCE HAS NOT BEEN INITIALISED PROPERLY" << std::endl;

	return instance_.get();
}


OgreManager::OgreManager(std::string initFileJson):plane_(nullptr)
{	

#if _DEBUG
	root_ = new Ogre::Root("plugins_d.cfg");
#else 	
	root_ = new Ogre::Root("plugins.cfg");
#endif

	root_->setRenderSystem(*(root_->getAvailableRenderers().begin()));
	root_->initialise(false);

	ResourceManager::instance()->initializeResources();

	sceneMgr_ = root_->createSceneManager();

	initWindow(initFileJson);		

	
	//ceguiInit();

	//Inicialización de ventana de SDL que se una a la de Ogre
	SDL_Init(SDL_INIT_EVERYTHING);
	hWnd = 0;
	window_->getCustomAttribute("WINDOW", &hWnd);
	SDL_CreateWindowFrom((void*)hWnd);
}

/*
void OgreSystem::ceguiInit() {
	//Carga de CEGUI y configurado automatico con elementos de OGRE
	CEGUI::OgreRenderer& myRenderer = CEGUI::OgreRenderer::bootstrapSystem(*static_cast<Ogre::RenderTarget*>(getWindow()));


}

*/

OgreManager::~OgreManager()
{
	CEGUI::System::destroy();
	
	if (root_ != nullptr)
		delete root_;
	if (plane_ != nullptr)
		delete plane_;

	instance_.release();
}

void OgreManager::render(unsigned int deltaTime)
{
	root_->renderOneFrame((Ogre::Real)deltaTime / 1000);	

	OIS::Mouse* mouse =  InputManager::getSingletonPtr()->getMouse();
	std::cout << CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().getPosition().d_x << std::endl;
	CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(mouse->getMouseState().X.rel
		, mouse->getMouseState().Y.rel );

}

Ogre::SceneManager * OgreManager::getSceneManager()
{
	return sceneMgr_;
}

Ogre::MeshManager * OgreManager::getMeshManager()
{
	return &Ogre::MeshManager::getSingleton();
}

Ogre::ResourceGroupManager * OgreManager::getResourceGroupManager()
{
	return &Ogre::ResourceGroupManager::getSingleton();
}

Ogre::TextureManager * OgreManager::getTextureManager()
{
	return &Ogre::TextureManager::getSingleton();
}

Ogre::FileSystemLayer * OgreManager::createFileSystemLayer(std::string cfLayerSystem)
{
	return OGRE_NEW Ogre::FileSystemLayer("cfLayerSystem");
}

void OgreManager::initWindow(std::string initFileJson)
{
	json initFile = ResourceManager::instance()->getJsonByKey(initFileJson);
	window_ = root_->createRenderWindow(initFile["WindowName"], initFile["Width"], initFile["Height"], false);
	window_->setFullscreen(initFile["fullScreen"], initFile["Width"], initFile["Height"]);
	window_->setActive(true);
	window_->setAutoUpdated(true);
	window_->setDeactivateOnFocusChange(false);

	sceneMgr_->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));

	Vector3 lightdir(0.55, -0.3, 0.75);
	lightdir.normalise();

	light_ = sceneMgr_->createLight("TestLight");
	light_->setType(Ogre::Light::LT_DIRECTIONAL);
	light_->setDirection(lightdir);
	light_->setDiffuseColour(Ogre::ColourValue::White);
	light_->setSpecularColour(Ogre::ColourValue(240 / 255, 240 / 255, 188 / 255));

	plane_ = new Ogre::Plane();
	plane_->d = 1000;
	plane_->normal = Vector3::NEGATIVE_UNIT_Y;
	sceneMgr_->setSkyPlane(
		true, *plane_, "SkyBox", 1500, 50, true, 1.5, 150, 150);
#if _DEBUG
	sceneMgr_->showBoundingBoxes(true); //Para debuggear las aabb
#endif
}


Ogre::Camera* OgreManager::createCamera(std::string name, Ogre::SceneNode* FatherNode, float NearClipDist, float FarClipDist, bool autoAspectRatio, float AspectRatio)
{
	Ogre::Camera* cam_ = getSceneManager()->createCamera(name);
	cam_->setNearClipDistance(NearClipDist);
	cam_->setFarClipDistance(FarClipDist);
	FatherNode->attachObject(cam_);
	if (autoAspectRatio)cam_->setAutoAspectRatio(autoAspectRatio);
	else cam_->setAspectRatio(AspectRatio);
	return cam_;
}

Ogre::Entity * OgreManager::createPlane(std::string name, std::string MaterialName, float width, float height, int Xsegments, int Ysegments, Ogre::SceneNode* FatherNode)
{
	Ogre::Entity* plane;
	getMeshManager()->createPlane(name, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Ogre::Plane(Vector3::UNIT_Y, 0), width, height,
		Xsegments, Ysegments, true, 1, 1.0, 1.0, Vector3::NEGATIVE_UNIT_Z);
	plane = getSceneManager()->createEntity(name);
	plane->setMaterialName(MaterialName);
	FatherNode->attachObject(plane);
	return plane;
}

TerrainGenerator * OgreManager::createTerrain(std::string terrainFile)
{
	TerrainGenerator* terrainCreator_ = new TerrainGenerator(getSceneManager(), getLight(), terrainFile);
	return terrainCreator_;
}

void OgreManager::deleteFileSystemLayer(Ogre::FileSystemLayer * fsLayer)
{
	OGRE_DELETE fsLayer;
}

