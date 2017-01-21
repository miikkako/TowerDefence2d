#include "usereventhandler.hpp"
#include "scenehandler.hpp"
#include "include/scenehandler.hpp"

UserEventHandler::UserEventHandler(SceneHandler& sh, bool use_virtual_debug_methods)
        :sceneHandler(sh)
        ,useVirtualDebugMethods(use_virtual_debug_methods)
{ }

void UserEventHandler::handleWindowEvents(sf::RenderWindow& w)
{
    _updateMouseWorldPosition(w);
    while(w.pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            w.close();
        } else if(event.type == sf::Event::Resized) {
            
        } else if(event.type == sf::Event::MouseMoved) {
            this->handleMouseMoved();
        } else if(event.type == sf::Event::MouseButtonPressed) {
            sceneHandler.scene->executeMouseButtonPressedActions();
            this->handleMouseButtonPressed();
        } else if(event.type == sf::Event::MouseButtonReleased) {
            sceneHandler.scene->executeMouseButtonReleasedActions();
            this->handleMouseButtonReleased();
        } else if(event.type == sf::Event::KeyPressed) {
            this->handleKeyPressed();
        }
    }
}

void UserEventHandler::handleNormalAndDebugWindowEvents(sf::RenderWindow& w)
{
    _updateMouseWorldPosition(w);
    while(w.pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            w.close();
        } else if(event.type == sf::Event::Resized) {
            
        } else if(event.type == sf::Event::MouseMoved) {
            this->handleMouseMoved();
            _defaultHandleMouseMovedDebug();
            if(useVirtualDebugMethods)
                this->handleMouseMovedDebug();
        } else if(event.type == sf::Event::MouseButtonPressed) {
            sceneHandler.scene->executeMouseButtonPressedActions();
            this->handleMouseButtonPressed();
            _defaultHandleMouseButtonPressedDebug();
            if(useVirtualDebugMethods)
                this->handleMouseButtonPressedDebug();
        } else if(event.type == sf::Event::MouseButtonReleased) {
            sceneHandler.scene->executeMouseButtonReleasedActions();
            this->handleMouseButtonReleased();
            _defaultHandleMouseButtonReleasedDebug();
            if(useVirtualDebugMethods)
                this->handleMouseButtonReleasedDebug();
        } else if(event.type == sf::Event::KeyPressed) {
            this->handleKeyPressed();
            _defaultHandleKeyPressedDebug();
            if(useVirtualDebugMethods)
                this->handleKeyPressedDebug();
        }
    }
}

void UserEventHandler::drawDebugThings(sf::RenderWindow& w)
{
    _defaultOnDrawDebugThings(w);
    this->onDrawDebugThings(w);
}

void UserEventHandler::_defaultHandleMouseMovedDebug()
{
    
}

void UserEventHandler::_defaultHandleMouseButtonPressedDebug()
{
    
}

void UserEventHandler::_defaultHandleMouseButtonReleasedDebug()
{
    
}

void UserEventHandler::_defaultHandleKeyPressedDebug()
{
    if(event.key.code == sf::Keyboard::P) {
        sceneHandler.pauseLogic();
    } else if(event.key.code == sf::Keyboard::S) {
        sceneHandler.printSceneDebug();
    } else if(event.key.code == sf::Keyboard::D) {
        sceneHandler.toggleSceneDebugDraw();
    } else if(event.key.code == sf::Keyboard::Z) {
        sceneHandler.decreaseUpdateFPS();
    } else if(event.key.code == sf::Keyboard::A) {
        sceneHandler.increaseUpdateFPS();
    }
}

void UserEventHandler::_defaultOnDrawDebugThings(sf::RenderWindow& w)
{
    _drawMousePosition(w);
}

void UserEventHandler::_drawMousePosition(sf::RenderWindow& w)
{
    sf::Vector2i world_pos(mouseWorldPos);
    sf::Text t;
    t.setString(std::to_string(world_pos.x) + "," + std::to_string(world_pos.y));
    t.setCharacterSize(17);
    t.setStyle(sf::Text::Regular);
    t.setFillColor(sf::Color::Black);
    t.setFont(sceneHandler.scene->getDefaultFont());
    AnimatedGameObject::setTextOriginToCenter(t);
    t.setPosition(world_pos.x, world_pos.y - 10);
    w.draw(t);
}

void UserEventHandler::_updateMouseWorldPosition(sf::RenderWindow& w)
{
    // Get the current mouse position in the window
    sf::Vector2i pixel_pos(sf::Mouse::getPosition(w));
    // Convert it to world coordinates and usable through this class
    mouseWorldPos = w.mapPixelToCoords(pixel_pos);
}
