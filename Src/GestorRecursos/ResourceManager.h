#pragma once

#include <Arquitectura/OgreIncludes.h>
#include <string>
#include <dirent.h>
#include <jsonParser.hpp>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

class Ogre::SceneManager;
class Ogre::SceneNode;
class Ogre::Entity;

using json = nlohmann::json;

class TerrainGenerator;

class ResourceManager 
{
public:
	~ResourceManager();

	static ResourceManager* instance();

	void initializeResources();
	void ceguiInit();


	json getJsonByKey(const std::string &key);

private:
	ResourceManager();

	static std::unique_ptr<ResourceManager> instance_;

	void loadJsonsFiles(const std::string resourcesPath);
	void loadJson(const std::string &streamFilePath, const std::string &fileName);

	const std::string FOLDER_PATH = "Assets\\jsons\\";

	

	//Contenedores de los recursos
	std::map<std::string, json> jsonMap;

};