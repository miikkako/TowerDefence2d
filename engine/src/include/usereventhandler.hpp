#ifndef USEREVENTHANDLER_HPP
#define USEREVENTHANDLER_HPP

#include <SFML/Graphics.hpp>

class SceneHandler;

class UserEventHandler
{
public:
    UserEventHandler(SceneHandler& sh, bool use_virtual_debug_methods);
    
    friend class SceneHandler;
    friend class Scene;
    
protected:
    virtual void handleMouseMoved(sf::Event& e) { (void) e; };
    virtual void handleMouseButtonPressed(sf::Event& e) { (void) e; };
    virtual void handleKeyPressed(sf::Event& e) { (void) e; };
    
    // These debug-methods get called if the member useVirtualDebugMethods is true
    virtual void handleMouseMovedDebug(sf::Event& e) { (void) e; };
    virtual void handleMouseButtonPressedDebug(sf::Event& e) { (void) e; };
    virtual void handleKeyPressedDebug(sf::Event& e) { (void) e; };
    
private:
    void handleWindowEvent(sf::RenderWindow& w); // Scene calls this
    void handleDebugWindowEvent(sf::RenderWindow& w); // Scene calls this
    
    // the default Debug-methods only get called when the SceneHandler's DEBUG-mode is on
    virtual void defaultHandleMouseMovedDebug(sf::Event& e);
    virtual void defaultHandleMouseButtonPressedDebug(sf::Event& e);
    virtual void defaultHandleKeyPressedDebug(sf::Event& e);
    
    SceneHandler& sceneHandler;
    bool          useVirtualDebugMethods;
};

#endif /* USEREVENTHANDLER_HPP */

