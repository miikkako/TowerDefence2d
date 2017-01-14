#ifndef TOWERDEFENCESCENE_HPP
#define TOWERDEFENCESCENE_HPP

#include "scene.hpp"
#include "map.hpp"

class Enemy;

class TowerDefenceScene : public Scene
{
public:
    TowerDefenceScene(SceneHandler& sh, const std::string& map_name);
    TowerDefenceScene(const TowerDefenceScene&) = delete;
    TowerDefenceScene& operator=(const TowerDefenceScene&) = delete;
    
    //std::shared_ptr<Tower>& getTowerStats(const std::string& towerName);
    //std::vector<std::shared_ptr<Tower>>& getBaseTowers() const;         
    
    //LevelHandler& levelHandler; // levelHandler handles spawning of Enemies!
    //
    //std::vector<std::shared_ptr<Tower>> baseTowerList;
    void enemyThrough(Enemy* e);
    Map* getMap() { return map.get(); };
    void spawnNewRandomEnemy();
    
    bool           drawHealthBars;
    sf::Color      healthBarColor;
    sf::Vector2f   healthBarSize;
    bool           beginLevelsAutomatically;
    float          towerResellValueMultiplier;
    unsigned       maxAllowedEnemiesThrough;
    int            startingMoney;
    
    int            money = 0;
    int            score = 0;
    unsigned       enemiesThrough = 0;
    
private:
    std::shared_ptr<Map>    map;
    GameObjectList          maps;
    GameObjectList          enemies;
    GameObjectList          towers;
    GameObjectList          projectiles;
    GameObjectList          staticAnimations;
    DrawableList            enemyHealthbars;
};

#endif /* TOWERDEFENCESCENE_HPP */

