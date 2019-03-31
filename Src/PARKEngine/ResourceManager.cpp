#include "ResourceManager.h"

//CEGUI
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

//OGRE
#include <PARKEngine/OgreIncludes.h>

//NUESTRO
#include <PARKEngine/OgreManager.h>



std::unique_ptr<ResourceManager> ResourceManager::instance_;

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
	instance_.release();
}

ResourceManager * ResourceManager::instance()
{

	if (instance_.get() == nullptr)
		instance_.reset(new ResourceManager());

	return instance_.get();
}

void ResourceManager::initializeResources()
{
	Ogre::ConfigFile cf;

	Ogre::FileSystemLayer* mFSLayer = OgreManager::instance()->createFileSystemLayer("cfLayerSystem");
	//Este metodo ya agrega '_d' si se compila en debug
	Ogre::String resourcesPath = mFSLayer->getConfigFilePath("resources.cfg");

	std::string jsonPath;
	
	if (Ogre::FileSystemLayer::fileExists(resourcesPath))
		cf.load(resourcesPath);

	else
		throw::std::invalid_argument("Archivo resources.cfg no encontrado");

	Ogre::String sec, type, arch;

	// Recorre todos los grupos de recursos definidos en el archivo
	Ogre::ConfigFile::SettingsBySection_::const_iterator seci;

	for (seci = cf.getSettingsBySection().begin(); seci != cf.getSettingsBySection().end(); ++seci)
	{
		sec = seci->first;

		const Ogre::ConfigFile::SettingsMultiMap& settings = seci->second;
		Ogre::ConfigFile::SettingsMultiMap::const_iterator i;

		// Recorre todos los path
		for (i = settings.begin(); i != settings.end(); i++)
		{
			type = i->first;
			std::string auxPath = resourcesPath;
			auxPath.erase(auxPath.find_last_of("\\") + 1, auxPath.size() - 1);
			jsonPath = auxPath;
			arch = auxPath + Ogre::FileSystemLayer::resolveBundlePath(i->second);

			//Va agregando las ubicaciones definidas en el cfg
			OgreManager::instance()->getResourceGroupManager()->addResourceLocation(arch, type, sec);
		}
	}

	OgreManager::instance()->getTextureManager()->setDefaultNumMipmaps(5);

	OgreManager::instance()->getResourceGroupManager()->initialiseAllResourceGroups();

	OgreManager::instance()->deleteFileSystemLayer(mFSLayer);

	loadJsonsFiles(jsonPath);

}

void ResourceManager::ceguiInit() {
	//Carga de CEGUI y configurado automatico con elementos de OGRE
	CEGUI::OgreRenderer& myRenderer = CEGUI::OgreRenderer::bootstrapSystem(*static_cast<Ogre::RenderTarget*>(OgreManager::instance()->getWindow()));

	//Carga de cosas
	// create (load) the TaharezLook scheme file
	// (this auto-loads the TaharezLook looknfeel and imageset files)
	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");

	// create (load) a font.
	// The first font loaded automatically becomes the default font, but note
	// that the scheme might have already loaded a font, so there may already
	// be a default set - if we want the "DejaVuSans-10" font to definitely
	// be the default, we should set the default explicitly afterwards.
	CEGUI::FontManager::getSingleton().createFromFile("DejaVuSans-10.font");

	CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultFont("DejaVuSans-10");
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
	CEGUI::System::getSingleton().getDefaultGUIContext().setDefaultTooltipType("TaharezLook/Tooltip");

	
	//Crear ventana cegui de prueba
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	CEGUI::Window* myRoot = wmgr.createWindow("DefaultWindow", "root");
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(myRoot);
	CEGUI::FrameWindow* fWnd = static_cast<CEGUI::FrameWindow*>(wmgr.createWindow("TaharezLook/FrameWindow", "testWindow"));
	myRoot->addChild(fWnd);
	// position a quarter of the way in from the top-left of parent.
	fWnd->setPosition(CEGUI::UVector2(CEGUI::UDim(0.25f, 0.0f), CEGUI::UDim(0.25f, 0.0f)));
	// set size to be half the size of the parent
	fWnd->setSize(CEGUI::USize(CEGUI::UDim(0.5f, 0.0f), CEGUI::UDim(0.5f, 0.0f)));
	fWnd->setText("Hello World!");
}

json ResourceManager::getJsonByKey(const std::string & key)
{
	std::map<std::string, json>::iterator it = jsonMap.find(key);

	//Si el puntero devuelve end() no ha encontrado ese archivo
	if (it != jsonMap.end()) return (*it).second;
	else return nullptr;
}

void ResourceManager::loadJsonsFiles(const std::string resourcesPath)
{
	//Se le a�ade al path exes la carpeta Assets\\jsons
	std::string filePath = resourcesPath + FOLDER_PATH;
	const char* filePathC = filePath.c_str();

	DIR *dir;
	struct dirent *ent;

	/*Se busca todos los archivos que existen el el directorio filePathPc*/
	if ((dir = opendir(filePathC)) != NULL) {

		while ((ent = readdir(dir)) != NULL) {
			//No se procesa el dir actual ni el padre
			if ((strcmp(ent->d_name, ".") == 1) && (strcmp(ent->d_name, "..") == 1)) {

				//Para los demas se abren, se leen y se pasan al tipo json
				std::fstream fStream;
				fStream.open(filePath + ent->d_name);
				loadJson(filePath + ent->d_name, ent->d_name);
				fStream.close();
			}
		}
		closedir(dir);
	}
}

void ResourceManager::loadJson(const std::string & streamFilePath, const std::string & fileName)
{
	std::fstream stream_(streamFilePath);
	json j;
	stream_ >> j;
	//Se inserta los json que se van encontrando en el dir al diccionario
	jsonMap.insert(std::pair<std::string, json>(fileName, j));
}

