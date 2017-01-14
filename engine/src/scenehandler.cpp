#include "include/scenehandler.hpp"

SceneHandler::SceneHandler(const bool DEBUG)
    :DEBUG                       (DEBUG)
    ,logicPaused                 (false)
    ,drawSceneDebugThings        (true)
    ,lowSoundVolume              (10)
    ,mediumSoundVolume           (30)
    ,highSoundVolume             (60)
    ,maxSoundVolume              (90)
    ,maxSoundsSimultaneously     (100)
    ,updateFPS                   (100)
    ,FPSchangeStep               (1)
    // Members below are not intended to be modified
//    ,updateInterval(sf::seconds(1.f / updateFPS))
    ,window(sf::VideoMode(0, 0), "")
    ,soundHandler(SoundHandler(maxSoundsSimultaneously))
{
    // Ensure that debug-things are not drawn if DEBUG mode is off
    if(drawSceneDebugThings && !DEBUG)
        drawSceneDebugThings = false;
    // "seed" the random numbers (for the parts of the game to get a random value).
    // Note that this is a weak random number generator
    srand(static_cast<unsigned>(time(0)));
}

void SceneHandler::run()
{
    os << "Running game..." << std::endl;
    if(!scene) os << "Scene not set!" << std::endl;
    scene->setUp();
    this->setUpdateFPS();
    while(window.isOpen())
    {
        // 1. Handle user events and the handle user debug events
        // 2. Clear the window
        // 3. Draw normal things and then draw debug things on top
        // 4. Display everything
        // 5. Delete played sounds
        // 6. Update logic if it's not paused
        scene->userEventHandler->handleAllWindowEvents(window);
        window.clear();
        scene->draw(window);
        if(drawSceneDebugThings)
        {
            scene->drawDebugThings(window);
            _drawSceneHandlerDebugThings();
            scene->userEventHandler->drawDebugThings(window);
        }
        window.display(); // window.display blocks if its framerate-limit is exceeded
        // @TODO: ¿event handling could run in a different thread?
        soundHandler.deletePlayedSounds();
        if(!logicPaused)
            scene->update();
    }
    os << "...Exiting" << std::endl;
}

void SceneHandler::setScene(Scene* s)
{
    scene.reset(s);
    window.create(sf::VideoMode(scene->getWindowSize().x, scene->getWindowSize().y),
                  scene->getTitle()); // recreate the window
}

void SceneHandler::printSceneDebug()
{
    os << *scene << std::endl;
}

void SceneHandler::setUpdateFPS()
{
//    updateInterval = sf::seconds(1.f / updateFPS);
    window.setFramerateLimit(updateFPS);
    os << "SceneHandler::updateFPS = " << updateFPS << std::endl;
}

void SceneHandler::increaseUpdateFPS()
{
    updateFPS += FPSchangeStep;
    setUpdateFPS();
}

void SceneHandler::decreaseUpdateFPS()
{
    if (updateFPS > 1)
        updateFPS -= FPSchangeStep;
    setUpdateFPS();
}

void SceneHandler::_drawSceneHandlerDebugThings()
{
    // e.g. draw FPS on screen
}


