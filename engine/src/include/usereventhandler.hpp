#ifndef USEREVENTHANDLER_HPP
#define USEREVENTHANDLER_HPP

#include <SFML/Graphics.hpp>

class SceneHandler;

class UserEventHandler
{
public:
    explicit UserEventHandler(SceneHandler& sh);
    
    friend class SceneHandler;
    friend class Scene;
    
protected:
    virtual void handleMouseMoved(sf::Event& e) { (void) e; };
    virtual void handleMouseButtonPressed(sf::Event& e) { (void) e; };
    virtual void handleKeyPressed(sf::Event& e) { (void) e; };
    
    
private:
    void handleWindowEvent(sf::RenderWindow& w); // Scene calls this
    
    // the Debug-methods only get called when the SceneHandler's DEBUG-mode is on
    virtual void handleMouseMovedDebug(sf::Event& e);
    virtual void handleMouseButtonPressedDebug(sf::Event& e);
    virtual void handleKeyPressedDebug(sf::Event& e);
    
    SceneHandler& sceneHandler;
};

#endif /* USEREVENTHANDLER_HPP */

