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
    const sf::Vector2f& getMouseWorldPos() const { return mouseWorldPos; };
    
    virtual void handleMouseMoved() { };
    virtual void handleMouseButtonPressed() { };
    virtual void handleMouseButtonReleased() { };
    virtual void handleKeyPressed() { };
    
    // These debug-methods get called if the member useVirtualDebugMethods is true
    virtual void handleMouseMovedDebug() { };
    virtual void handleMouseButtonPressedDebug() { };
    virtual void handleMouseButtonReleasedDebug() { };
    virtual void handleKeyPressedDebug() { };
    virtual void onDrawDebugThings(sf::RenderWindow& w) { (void) w; };
    
    sf::Event     event; // this event gets polled every time the handleAllWindowEvents is called
    sf::Vector2f  mouseWorldPos; // mouse position gets updated every time the handleAllWindowEvents is called
    bool          mouseButtonPressed;
    
private:
    void handleWindowEvents(sf::RenderWindow& w); // SceneHandler calls this if not DEBUG
    void handleNormalAndDebugWindowEvents(sf::RenderWindow& w); // SceneHandler calls this if DEBUG
    void drawDebugThings(sf::RenderWindow& w); // SceneHandler calls this
    
    // the default Debug-methods can only get called when the SceneHandler's DEBUG-mode is on
    void _defaultHandleMouseMovedDebug();
    void _defaultHandleMouseButtonPressedDebug();
    void _defaultHandleMouseButtonReleasedDebug();
    void _defaultHandleKeyPressedDebug();
    void _defaultOnDrawDebugThings(sf::RenderWindow& w);
    
    // Helper methods
    void _drawMousePosition(sf::RenderWindow& w);
    void _updateMouseWorldPosition(sf::RenderWindow& w);
    
    SceneHandler& sceneHandler;
    bool          useVirtualDebugMethods;
};

#endif /* USEREVENTHANDLER_HPP */

