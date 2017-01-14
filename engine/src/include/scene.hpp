#ifndef SCENE_HPP
#define SCENE_HPP

#include "gameobject.hpp"
#include "usereventhandler.hpp"
#include "soundhandler.hpp"
#include "scenehandler.hpp"

//@TODO: move all file-related stuff out of Scene-class
class Scene
{
public:
    typedef std::vector<std::shared_ptr<AnimatedGameObject>> GameObjectList;
    typedef std::vector<GameObjectList*> ListOfGameObjectLists;
    typedef std::vector<std::shared_ptr<sf::Drawable>> DrawableList;
    typedef std::vector<DrawableList*> ListOfDrawableLists;
    
    Scene(SceneHandler& sh
         ,std::shared_ptr<UserEventHandler> u
         ,sf::Vector2u window_size
         ,const std::string& window_title
         ,const std::string& engine_directory_path);
    virtual ~Scene();
    
    bool getDebugMode() const;
    std::ostream& getOs() const;
    std::ostream& getImportantOs() const;
    const sf::Vector2u& getWindowSize()   const       { return windowSize; };
//    void                setWindowSize(sf::Vector2u s) { windowSize = s; };
    const std::string&  getTitle()        const       { return title; };
    
    // @TODO: an empty animation getter. i.e. returns empty sf::Textures (So that the animation can be an empty texture)
    const sf::Font& getDefaultFont() const noexcept;
    const sf::Font& getFont(const std::string& font_name) const;
    const sf::SoundBuffer& getSoundbuffer(const std::string& soundbuffer_name) const;
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
    /// \brief Load all the textures from a folder
    /// NOTE! Do not use a trailing slash in the folder_path parameter
    /// \param folder_path the path to the folder containing the sprites named as '00.file_extension', '01.file_extension', and so on.
    /// \param file_extension the file extensions of the images in the folder
    /// \return the name that the animation was saved as to the animation-map (The folder name extracted from the path)
    ////////////////////////////////////////////////////////////
    std::string loadAndSaveAnimation(const std::string& folder_path
                                    ,const std::string file_extension);
    
    std::string loadAndSaveSoundbuffer(const std::string& file_path); // save the sound buffer using the file's name
    
    std::string loadAndSaveFont(const std::string& file_path); // save the font using the file's name
    
    void addGameObjectListToBeUpdatedAndDrawn(GameObjectList* list);
    void addDrawableListToBeDrawn(DrawableList* list);
    
    SceneHandler&                     sceneHandler;
    std::shared_ptr<UserEventHandler> userEventHandler;
    
private:
    void setUp();
    void update();
    void draw(sf::RenderWindow& w);
    void drawDebugThings(sf::RenderWindow& w) const;
    void _drawDefaultSceneDebugThings(sf::RenderWindow& w) const;
    
    sf::Texture loadTexture(const std::string& filename);
    AnimatedGameObject::TextureList loadAnimation(const std::string& folder_path
                                                 ,const std::string file_extension);
    sf::SoundBuffer loadSoundbuffer(const std::string& file_path);
    sf::Font loadFont(const std::string& file_path);
    void loadAndSaveDefaultFont() noexcept;
    
    sf::Vector2u                                           windowSize;
    std::string                                            title;
    std::string                                            engineDirectoryPath;
    std::string                                            engineAssetsPath;
    std::string                                            defaultFontFilename;
    std::map<std::string, AnimatedGameObject::TextureList> animationMap;
    std::map<std::string, sf::SoundBuffer>                 soundbufferMap;
    std::map<std::string, sf::Font>                        fontMap;
    ListOfGameObjectLists                                  allGameObjects;
    ListOfDrawableLists                                    allOtherDrawables; 
};

std::string extractFilename(const std::string& file_path);

#endif /* SCENE_HPP */

