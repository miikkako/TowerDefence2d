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
            (*iter)->drawOrigin(w, sceneHandler.gameobjectOriginColor);
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
    std::string folder_name = extractFilename(folder_path);
    animationMap.insert(std::make_pair(folder_name
                                       ,this->loadAnimation(folder_path
                                                           ,file_extension)));
    sceneHandler.os << "The animation was saved to the animation-map as \""
            << folder_name << "\"" << std::endl;
    return folder_name;
}

std::string Scene::loadAndSaveSoundbuffer(const std::string& file_path)
{
    std::string filename = extractFilename(file_path);
    soundbufferMap.insert(std::make_pair(filename, this->loadSoundbuffer(file_path)));
    sceneHandler.os << "The sound buffer was saved to the sound buffer -map as \""
            << filename << "\"" << std::endl;
    return filename;
}

std::string Scene::loadAndSaveFont(const std::string& file_path)
{
    std::string filename = extractFilename(file_path);
    fontMap.insert(std::make_pair(filename, this->loadFont(file_path)));
    sceneHandler.os << "The font was saved to the font-map as \""
            << filename << "\"" << std::endl;
    return filename;
}

sf::Font& Scene::getFont(const std::string& font_name)
{
    try {
        return fontMap.at(font_name);
    } catch (std::exception& e) {
        throw std::invalid_argument("Scene::getFont(\"" + font_name + "\").");
    }
}

sf::SoundBuffer& Scene::getSoundbuffer(const std::string& soundbuffer_name)
{
    try {
        return soundbufferMap.at(soundbuffer_name);
    } catch (std::exception& e) {
        throw std::invalid_argument("Scene::getSoundbuffer(\"" + soundbuffer_name + "\").");
    }
}

AnimatedGameObject::TextureList* Scene::getAnimation(const std::string& animation_name)
{
    try {
        return &animationMap.at(animation_name);
    } catch (std::exception& e) {
        throw std::invalid_argument("Scene::getAnimation(\"" + animation_name + "\").");
    }
}

AnimatedGameObject::TextureList* Scene::loadAndSaveAndGetAnimation(const std::string& folder_path
                                                                  ,const std::string file_extension)
{
    std::string folder_name = this->loadAndSaveAnimation(folder_path, file_extension);
    return this->getAnimation(folder_name);
}

sf::Texture Scene::loadTexture(const std::string& file_path)
{
    sf::Texture t;
    if(!t.loadFromFile(file_path))
        throw std::invalid_argument("Texture \"" + file_path + "\" not found");
    sceneHandler.os << "Loaded texture \"" + file_path << "\"" << std::endl;
    return t;
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

sf::SoundBuffer Scene::loadSoundbuffer(const std::string& file_path)
{
    sf::SoundBuffer s;
    if(!s.loadFromFile(file_path))
        throw std::invalid_argument("Sound \"" + file_path + "\"not found");
    sceneHandler.os << "Loaded sound \"" + file_path << "\"" << std::endl;
    return s;
}

sf::Font Scene::loadFont(const std::string& file_path)
{
    sf::Font f;
    if(!f.loadFromFile(file_path))
        throw std::invalid_argument("Font\"" + file_path + "\" not found");
    sceneHandler.os << "Loaded font \"" + file_path << "\"" << std::endl;
    return f;
}

std::string extractFilename(const std::string& file_path)
{
    std::string filename;
    size_t pos = file_path.find_last_of("/");
    if(pos != std::string::npos)
        filename.assign(file_path.begin() + pos + 1, file_path.end());
    else
        filename = file_path;
    return filename;
}
