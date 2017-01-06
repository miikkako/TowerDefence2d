#include "towerdefencescene.hpp"

TowerDefenceScene::TowerDefenceScene(SceneHandler& sh)
        :Scene(sh, sf::Vector2u(1024, 768))
        ,drawHealthBars             (true)
        ,beginLevelsAutomatically   (true)
        ,towerResellValueMultiplier (0.5f)
        ,maxAllowedEnemiesTrough    (10)
        ,startingMoney              (400)
{
    title = "Tower Defence";
    //userEventHandler.reset(new TowerDefenceUserActionHandler(sceneHandler));
    this->allGameObjects.push_back(&enemies);
    this->allGameObjects.push_back(&towers);
    this->allGameObjects.push_back(&projectiles);
    this->allGameObjects.push_back(&staticAnimations);
    /* init animations and sounds and towerdefence-stuff */
}