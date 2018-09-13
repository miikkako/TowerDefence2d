#ifndef MAP_HPP
#define MAP_HPP

#include "gameobject.hpp"

class TowerDefenceScene;

class Map : public AnimatedGameObject
{
public:
    typedef std::vector<sf::Vector2f> EnemyPath;
    typedef std::vector<EnemyPath> EnemyPathsList;
    
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
    void drawOtherDebugThings(sf::RenderWindow& w) override;
    void drawDebugTooltip(sf::RenderWindow& w, const sf::Font& f, const sf::Vector2u& window_size) const override
    { (void) w; (void) f; (void) window_size; }; // disable map's tooltip for now
    
private:
    void drawWaypoints(sf::RenderWindow& w) const;
    void initializeMap();
    void makeReversePaths(); // this method constructs a reverse path for every path
    
    TowerDefenceScene*                     currentScene;
    EnemyPathsList                         enemyPaths;
    short unsigned                         pathIndexOfLastEnemy = 0;
    std::string                            mapName;
    std::string                            contentFolderPath;
    std::string                            enemypathsFilename;
};

#endif /* MAP_HPP */

