#include "include/scenehandler.hpp"

SceneHandler::SceneHandler()
    :DEBUG                   (true)
    ,lowSoundVolume          (10)
    ,mediumSoundVolume       (30)
    ,highSoundVolume         (60)
    ,maxSoundVolume          (90)
    ,maxSoundsSimultaneously (100)
    ,logicUpdateFPS          (100)
    ,userActionUpdateFPS     (200)
    /* Members below are not intended to be modified */
    ,logicUpdateInterval(sf::seconds(1.f / logicUpdateFPS))
    ,userActionUpdateInterval(sf::seconds(1.f / userActionUpdateFPS))
    ,window(sf::VideoMode(10, 10), "")
    ,soundHandler(SoundHandler(maxSoundsSimultaneously))
{
    /* "seed" the random numbers (for the parts of the game to get a random value).
     * Note that this is a weak random number generator */
    srand(static_cast<unsigned>(time(0)));
}

void SceneHandler::run()
{
    os << "Running game..." << std::endl;
    if(!scene) os << "Scene not set" << std::endl;
    sf::Clock logic_clock, useraction_clock;
    sf::Time elapsed_since_last_logic_update, elapsed_since_last_useraction_update;
    scene->setUp();
    while(window.isOpen())
    {
        /* @TODO: sleep if possible */
        elapsed_since_last_useraction_update = useraction_clock.getElapsedTime();
        if(elapsed_since_last_useraction_update > userActionUpdateInterval)
        {
            scene->handleWindowEvent(window);
            useraction_clock.restart();
        }
        elapsed_since_last_logic_update = logic_clock.getElapsedTime();
        if(!logicPaused && elapsed_since_last_logic_update > logicUpdateInterval)
        {
            window.clear();
            scene->draw(window);
            window.display();
            soundHandler.deletePlayedSounds();
            scene->update();
            logic_clock.restart();
        }
    }
    os << "...Exiting" << std::endl;
}

void SceneHandler::setScene(Scene* s)
{
    scene.reset(s);
    window.setSize(scene->getWindowSize());
    window.setTitle(scene->getTitle());
}

void SceneHandler::setLogicFPS()
{
    logicUpdateInterval = sf::seconds(1.f / logicUpdateFPS);
    if(logicUpdateFPS < 60)
        window.setFramerateLimit(60);
    else
        window.setFramerateLimit(logicUpdateFPS);
}

void SceneHandler::increaseLogicFPS()
{
    logicUpdateFPS += 10;
    setLogicFPS();
}

void SceneHandler::decreaseLogicFPS()
{
    if(logicUpdateFPS > 10)
        logicUpdateFPS -= 10;
    else if (logicUpdateFPS > 1)
        logicUpdateFPS -= 1;
    setLogicFPS();
}
