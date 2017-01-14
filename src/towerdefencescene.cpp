#include "towerdefencescene.hpp"
#include "include/enemy.hpp"
#include "include/tdusereventhandler.hpp"

#define ROOT_FOLDER std::string("../")
#define ASSETS ROOT_FOLDER+"assets/"
#define FONTS ASSETS+"fonts/"
#define MAPS ASSETS+"maps/"
#define ENEMIES ASSETS+"enemies/"

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
    map.reset(new Map(this, MAPS+map_name, "png"));
    maps.push_back(map);
    
    /* Configure animations and sounds and towerdefence-stuff below */
    std::string first_enemy_name(this->loadAndSaveAnimation(ENEMIES+"FirstEnemy", "png"));
}

void TowerDefenceScene::enemyThrough(Enemy* e)
{
    this->getOs() << *e << " through!" << std::endl;
    enemiesThrough += 1;
}

void TowerDefenceScene::spawnNewRandomEnemy()
{
    // @TODO: make this method better
    enemies.push_back(std::shared_ptr<Enemy>(new MapWaypointEnemy(this,
            getAnimation("FirstEnemy"), 5, map->getPathIndexForEnemy(), 100.f, 1.f)));
}

