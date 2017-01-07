#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <vector>
#include <SFML/Graphics.hpp>

class Scene;

/* This class shall be the base class of all GameObjects */
class AnimatedGameObject
{
public:
    typedef std::vector<sf::Texture> TextureList;
    
    /* In the constructor, the sprite's origin is set to the texture's center by default */
    AnimatedGameObject(float x_pos, float y_pos,
        TextureList* t, short unsigned animation_tick_interval, bool centerize_origin = true);
    
    /* This constructor also sets the rotation of the sprite */
    AnimatedGameObject(float x_pos, float y_pos, float rotation_angle_degrees,
        TextureList* t, short unsigned animation_tick_interval, bool centerize_origin = true);
    
    sf::Sprite& getSprite() { return sprite; };
    
    /* This draw-method is bound to gameticks. Return false = delete object */
    virtual bool draw(sf::RenderWindow& w);
//    bool otherDrawMethodThatIsNotBoundToGameTicks(sf::RenderWindow& w);
    
    virtual void setUp() {}; // optional
    virtual bool update() = 0; // obligatory, return false = delete object
    
protected:
    void updateAnimation();
    sf::Texture& getNextTexture();
//    void setAnimation(TextureList& t);
    void initializeAnimation();
    
    short unsigned currentFrameIndex = 0; // this always starts from zero
    short unsigned ticksFromLastFrameUpdate = 0; // this always starts from zero
    
    Scene* currentScene; // this can be initialized in the derived classes
    TextureList* textures; // the corresponding scene handles the memory of these pointers
    short unsigned animationTickInterval;
    bool centerizeOrigin;
    
    sf::Sprite sprite;
};

/* StaticGameObject can be used as e.g. explosion, gun flame, etc. */
class StaticAnimation : public AnimatedGameObject
{
public:
    StaticAnimation(float x_pos, float y_pos, float rotation_angle_degrees,
        short unsigned animation_loops_lifetime, TextureList* t,
        short unsigned animation_tick_interval, bool centerize_origin = true);
    /* This class has its own draw-method */
    bool draw(sf::RenderWindow& w) override;
    
private:
    short unsigned animationLoopsLifetime; // initialize as 0 if the object lasts forever
    short unsigned currentLoop = 0;
};


#endif /* GAMEOBJECT_HPP */
