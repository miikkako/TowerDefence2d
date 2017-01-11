#ifndef MAP_HPP
#define MAP_HPP

#include "gameobject.hpp"

class TowerDefenceScene;

class Map : public AnimatedGameObject
{
public:
    Map(TowerDefenceScene* current_scene
       ,const std::string& map_name
       ,const std::string& sprite_folder_path
       ,const std::string& image_file_extension);
    
    bool update() override { return true; }; // nothing to be updated in the Map
    
    short unsigned getPathIndexForEnemy();
    const sf::Vector2f& getWaypoint(short unsigned path_index, size_t waypoint_index) const;
    bool isWaypointIndexInBound(short unsigned path_index, size_t waypoint_index) const;
    bool onMap(const sf::Vector2f& coordinate) const;
    
protected:
    void drawOtherDebugThings(sf::RenderWindow& w) const override;
    
private:    
    TowerDefenceScene*                     currentScene;
    std::vector<std::vector<sf::Vector2f>> enemyPaths;
    short unsigned                         pathIndexOfLastEnemy = 0;
};

#endif /* MAP_HPP */

