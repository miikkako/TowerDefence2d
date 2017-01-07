#include "include/map.hpp"

Map::Map(TowerDefenceScene* current_scene, const std::string& map_name)
        :AnimatedGameObject(0, 0, nullptr, -1, false)
{
    currentScene = current_scene;
    if(!loadMap(map_name))
        throw std::invalid_argument("No map named '" + map_name + "' found.");
}

short unsigned Map::getPathIndexForEnemy()
{
    if(++pathIndexOfLastEnemy >= enemyPaths.size())
        pathIndexOfLastEnemy = 0;
    return pathIndexOfLastEnemy;
}

const sf::Vector2f& Map::getWaypointCoordinate(short unsigned path_index, size_t waypoint_index) const
{
    return enemyPaths[path_index][waypoint_index];
}

bool Map::isWaypointIndexInBound(short unsigned path_index, size_t waypoint_index) const
{
    return waypoint_index < enemyPaths[path_index].size() ? true : false;
}

bool Map::onMap(const sf::Vector2f& coordinate) const
{
    return sprite.getGlobalBounds().contains(coordinate);
}

bool Map::loadMap(const std::string& map_name)
{
    if(map_name == "Hardcoded Map 1")
    {
        enemyPaths = 
        {
             {sf::Vector2f(200,0), sf::Vector2f(200,100), sf::Vector2f(300,100), sf::Vector2f(300,150), sf::Vector2f(720,150), sf::Vector2f(720,400), sf::Vector2f(500,400), sf::Vector2f(500,200), sf::Vector2f(600,200), sf::Vector2f(600,600)}
            ,{sf::Vector2f(0,200), sf::Vector2f(100,200), sf::Vector2f(100,300), sf::Vector2f(150,300), sf::Vector2f(150,720), sf::Vector2f(400,720), sf::Vector2f(400,500), sf::Vector2f(200,500), sf::Vector2f(200,600), sf::Vector2f(600,600)}
        };
        textures = currentScene->getAnimation(map_name);
        animationTickInterval = 0;
        return true;
    }
    return false;
}
