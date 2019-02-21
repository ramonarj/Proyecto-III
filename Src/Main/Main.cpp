#include "initOgreApplication.h"
#include <OgreSceneManager.h>
#include <list>
#include <OgreResourceGroupManager.h>
#include <OgreStringVector.h>
#include "Arquitectura/Entity.h"

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
