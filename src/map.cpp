#include "include/map.hpp"
#include "include/towerdefencescene.hpp"

Map::Map   (TowerDefenceScene* current_scene
           ,const std::string& map_name
           ,const std::string& sprite_folder_path
           ,const std::string& image_file_extension)
        :AnimatedGameObject(0
                           ,0
                           ,current_scene->loadAndSaveAndGetAnimation(sprite_folder_path
                                                                     ,image_file_extension)
                           ,0
                           ,0.f
                           ,false)
        ,currentScene(current_scene)
{
    if(map_name == "FirstMap")
    {
        enemyPaths = 
        {
             {sf::Vector2f(200,0), sf::Vector2f(200,100), sf::Vector2f(300,100), sf::Vector2f(300,150), sf::Vector2f(700,150), sf::Vector2f(700,400), sf::Vector2f(500,400), sf::Vector2f(500,200), sf::Vector2f(600,200), sf::Vector2f(600,600)}
            ,{sf::Vector2f(0,200), sf::Vector2f(100,200), sf::Vector2f(100,300), sf::Vector2f(150,300), sf::Vector2f(150,700), sf::Vector2f(400,700), sf::Vector2f(400,500), sf::Vector2f(200,500), sf::Vector2f(200,600), sf::Vector2f(600,600)}
        };
//        textures = currentScene->getAnimation("FirstMap");
//        animationTickInterval = 0;
    }
    else
        throw std::invalid_argument("No map named '" + map_name + "' found.");
    currentScene->getOs() << "Loaded Map '" + map_name + "' succesfully" << std::endl;
}

void Map::drawOtherDebugThings(sf::RenderWindow& w) const
{
    (void) w;
}

short unsigned Map::getPathIndexForEnemy()
{
    if(++pathIndexOfLastEnemy >= enemyPaths.size())
        pathIndexOfLastEnemy = 0;
    return pathIndexOfLastEnemy;
}

const sf::Vector2f& Map::getWaypoint(short unsigned path_index, size_t waypoint_index) const
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

