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
    typedef std::vector<std::shared_ptr<sf::Drawable>> DrawableList;
    typedef std::vector<DrawableList*> ListOfDrawableLists;
    
    Scene(SceneHandler& sh
         ,UserEventHandler* u
         ,sf::Vector2u window_size
         ,const std::string& window_title);
    virtual ~Scene();
    
    bool getDebugMode() const;
    std::ostream& getOs() const;
    std::ostream& getImportantOs() const;
    const sf::Vector2u& getWindowSize()   const       { return windowSize; };
//    void                setWindowSize(sf::Vector2u s) { windowSize = s; };
    const std::string&  getTitle()        const       { return title; };
    
    AnimatedGameObject::TextureList* getAnimation(const std::string& animation_name);
    AnimatedGameObject::TextureList* loadAndSaveAndGetAnimation(const std::string& folder_path
                                                               ,const std::string file_extension);
    
    virtual void print(std::ostream& os) const { (void) os; }; // optional
    friend std::ostream& operator<< (std::ostream& os, const Scene& s);
    friend class SceneHandler;
    
protected:
    virtual void updateSceneBehaviour() { }; // optional for the derived class
    virtual void drawSceneDebugThings(sf::RenderWindow& w) const { (void) w; }; // optional, only called if DEBUG mode is on
    
    ////////////////////////////////////////////////////////////
    /// \param folder_path the path to the folder containing the sprites named as '00.file_extension', '01.file_extension', and so on.
    /// \param file_extension the file extensions of the images in the folder
    /// \return the name that the animation was saved as to the animation-map (The folder name extracted from the path)
    ////////////////////////////////////////////////////////////
    std::string loadAndSaveAnimation(const std::string& folder_path
                                    ,const std::string file_extension);
    
    std::string loadAndSaveSoundBuffer(const std::string& filename); // saves the sound buffer using the file's name
    
    void addGameObjectListToBeUpdatedAndDrawn(GameObjectList* list);
    void addDrawableListToBeDrawn(DrawableList* list);
    
    SceneHandler&                     sceneHandler;
    std::shared_ptr<UserEventHandler> userEventHandler; // this can be overridden  
    
private:
    void handleWindowEvent(sf::RenderWindow& w);
    void setUp();
    void update();
    void draw(sf::RenderWindow& w);
    void drawDebugThings(sf::RenderWindow& w) const;
    
    sf::Texture loadTexture(const std::string& s);
    AnimatedGameObject::TextureList loadAnimation(const std::string& folder_path
                                                 ,const std::string file_extension);
    sf::SoundBuffer loadSoundBuffer(const std::string& filename);
    
    sf::Vector2u                                           windowSize;
    std::string                                            title;
    std::map<std::string, AnimatedGameObject::TextureList> animationMap;
    std::map<std::string, sf::SoundBuffer>                 soundBufferMap;
    ListOfGameObjectLists                                  allGameObjects;
    ListOfDrawableLists                                    allOtherDrawables; 
};

#endif /* SCENE_HPP */

