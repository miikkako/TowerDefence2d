#include "include/scenehandler.hpp"

SceneHandler::SceneHandler(const bool DEBUG)
    :DEBUG                       (DEBUG)
    ,logicPaused                 (false)
    ,drawSceneDebugThings        (true)
    ,boundingBoxColor            (sf::Color::Red)
    ,gameobjectOriginColor       (sf::Color::Cyan)
    ,lowSoundVolume              (10)
    ,mediumSoundVolume           (30)
    ,highSoundVolume             (60)
    ,maxSoundVolume              (90)
    ,maxSoundsSimultaneously     (100)
    ,updateFPS                   (100)
    ,FPSchangeStep               (1)
    /* Members below are not intended to be modified */
//    ,updateInterval(sf::seconds(1.f / updateFPS))
    ,window(sf::VideoMode(0, 0), "")
    ,soundHandler(SoundHandler(maxSoundsSimultaneously))
{
    /* "seed" the random numbers (for the parts of the game to get a random value).
     * Note that this is a weak random number generator */
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
        scene->handleWindowEvent(window); // this could run in a different thread
        window.clear();
        scene->draw(window);
        if(DEBUG && drawSceneDebugThings)
            scene->drawDebugThings(window);
        window.display(); // window.display blocks if its framerate-limit is exceeded
        soundHandler.deletePlayedSounds();
        if(DEBUG && !logicPaused)
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
