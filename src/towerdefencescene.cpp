#include "towerdefencescene.hpp"
#include "include/enemy.hpp"

#define ROOT_FOLDER std::string("../")
#define ASSETS ROOT_FOLDER+"assets/"
#define SPRITES ASSETS+"sprites/"

TowerDefenceScene::TowerDefenceScene(SceneHandler& sh, const std::string& map_name)
        :Scene(sh
              ,new /* Here TDUserEventHandler */ UserEventHandler(sh)
              ,sf::Vector2u(1280, 720)
              ,"Defend!")
        ,drawHealthBars             (true)
        ,healthBarColor             (sf::Color::Green)
        ,healthBarSize              (sf::Vector2f(45, 8))
        ,beginLevelsAutomatically   (true)
        ,towerResellValueMultiplier (0.5f)
        ,maxAllowedEnemiesThrough   (10)
        ,startingMoney              (400)
{
    this->addGameObjectListToBeUpdatedAndDrawn(&maps);
    this->addGameObjectListToBeUpdatedAndDrawn(&enemies);
    this->addGameObjectListToBeUpdatedAndDrawn(&towers);
    this->addGameObjectListToBeUpdatedAndDrawn(&projectiles);
    this->addGameObjectListToBeUpdatedAndDrawn(&staticAnimations);
    map.reset(new Map(this, map_name, SPRITES+"Maps/"+map_name, "png"));
    maps.push_back(map);
    
    /* Configure animations and sounds and towerdefence-stuff below */
    std::string first_enemy_name = this->loadAndSaveAnimation(SPRITES+"Enemies/FirstEnemy", "png");
    
    enemies.push_back(std::shared_ptr<Enemy>(new MapWaypointEnemy(this,
            getAnimation(first_enemy_name), 5, map->getPathIndexForEnemy(), 100.f, 1.f)));
}

void TowerDefenceScene::enemyThrough(Enemy* e)
{
    this->getOs() << "Enemy " << *e << " through!" << std::endl;
    enemiesThrough -= 1;
}

