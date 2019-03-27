#pragma once
#include <OgreTerrain.h>
#include <OgreTerrainGroup.h>
#include <GestorRecursos/ResourceManager.h>

class TerrainGenerator
{
public:
	TerrainGenerator();
	TerrainGenerator(Ogre::SceneManager * scnMgn, Ogre::Light * light, std::string terrainFile);
	~TerrainGenerator();
	Ogre::SceneManager * scnMgn_;

	//M�todos para la prueba del terreno
	json terrainJson_;
	void defineTerrain(long x, long y);
	void initBlendMaps(Ogre::Terrain* terrain);
	void configureTerrainDefaults(Ogre::Light* light);
	void getTerrainImage(bool flipX, bool flipY, Ogre::Image& img);

	bool mTerrainsImported_;
	Ogre::TerrainGroup* mTerrainGroup_;
	Ogre::TerrainGlobalOptions* mTerrainGlobals_;
};
