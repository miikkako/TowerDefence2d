#ifndef MAP_HPP
#define MAP_HPP

#include "gameobject.hpp"

class TowerDefenceScene;

class Map : public AnimatedGameObject
{
public:
    Map(TowerDefenceScene* current_scene
       ,const std::string& sprite_folder_path
       ,const std::string& image_file_extension);
    
    short unsigned getPathIndexForEnemy();
    const sf::Vector2f& getWaypoint(short unsigned path_index, size_t waypoint_index) const;
    bool isWaypointIndexInBound(short unsigned path_index, size_t waypoint_index) const;
    bool onMap(const sf::Vector2f& coordinate) const;
    
    ///////////////////////////////////////////////////
    /// \brief Load the enemy path
    /// Syntax: One path in one line like: "(x,y),(x,y)"...
    /// \return was the loading succesful?
    ///////////////////////////////////////////////////
    bool loadEnemyPathsFromFile();
    
protected:
    void drawOtherDebugThings(sf::RenderWindow& w) const override;
    
private:
    TowerDefenceScene*                     currentScene;
    std::vector<std::vector<sf::Vector2f>> enemyPaths;
    short unsigned                         pathIndexOfLastEnemy = 0;
    std::string                            mapName;
    std::string                            contentFolderPath;
    std::string                            enemypathsFilename;
};

#endif /* MAP_HPP */

