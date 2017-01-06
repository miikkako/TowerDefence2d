#ifndef TOWERDEFENCESCENE_HPP
#define TOWERDEFENCESCENE_HPP

#include "scene.hpp"

#define ASSETS std::string("assets/")
#define SPRITES ASSETS+"sprites/"

class TowerDefenceScene : public Scene
{
public:
    explicit TowerDefenceScene(SceneHandler& sh);
    TowerDefenceScene(const TowerDefenceScene&) = delete;
    TowerDefenceScene& operator=(const TowerDefenceScene&) = delete;

    //std::shared_ptr<Tower>& getTowerStats(const std::string& towerName);
    //std::vector<std::shared_ptr<Tower>>& getBaseTowers() const; 
    
    //sf::SoundBuffer& getSoundBuffer(const std::string& sound_name);
        
    //AnimatedGameObject::TextureList& getAnimation(const std::string& animation_name);
    
    //LevelHandler& levelHandler; // levelHandler handles spawning of Enemies!
    //
    //std::vector<std::shared_ptr<Tower>> baseTowerList;
    
    bool         drawHealthBars;
    bool         beginLevelsAutomatically;
    float        towerResellValueMultiplier;
    int          maxAllowedEnemiesTrough;
    int          startingMoney;
    
private:
    GameObjectList enemies;
    GameObjectList towers;
    GameObjectList projectiles;
    GameObjectList staticAnimations;
};

#endif /* TOWERDEFENCESCENE_HPP */

