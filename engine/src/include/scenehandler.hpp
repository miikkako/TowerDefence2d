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
    
private: // these private methods are only callable by the UserEventHandler base class
    void pauseLogic() { if(DEBUG) logicPaused = !logicPaused; }; // friend method
    void toggleSceneDebugDraw() { drawSceneDebugThings = !drawSceneDebugThings; };
    void printScene();
    void setUpdateFPS();
    void increaseUpdateFPS();
    void decreaseUpdateFPS();
    
public:
    /* Initialize the outputstreams in the header file so that they can be modified more easily */
    std::ostream&               os          = std::cerr; // os for debugging
    std::ostream&               importantOs = std::cout;
    const bool                  DEBUG;
    bool                        logicPaused;
    bool                        drawSceneDebugThings;
    const sf::Color             boundingBoxColor;
    const sf::Color             gameobjectOriginColor;
    const int                   lowSoundVolume;
    const int                   mediumSoundVolume;
    const int                   highSoundVolume;
    const int                   maxSoundVolume;
    const unsigned              maxSoundsSimultaneously;
    
private:
    short unsigned              updateFPS;
    short unsigned              FPSchangeStep;
    sf::Time                    updateInterval;
    std::shared_ptr<Scene>      scene;
    sf::RenderWindow            window;
    SoundHandler                soundHandler;
};

#endif /* SCENEHANDLER_HPP */

