#ifndef SCENEHANDLER_HPP
#define SCENEHANDLER_HPP

#include "scene.hpp"
#include <stdlib.h>
#include <iostream>

class SceneHandler
{
public:
    SceneHandler();
    // explicit SceneHandler(Scene* starting_scene);
    SceneHandler(const SceneHandler&) = delete;
    SceneHandler& operator=(const SceneHandler&) = delete;
    void run();
    void setScene(Scene* s);
    
    friend class UserEventHandler;
    
private:
    void pauseLogic() { if(DEBUG) logicPaused = !logicPaused; }; // friend method
    void setLogicFPS();
    void increaseLogicFPS();
    void decreaseLogicFPS();
    
public:
    /* Initialize the outputstreams in the header file so that they can be modified more easily */
    std::ostream&               os          = std::cerr; // os for debugging
    std::ostream&               importantOs = std::cout;
    const bool                  DEBUG;
    const int                   lowSoundVolume;
    const int                   mediumSoundVolume;
    const int                   highSoundVolume;
    const int                   maxSoundVolume;
    const unsigned              maxSoundsSimultaneously;
    
private:
    short unsigned              logicUpdateFPS;
    short unsigned              userActionUpdateFPS;
    sf::Time                    logicUpdateInterval;
    sf::Time                    userActionUpdateInterval;
    bool                        logicPaused = false;
    std::shared_ptr<Scene>      scene;
    sf::RenderWindow            window;
    SoundHandler                soundHandler;
};

#endif /* SCENEHANDLER_HPP */

