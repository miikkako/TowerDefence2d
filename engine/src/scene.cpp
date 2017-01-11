#include "scene.hpp"

Scene::Scene(SceneHandler& sh
            ,UserEventHandler* u
            ,sf::Vector2u window_size
            ,const std::string& window_title)
    :sceneHandler      (sh)
    ,userEventHandler  (u)
    ,windowSize        (window_size)
    ,title             (window_title)
{ }

Scene::~Scene()
{
    this->getOs() << "In the destructor of Scene \"" << typeid(*this).name()
            << "\", the destructor is not yet implemented" << std::endl;
}

void Scene::handleWindowEvent(sf::RenderWindow& w)
{
    userEventHandler->handleWindowEvent(w);
}

void Scene::setUp()
{
    for(auto list_iter = allGameObjects.begin(); list_iter != allGameObjects.end();
        ++list_iter)
    {
        for(auto iter = (*list_iter)->begin(); iter != (*list_iter)->end(); ++iter)
        {
            (*iter)->setUp();
        }
    }
}

void Scene::update()
{
    for(auto list_iter = allGameObjects.begin(); list_iter != allGameObjects.end();
        ++list_iter)
    {
        for(auto iter = (*list_iter)->begin(); iter != (*list_iter)->end(); ++iter)
        {
            if(!(*iter)->update())
            {
                iter = (*list_iter)->erase(iter);
                --iter;
            }
        }
    }
    this->updateSceneBehaviour();
}

void Scene::draw(sf::RenderWindow& w)
{
    for(auto list_iter = allGameObjects.begin(); list_iter != allGameObjects.end();
        ++list_iter)
    {
        for(auto iter = (*list_iter)->begin(); iter != (*list_iter)->end(); ++iter)
        {
            if(!(*iter)->draw(w))
            {
                iter = (*list_iter)->erase(iter);
                --iter;
            }
        }
    }
    for(auto list_iter = allOtherDrawables.begin(); list_iter != allOtherDrawables.end();
        ++list_iter)
    {
        for(auto iter = (*list_iter)->begin(); iter != (*list_iter)->end(); ++iter)
        {
            w.draw(**iter);
        }
    }
}

void Scene::drawDebugThings(sf::RenderWindow& w) const
{
    for(auto list_iter = allGameObjects.begin(); list_iter != allGameObjects.end();
        ++list_iter)
    {
        for(auto iter = (*list_iter)->begin(); iter != (*list_iter)->end(); ++iter)
        {
            (*iter)->drawBoundingBox(w, sceneHandler.boundingBoxColor);
            (*iter)->drawOriginCircle(w, sceneHandler.gameobjectOriginColor);
            (*iter)->drawOtherDebugThings(w);
        }
    }
    this->drawSceneDebugThings(w);
}

std::ostream& operator<< (std::ostream& os, const Scene& s)
{
    os << "Scene " << typeid(s).name() << ":" << std::endl;
    os << "All AnimatedGameObjects that get update()'d and draw()'d :" << std::endl;
    for(auto list_iter = s.allGameObjects.begin(); list_iter != s.allGameObjects.end();
        ++list_iter)
    {
        for(auto iter = (*list_iter)->begin(); iter != (*list_iter)->end(); ++iter)
        {
            os << "\t" << **iter << std::endl;
        }
    }
    s.print(os);
    return os;
}

bool Scene::getDebugMode() const
{
    return sceneHandler.DEBUG;
}

std::ostream& Scene::getOs() const
{
    return sceneHandler.os;
}

std::ostream& Scene::getImportantOs() const
{
    return sceneHandler.importantOs;
}

void Scene::addGameObjectListToBeUpdatedAndDrawn(GameObjectList* list)
{
    allGameObjects.push_back(list);
}

void Scene::addDrawableListToBeDrawn(DrawableList* list)
{
    allOtherDrawables.push_back(list);
}

std::string Scene::loadAndSaveAnimation(const std::string& folder_path
                                       ,const std::string file_extension)
{
    // Extract the folder name from the path first
    std::string folder_name;
    size_t pos = folder_path.find_last_of("/");
    if(pos != std::string::npos)
        folder_name.assign(folder_path.begin() + pos + 1, folder_path.end());
    else
        folder_name = folder_path;
    animationMap.insert(std::make_pair(folder_name
                                       ,this->loadAnimation(folder_path
                                                           ,file_extension)));
    sceneHandler.os << "The animation was saved to the animation-map as \""
            << folder_name << "\"" << std::endl;
    return folder_name;
}

std::string Scene::loadAndSaveSoundBuffer(const std::string& filename)
{
    soundBufferMap.insert(std::make_pair(filename, this->loadSoundBuffer(filename)));
    return filename;
}

AnimatedGameObject::TextureList* Scene::getAnimation(const std::string& animation_name)
{
    try {
        return &animationMap.at(animation_name);
    } catch (std::exception& e) {
        throw std::invalid_argument("Scene::getAnimation('" + animation_name + "').");
    }
}

AnimatedGameObject::TextureList* Scene::loadAndSaveAndGetAnimation(const std::string& folder_path
                                                                  ,const std::string file_extension)
{
    std::string folder_name = this->loadAndSaveAnimation(folder_path, file_extension);
    return this->getAnimation(folder_name);
}

sf::Texture Scene::loadTexture(const std::string& s)
{
    sf::Texture texture;
    if(!texture.loadFromFile(s))
        throw std::invalid_argument("Texture \"" + s + "\" not found");
    sceneHandler.os << "Loaded texture \"" + s << "\"" << std::endl;
    return texture;
}

AnimatedGameObject::TextureList Scene::loadAnimation(const std::string& folder_path
                                                    ,const std::string file_extension)
{
    sceneHandler.os << "Loading animation from \"" << folder_path << "\"" << std::endl;
    AnimatedGameObject::TextureList ret;
    short unsigned loop_index(0), first_number(0), second_number(0);
    while(true)
    {
        first_number = loop_index / 10u;
        second_number = loop_index % 10u;
        try {
            std::string texture_full_path = folder_path
                                          + "/"
                                          + std::to_string(first_number)
                                          + std::to_string(second_number)
                                          + "."
                                          + file_extension;
            ret.push_back(loadTexture(texture_full_path));
        } catch(const std::invalid_argument&) {
            if(loop_index == 0)
                throw std::invalid_argument("No textures found in folder: \""
                                            + folder_path + "\"");
            break;
        }
        ++loop_index;
    }
    sceneHandler.os << "Succesfully loaded animation from folder \"" << folder_path
            << "\"" << std::endl;
    return ret;
}

sf::SoundBuffer Scene::loadSoundBuffer(const std::string& filename)
{
    sf::SoundBuffer sound;
    if(!sound.loadFromFile(filename))
        throw std::invalid_argument("Sound \"" + filename + "\"not found");
    return sound;
}

