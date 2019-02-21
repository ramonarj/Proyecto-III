#include <iostream>
#include "PruebaLib/saluda.h"
#include <OgreRoot.h>
#include "initOgreApplication.h"
#include <OgreEntity.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <list>
#include <OgreResourceGroupManager.h>
#include <OgreStringVector.h>
#include <OgreCamera.h>
#include "checkML.h"

int main()
{
	//Para el control de basura
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Ogre::Root* root;
    #if _DEBUG
		root = new Ogre::Root("plugins_d.cfg");
    #else 	
		root = new Ogre::Root("plugins.cfg");
	#endif

	initOgreApplication* Ogreinit = new initOgreApplication(root);

	Ogre::SceneManager* scnMgr = Ogreinit->getSceneManager();

	scnMgr->createEntity("ogrehead.mesh");

	system("pause");


	return 0;
}
