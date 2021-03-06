#include "include/tdusereventhandler.hpp"

TdUserEventHandler::TdUserEventHandler(SceneHandler& sh
                                      ,TowerDefenceScene* current_scene
                                      ,bool use_virtual_debug_methods)
        :UserEventHandler(sh, use_virtual_debug_methods)
        ,currentScene(current_scene)
{ }

void TdUserEventHandler::handleKeyPressedDebug()
{
    if(event.key.code == sf::Keyboard::M) {
        currentScene->getMap()->loadEnemyPathsFromFile();
    } else if(event.key.code == sf::Keyboard::E) {
        currentScene->spawnNewRandomEnemy();
    }
}
