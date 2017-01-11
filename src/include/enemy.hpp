#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "towerdefencescene.hpp"
#include "map.hpp"

class Enemy : public AnimatedGameObject
{
public:
    
    ////////////////////////////////////////////////////////////
    /// \brief Construct an Enemy to the map
    /// \param current_scene "TowerDefenceScene" from which "Map" is got
    /// \param t \see AnimatedGameObject
    /// \param animation_tick_interval \see AnimatedGameObject
    /// \param map_path_index the index of the path this enemy moves. This value can be received from \see Map::getPathIndexForEnemy()
    /// \param health the health of the enemy
    /// \param speed the speed of the enemy
    ////////////////////////////////////////////////////////////
    Enemy(TowerDefenceScene* current_scene
         ,sf::Vector2f pos
         ,TextureList* t
         ,short unsigned animation_tick_interval
         ,float rotation_angle_degrees
         ,float health
         ,float speed);
    
//    bool update() override = 0;
    virtual int getPointsFromKill() = 0;
    
    /* @TODO: make a derived Enemy-class that doesn't just move through the waypoints,
     * but using the waypoints as a road, "drives" through the road like a rally car :) */
    
protected:
    sf::RectangleShape* createHealthBarAndReturnRef();
    void updateHealthbar();
    
    TowerDefenceScene*          currentScene;
    float                       health;
    float                       originalHealth;
    float                       speed;
    size_t                      currentWaypointIndex = 0;
    float                       speedDecrease = 0.f; // could be used for e.g. if a tower uses 'glue'
    sf::RectangleShape*         healthbarRectangle; // memory is managed by the base-class's childrenShapes-vector
};

class MapWaypointEnemy : public Enemy
{
public:
    MapWaypointEnemy(TowerDefenceScene* current_scene
                    ,TextureList* t
                    ,short unsigned animation_tick_interval
                    ,short unsigned map_path_index
                    ,float health
                    ,float speed);
    
    bool update() override;
    int getPointsFromKill() override;
    
protected:
    ////////////////////////////////////////////////////////////
    /// \brief Move the Enemy through the Map's waypoints smoothly
    /// \return has the Enemy reached its goal?
    ////////////////////////////////////////////////////////////
    bool moveWithWaypointsAndCheckIfGoaled();
    
    short unsigned              mapPathIndex;
};

#endif /* ENEMY_HPP */

