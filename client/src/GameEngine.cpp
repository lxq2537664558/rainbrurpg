#include "GameEngine.hpp"
//#include "Logger.hpp"

#include <Ogre.h>

using namespace Ogre;

GameEngine::GameEngine(void)
{
  //  log("Starting Ogre::Root");
  Root* mRoot = new Root();
  if (mRoot->showConfigDialog())
    {
      //    log("Creating rendering window");
      RenderWindow* rw = mRoot->initialise(true, "RPG");
      
      // Create the SceneManager, in this case a generic one
      SceneManager* mSceneMgr = mRoot->createSceneManager(ST_GENERIC, "ExampleSMInstance");
      
      // Create the camera
      Camera* mCamera = mSceneMgr->createCamera("PlayerCam");
      
      
      mRoot->startRendering();
    }
}
