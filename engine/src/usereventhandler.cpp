#include "usereventhandler.hpp"
#include "scenehandler.hpp"
#include "include/scenehandler.hpp"

UserEventHandler::UserEventHandler(SceneHandler& sh, bool use_virtual_debug_methods)
        :sceneHandler(sh)
        ,useVirtualDebugMethods(use_virtual_debug_methods)
{ }

void UserEventHandler::handleWindowEvent(sf::RenderWindow& w)
{
    sf::Event e;
    while(w.pollEvent(e)) {
        if(e.type == sf::Event::Closed) {
            w.close();
        } else if(e.type == sf::Event::Resized) {
            
        } else if(e.type == sf::Event::MouseMoved) {
            this->handleMouseMoved(e);
            if(useVirtualDebugMethods)
                this->handleMouseMovedDebug(e);
        } else if(e.type == sf::Event::MouseButtonPressed) {
            this->handleMouseButtonPressed(e);
            if(useVirtualDebugMethods)
                this->handleMouseButtonPressedDebug(e);
        } else if(e.type == sf::Event::KeyPressed) {
            this->handleKeyPressed(e);
            if(useVirtualDebugMethods)
                this->handleKeyPressedDebug(e);
        }
    }
}

void UserEventHandler::handleDebugWindowEvent(sf::RenderWindow& w)
{
    sf::Event e;
    while(w.pollEvent(e)) {
        if(e.type == sf::Event::MouseMoved) {
            defaultHandleMouseMovedDebug(e);
        } else if(e.type == sf::Event::MouseButtonPressed) {
            defaultHandleMouseButtonPressedDebug(e);
        } else if(e.type == sf::Event::KeyPressed) {
            defaultHandleKeyPressedDebug(e);
        }
    }
}

void UserEventHandler::defaultHandleMouseMovedDebug(sf::Event& e)
{
    (void) e;
    // @TODO: a tooltip for drawing info about gameobjects
}

void UserEventHandler::defaultHandleMouseButtonPressedDebug(sf::Event& e)
{
    (void) e;
}

void UserEventHandler::defaultHandleKeyPressedDebug(sf::Event& e)
{
    if(e.key.code == sf::Keyboard::P) {
        sceneHandler.pauseLogic();
    } else if(e.key.code == sf::Keyboard::S) {
        sceneHandler.printSceneDebug();
    } else if(e.key.code == sf::Keyboard::D) {
        sceneHandler.toggleSceneDebugDraw();
    } else if(e.key.code == sf::Keyboard::A) {
        sceneHandler.decreaseUpdateFPS();
    } else if(e.key.code == sf::Keyboard::Z) {
        sceneHandler.increaseUpdateFPS();
    }
}

