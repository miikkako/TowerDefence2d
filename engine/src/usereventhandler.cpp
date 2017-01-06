#include "usereventhandler.hpp"
#include "scenehandler.hpp"

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
            
        } else if(e.type == sf::Event::KeyPressed) {
            handleKeyPressed(e);
        } else if(e.type == sf::Event::MouseButtonPressed) {
            handleMouseButtonPressed(e);
        } else if(e.type == sf::Event::MouseMoved) {
            handleMouseMoved(e);
        }
    }
}

void UserEventHandler::handleMouseMoved(sf::Event& e)
{
    (void) e;
    //scaleMousePositionCoordinates(e);
}

void UserEventHandler::handleKeyPressed(sf::Event& e)
{
    /* This method is meant to be overridden */
    this->handleDebugKeys(e);
}

void UserEventHandler::handleMouseButtonPressed(sf::Event& e)
{
    (void) e;
}

void UserEventHandler::handleDebugKeys(sf::Event& e)
{
    if (e.key.code == sf::Keyboard::P) {
        sceneHandler.pauseLogic();
    }
}