#include "usereventhandler.hpp"
#include "scenehandler.hpp"
#include "include/scenehandler.hpp"

UserEventHandler::UserEventHandler(SceneHandler& sh)
    :sceneHandler(sh)
{ }

void UserEventHandler::handleWindowEvent(sf::RenderWindow& window)
{
    sf::Event e;
    while (window.pollEvent(e)) {
        if(e.type == sf::Event::Closed) {
            window.close();
        } else if(e.type == sf::Event::Resized) {
            
        } else if(e.type == sf::Event::MouseMoved) {
            this->handleMouseMoved(e);
            if(sceneHandler.DEBUG)
                handleMouseMovedDebug(e);
        } else if(e.type == sf::Event::MouseButtonPressed) {
            this->handleMouseButtonPressed(e);
            if(sceneHandler.DEBUG)
                handleMouseButtonPressedDebug(e);
        } else if(e.type == sf::Event::KeyPressed) {
            this->handleKeyPressed(e);
            if(sceneHandler.DEBUG)
                handleKeyPressedDebug(e);
        }
    }
}

void UserEventHandler::handleMouseMovedDebug(sf::Event& e)
{
    (void) e;
    // @TODO: a tooltip for drawing info about gameobjects
}

void UserEventHandler::handleMouseButtonPressedDebug(sf::Event& e)
{
    (void) e;
}

void UserEventHandler::handleKeyPressedDebug(sf::Event& e)
{
    if(e.key.code == sf::Keyboard::P) {
        sceneHandler.pauseLogic();
    } else if(e.key.code == sf::Keyboard::S) {
        sceneHandler.printSceneDebug();
    } else if(e.key.code == sf::Keyboard::D) {
        sceneHandler.toggleSceneDebugDraw();
    }
}

