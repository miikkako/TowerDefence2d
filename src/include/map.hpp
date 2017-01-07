#ifndef MAP_HPP
#define MAP_HPP

#include "gameobject.hpp"
#include "towerdefencescene.hpp"

class Map : public AnimatedGameObject
{
public:
    Map(TowerDefenceScene* current_scene, const std::string& map_name);
    
    short unsigned getPathIndexForEnemy();
    const sf::Vector2f& getWaypointCoordinate(short unsigned path_index, size_t waypoint_index) const;
    bool isWaypointIndexInBound(short unsigned path_index, size_t waypoint_index) const;
    bool onMap(const sf::Vector2f& coordinate) const;
    
private:
    bool loadMap(const std::string& map_name);
    
    short unsigned pathIndexOfLastEnemy = 0;
    std::vector<std::vector<sf::Vector2f>> enemyPaths;
};

#endif /* MAP_HPP */

