#ifndef SCENE_HPP
#define SCENE_HPP

#include "gameobject.hpp"
#include "usereventhandler.hpp"
#include "soundhandler.hpp"
#include "scenehandler.hpp"

class Scene
{
public:
    typedef std::vector<std::shared_ptr<AnimatedGameObject>> GameObjectList;
    typedef std::vector<GameObjectList*> ListOfGameObjectLists;
    static sf::Texture loadTexture(const std::string& s);
    static AnimatedGameObject::TextureList loadAnimation(const std::string& folder_name);
    static sf::SoundBuffer loadSound(const std::string& s);
    
    Scene(SceneHandler& sh, sf::Vector2u window_size);
    virtual ~Scene() { /* No implementation yet */ };
    
    void handleWindowEvent(sf::RenderWindow& w);
    
    void setUp();
    void update();
    void draw(sf::RenderWindow& window);
    
    AnimatedGameObject::TextureList* getAnimation(const std::string& animation_name);
    const sf::Vector2u& getWindowSize()   const { return windowSize; };
    const std::string&  getTitle()        const { return title; };
    std::ostream& getOs() const;
    
protected:
    virtual void updateSceneBehaviour() { }; // optional
    
    sf::Vector2u windowSize;
    std::string  title;
    SceneHandler&                       sceneHandler;
    std::shared_ptr<UserEventHandler>   userEventHandler; // this needs to be initialized in the derived classes
    
    std::map<std::string, AnimatedGameObject::TextureList> animationMap;
    std::map<std::string, sf::SoundBuffer>                 soundMap;
    
    ListOfGameObjectLists allGameObjects;
};

#endif /* SCENE_HPP */

