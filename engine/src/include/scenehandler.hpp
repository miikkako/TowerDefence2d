#ifndef SCENEHANDLER_HPP
#define SCENEHANDLER_HPP

#include "scene.hpp"
#include <stdlib.h>
#include <iostream>

class SceneHandler
{
public:
    explicit SceneHandler(const bool DEBUG);
    // explicit SceneHandler(Scene* starting_scene);
    SceneHandler(const SceneHandler&) = delete;
    SceneHandler& operator=(const SceneHandler&) = delete;
    void run();
    void setScene(Scene* s);
    
    friend class UserEventHandler;
    friend class Scene;
    
private:
    // These private methods are only meant to be called only by the UserEventHandler base class
    void pauseLogic() { if(DEBUG) logicPaused = !logicPaused; }; // friend method
    void toggleSceneDebugDraw() { drawSceneDebugThings = !drawSceneDebugThings; };
    void printSceneDebug();
    void setUpdateFPS();
    void increaseUpdateFPS();
    void decreaseUpdateFPS();
    
    // Private methods
    void debugRun(); // debugRun() is callad by run() if DEBUG mode is on
    void normalRun(); // normalRun() is callad by run() if DEBUG mode is off
    void _drawSceneHandlerDebugThings();
    
public:
    const bool                  DEBUG;
    std::ostream                nullStream;
    std::ostream*               os;
    std::ostream&               importantOs = std::cout;
    bool                        logicPaused;
    bool                        drawSceneDebugThings; // @TODO: make things private and usable by friends?
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

