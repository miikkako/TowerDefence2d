#include "include/map.hpp"
#include "include/towerdefencescene.hpp"
#include <array>
#include <stdlib.h>
#include <fstream>
#include <sstream>

Map::Map   (TowerDefenceScene* current_scene
           ,const std::string& sprite_folder_path
           ,const std::string& image_file_extension)
        :AnimatedGameObject(0
                           ,0
                           ,current_scene->loadAndSaveAndGetAnimation(sprite_folder_path
                                                                     ,image_file_extension)
                           ,0
                           ,0.f
                           ,false)
        ,currentScene       (current_scene)
        ,mapName            (extractFilename(sprite_folder_path))
        ,contentFolderPath  (sprite_folder_path)
        ,enemypathsFilename  ("paths.dat")
{
    if(mapName == "FirstMap")
    {
        if(!loadEnemyPathFromFile())
            throw std::invalid_argument("Loading the map \"" + mapName + "\" failed.");
//        textures = currentScene->getAnimation("FirstMap");
//        animationTickInterval = 0;
    }
    else
        throw std::invalid_argument("No map named \"" + mapName + "\" found.");
    currentScene->getOs() << "Loaded Map \"" + mapName + "\" and its waypoints succesfully" << std::endl;
}

void Map::drawOtherDebugThings(sf::RenderWindow& w) const
{
    // draw waypoints
    sf::CircleShape circle(4);
    this->setShapeOriginToCenter(&circle);
    sf::Text text;
    text.setFont(currentScene->getFont("Regular.otf"));
    text.setCharacterSize(10);
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Regular);
    std::array<sf::Color, 4> waypoint_colors
        {{sf::Color(38, 120, 230), sf::Color(200, 90, 120), sf::Color(90, 200, 120), sf::Color(120, 200, 15)}};
    for(size_t path_i(0); path_i < enemyPaths.size(); ++path_i)
    {
        circle.setFillColor(waypoint_colors[path_i % 4]);
        for(size_t waypoint_i(0); waypoint_i < enemyPaths[path_i].size(); ++waypoint_i)
        {
            circle.setPosition(enemyPaths[path_i][waypoint_i]);
            text.setPosition(enemyPaths[path_i][waypoint_i].x, enemyPaths[path_i][waypoint_i].y - 15);
            text.setString(std::to_string(waypoint_i));
            w.draw(circle);
            w.draw(text);
        }
    }
}

short unsigned Map::getPathIndexForEnemy()
{
    return pathIndexOfLastEnemy++ % enemyPaths.size();
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

bool Map::loadEnemyPathFromFile()
{
//    enemyPaths = 
//    {
//        {sf::Vector2f(0,205), sf::Vector2f(100,220), sf::Vector2f(200,230), sf::Vector2f(250,240), sf::Vector2f(275,255), sf::Vector2f(290,270), sf::Vector2f(295,285), sf::Vector2f(290,310)}
//    };
    std::string line;
    std::string filepath(contentFolderPath + "/" + enemypathsFilename);
    std::ifstream enemypaths_file(filepath.c_str());
    currentScene->getOs() << "Opening Enemy-paths file \"" << filepath << "\"...";
    if (enemypaths_file.is_open())
    {
        float coord1, coord2;
        currentScene->getOs() << " opening succesful, reading the paths from the file" << std::endl;
        while(std::getline(enemypaths_file, line))
        {
            std::istringstream line_iss(line);
            std::string line_str;
            std::vector<sf::Vector2f> vec;
            do {
                if(std::getline(line_iss, line_str, '('))
                {
                    if(std::getline(line_iss, line_str, ','))
                    {
                        coord1 = std::stof(line_str);
                        if(std::getline(line_iss, line_str, ')'))
                        {
                            coord2 = std::stof(line_str);
                            vec.push_back(sf::Vector2f(coord1, coord2));
                        }
                        else
                            return false;
                    }
                    else
                        return false;
                }
                
            } while(std::getline(line_iss, line_str, ','));
            enemyPaths.push_back(vec);
        }
    }
    else
    {
        currentScene->getOs() << " opening unsuccesful" << std::endl;
        return false;
    }
    return true;
}
