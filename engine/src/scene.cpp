#include "scene.hpp"

Scene::Scene(SceneHandler& sh, sf::Vector2u window_size)
    :windowSize        (window_size)
    ,sceneHandler      (sh)
    ,userEventHandler  (new UserEventHandler(sh)) // just a default value
{ }

void Scene::setUp()
{
    for(auto list_iter = allGameObjects.begin(); list_iter != allGameObjects.end(); ++list_iter)
    {
        for(auto iter = (*list_iter)->begin(); iter != (*list_iter)->end(); ++iter)
        {
            (*iter)->setUp();
        }
    }
}

void Scene::update()
{
    for(auto list_iter = allGameObjects.begin(); list_iter != allGameObjects.end(); ++list_iter)
    {
        for(auto iter = (*list_iter)->begin(); iter != (*list_iter)->end(); ++iter)
        {
            if((*iter)->update())
            {
                iter = (*list_iter)->erase(iter);
                --iter;
            }
        }
    }
}

void Scene::draw(sf::RenderWindow& window)
{
    for(auto list_iter = allGameObjects.begin(); list_iter != allGameObjects.end(); ++list_iter)
    {
        for(auto iter = (*list_iter)->begin(); iter != (*list_iter)->end(); ++iter)
        {
            if((*iter)->draw(window))
            {
                iter = (*list_iter)->erase(iter);
                --iter;
            }
        }
    }
}

void Scene::handleWindowEvent(sf::RenderWindow& w)
{
    userEventHandler->handleWindowEvent(w);
}

sf::Texture Scene::loadTexture(const std::string& s)
{
    sf::Texture texture;
    if (! texture.loadFromFile(s))
        throw std::invalid_argument("Texture not found");
    return texture;
}

AnimatedGameObject::TextureList Scene::loadAnimation(const std::string& folder_name)
{
    AnimatedGameObject::TextureList ret;
    short unsigned loop_index(0), first_number(0), second_number(0);
    while(true)
    {
        first_number = loop_index / 10u;
        second_number = loop_index % 10u;
        try{
            ret.push_back(loadTexture(std::to_string(first_number) + std::to_string(second_number)));
        } catch(const std::invalid_argument&){
            if(loop_index == 0)
                throw std::invalid_argument("No textures found in folder: " + folder_name);
            break;
        }
        ++loop_index;
    }
    return ret;
}

sf::SoundBuffer Scene::loadSound(const std::string& s)
{
    
    sf::SoundBuffer sound;
    if (! sound.loadFromFile(s))
        throw std::invalid_argument("Sound not found");
    return sound;
}

