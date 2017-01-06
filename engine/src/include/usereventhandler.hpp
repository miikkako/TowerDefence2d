#ifndef USEREVENTHANDLER_HPP
#define USEREVENTHANDLER_HPP

#include <SFML/Graphics.hpp>

class SceneHandler;

class UserEventHandler
{
public:
    explicit UserEventHandler(SceneHandler& sh);
    void handleWindowEvent(sf::RenderWindow& w);
protected:
    virtual void handleMouseMoved(sf::Event& e);
    virtual void handleKeyPressed(sf::Event& e);
    virtual void handleMouseButtonPressed(sf::Event& e);
    
    void handleDebugKeys(sf::Event& e);
    
    SceneHandler& sceneHandler;
};

#endif /* USEREVENTHANDLER_HPP */

