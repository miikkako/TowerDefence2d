#include "towerdefencescene.hpp"
#include "include/enemy.hpp"
#include "include/tdusereventhandler.hpp"
#include "button.hpp"

#define ROOT_FOLDER std::string("../")
#define ASSETS ROOT_FOLDER+"assets/"
#define FONTS ASSETS+"fonts/"
#define MAPS ASSETS+"maps/"
#define ENEMIES ASSETS+"enemies/"
#define BUTTONS ASSETS+"buttons/"

TowerDefenceScene::TowerDefenceScene(SceneHandler& sh, const std::string& map_name)
        :Scene(sh
              ,std::shared_ptr<UserEventHandler>(new TdUserEventHandler(sh, this, true))
              ,sf::Vector2u(1280, 720)
              ,"Defend!"
              ,"../engine/")
        ,drawHealthBars             (true)
        ,healthBarColor             (sf::Color::Green)
        ,healthBarSize              (sf::Vector2f(40, 6))
        ,beginLevelsAutomatically   (true)
        ,towerResellValueMultiplier (0.5f)
        ,maxAllowedEnemiesThrough   (10)
        ,startingMoney              (400)
{
    this->loadAndSaveFont(FONTS+"FiraSans/Regular.otf");
    
    this->addGameObjectListToBeUpdatedAndDrawn(&maps);
    this->addGameObjectListToBeUpdatedAndDrawn(&enemies);
    this->addGameObjectListToBeUpdatedAndDrawn(&towers);
    this->addGameObjectListToBeUpdatedAndDrawn(&projectiles);
    this->addGameObjectListToBeUpdatedAndDrawn(&staticAnimations);
    this->addGameObjectListToBeUpdatedAndDrawn(&buttons);
    map.reset(new Map(this, MAPS+map_name, "png"));
    maps.push_back(map);
    
    /* Configure animations and sounds and towerdefence-stuff below */
    // Enemies
    std::string first_enemy_name(this->loadAndSaveAnimation(ENEMIES+"FirstEnemy", "png"));
    
    // Buttons
    std::string fpsfastforward_button_passive_animation_name(this->loadAndSaveAnimation(BUTTONS+"FPSFastForward/Passive", "png"));
    std::string fpsfastforward_button_mb_pressed_animation_name(this->loadAndSaveAnimation(BUTTONS+"FPSFastForward/MBpressed", "png"));
    std::string fpsfastforward_button_active_animation_name(this->loadAndSaveAnimation(BUTTONS+"FPSFastForward/Active", "png"));
    buttons.push_back(std::shared_ptr<AnimatedGameObject>(new OnOffButton<SceneHandler>(
                                      sf::Vector2f(this->getWindowSize().x - 40, 100)
                                     ,this->getAnimation(fpsfastforward_button_passive_animation_name)
                                     ,this->getAnimation(fpsfastforward_button_mb_pressed_animation_name)
                                     ,this->getAnimation(fpsfastforward_button_active_animation_name)
                                     ,0
                                     ,&SceneHandler::setFastForwardFPS
                                     ,&sceneHandler
                                     ,this)));
}

void TowerDefenceScene::updateSceneBehaviour()
{
    
}

void TowerDefenceScene::enemyThrough(Enemy* e)
{
    this->getOs() << *e << " through!" << std::endl;
    enemiesThrough += 1;
}

void TowerDefenceScene::spawnNewRandomEnemy()
{
    // @TODO: make this method better
    enemies.push_back(std::shared_ptr<Enemy>(new MapWaypointEnemy(this->getAnimation("FirstEnemy")
                                                                 ,5
                                                                 ,map->getPathIndexForEnemy()
                                                                 ,this
                                                                 ,100.f
                                                                 ,1.f
                                                                 ,nullptr
                                                                 ,nullptr)));
}

