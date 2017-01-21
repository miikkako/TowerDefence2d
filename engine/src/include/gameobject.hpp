#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>

#define PI 3.14159f // use this rather than M_PI 

class Scene;

/* This class shall be the base class of all GameObjects */
class AnimatedGameObject
{
public:
    typedef std::vector<sf::Texture> TextureList;
    
    ////////////////////////////////////////////////////////////
    /// \param source two component vector with member "x" and "y"
    /// \return the length of the parameter source
    ////////////////////////////////////////////////////////////
    template <typename vec_T>
    static float length(const vec_T& source);
    
    ////////////////////////////////////////////////////////////
    /// \param source two component vector with member "x" and "y"
    /// \return the angle of the vector in degrees
    ////////////////////////////////////////////////////////////
    template <typename vec_T>
    static float angleDeg(const vec_T& source);
    
    ////////////////////////////////////////////////////////////
    /// \param source two component vector with member "x" and "y"
    /// \return the parameter source vector normalized
    ////////////////////////////////////////////////////////////
    template <typename vec_T>
    static vec_T normalize(const vec_T& source);
    
    static void setShapeOriginToCenter(sf::Shape* s);
    static void setTextOriginToCenter(sf::Text& s);
    
    ////////////////////////////////////////////////////////////
    /// \brief Construct the AnimatedGameObject with the parameters
    /// \param x_pos the initial x coordinate to set the object on
    /// \param y_pos the initial y coordinate to set the object on
    /// \param t pointer to a list of textures that loop
    /// \param animation_tick_interval the interval of game ticks of the animation loop
    /// \param rotation_angle_degrees the initial rotation of the object
    /// \param centerize_origin set the center of the sprite to the center of the texture, otherwise in the top left corner
    ////////////////////////////////////////////////////////////
    AnimatedGameObject(float x_pos
                      ,float y_pos
                      ,const TextureList* t
                      ,short unsigned animation_tick_interval
                      ,float rotation_angle_degrees = 0
                      ,bool centerize_origin = true);
    
    ////////////////////////////////////////////////////////////
    /// \brief Construct the AnimatedGameObject with the parameters
    /// \param pos the initial position to set the object on
    /// \param t pointer to a list of textures that loop
    /// \param animation_tick_interval the interval of game ticks of the animation loop
    /// \param rotation_angle_degrees the initial rotation of the object
    /// \param centerize_origin set the center of the sprite to the center of the texture, otherwise to the top left corner
    ////////////////////////////////////////////////////////////
    AnimatedGameObject(sf::Vector2f pos
                      ,const TextureList* t
                      ,short unsigned animation_tick_interval
                      ,float rotation_angle_degrees = 0
                      ,bool centerize_origin = true);
    
    bool insideBoundingBox(const sf::Vector2f& coord) const;
    
    ////////////////////////////////////////////////////////////
    /// \brief Add a drawable and movable shape to be attached to the parent object
    /// NOTE! the pointer is saved to the list as a smart pointer, 
    /// i.e. its destructor will be called when the main object (and the list) is destroyed
    /// \param obj_ptr the drawable shape
    ////////////////////////////////////////////////////////////
    void addChildDrawable(std::shared_ptr<sf::Shape> obj); // @TODO: addChildAnimatedGameObject()
    void removeChildDrawable(sf::Shape* obj_ptr);
    
    virtual void print(std::ostream& os) const { (void) os; }; // optional
    friend std::ostream& operator<<(std::ostream& os, const AnimatedGameObject& a);
    
    friend class StaticAnimation;
    friend class Scene;
    
protected:
    virtual void setUp() {}; // optional
    virtual bool update() { return true; }; // optional, return false = delete object
    virtual void drawOtherDebugThings(sf::RenderWindow& w) { (void) w; }; // optional, only called if DEBUG mode is on
    
    ////////////////////////////////////////////////////////////
    /// \brief Draw the object's information on top of the object
    /// This gets called if DEBUG is on and mouse is hovered over the object (can be overridden)
    /// This method is called from the UserEventHandler
    /// \param w the window to draw the tooltip on
    ////////////////////////////////////////////////////////////
    virtual void drawDebugTooltip(sf::RenderWindow& w, const sf::Font& f) const; // optional to override
    // @TODO: make one method for drawing debug tooltip, and then ask additional information as strings in virtual methods
    
    virtual void onMouseOverDraw(sf::RenderWindow& w, const sf::Font& f)
    { (void) w; (void) f; }; // optional
    
    virtual void onMouseOverAction() { }; // optional
    virtual void onMouseButtonPressedAction() { }; // optional
    virtual void onMouseButtonReleasedAction() { }; // optional
    
    ////////////////////////////////////////////////////////////
    /// \brief Move the object and its children shapes
    /// \param movement the amount that the object is moved as an rvalue reference
    ////////////////////////////////////////////////////////////
    void move(sf::Vector2f&& movement);
    
    ////////////////////////////////////////////////////////////
    /// \brief Set this object's orientation towards the pointed direction
    /// This method also sets the orientation of the sprite's bounding box
    /// \param direction the vector that points the direction
    ////////////////////////////////////////////////////////////
    void setRotation(const sf::Vector2f& direction);
    
    void setOriginToCenter();
    void setAnimation(const TextureList* t);
    const TextureList* getAnimation() const { return textures; };
    
    sf::Sprite                          sprite; // For now, the sprite is freely modifiable
    short unsigned                      animationTickInterval;
    bool                                centerizeOrigin;
    
private:
    ////////////////////////////////////////////////////////////
    /// \brief Draw and animate the object
    /// Update the animation tick every time called.
    /// \param w target to draw the object to
    /// \return does the object live?
    ////////////////////////////////////////////////////////////
    virtual bool draw(sf::RenderWindow& w);
//    bool otherDrawMethodThatIsNotBoundToGameTicks(sf::RenderWindow& w);?
    void initializeAnimation();
    void onDraw(sf::RenderWindow& w);
    void updateAnimation();
    const sf::Texture& getNextTexture();
    
    // Debugging methods, only called if DEBUG mode is on
    void drawDebugThings(sf::RenderWindow& w) const;
    void drawBoundingBox(sf::RenderWindow& w) const;
    void drawOrigin(sf::RenderWindow& w) const;
    void onMouseOverDebugDraw(sf::RenderWindow& w, const sf::Font& f);
    
    const TextureList*                  textures; // Scene handles the memory of the pointers
    short unsigned                      currentFrameIndex = 0;
    short unsigned                      ticksFromLastFrameUpdate = 0;
    
    // The children shapes get drawn when the parent object gets, and moved in the member "move()"-method.
    // The vector owns the pointers, i.e. when the gameobject is destroyed, the shared pointers are destroyed
    // @TODO: the list could be a list of AnimatedGameObjects
    std::vector<std::shared_ptr<sf::Shape>> childrenShapes;
};

// @TODO: move derived utility classes to a separate file
/* StaticAnimation can be used as e.g. explosion, gun flame, etc. */
class StaticAnimation : public AnimatedGameObject
{
public:
    StaticAnimation(float x_pos
                   ,float y_pos
                   ,const TextureList* t
                   ,short unsigned animation_loops_lifetime
                   ,short unsigned animation_tick_interval
                   ,float rotation_angle_degrees = 0
                   ,bool centerize_origin = true);
    StaticAnimation(sf::Vector2f pos
                   ,const TextureList* t
                   ,short unsigned animation_loops_lifetime
                   ,short unsigned animation_tick_interval
                   ,float rotation_angle_degrees = 0
                   ,bool centerize_origin = true);
    
private:
    ////////////////////////////////////////////////////////////
    /// \param w target which the object is drawn to
    /// \return false if the object has looped enough, true otherwise
    ////////////////////////////////////////////////////////////
    bool draw(sf::RenderWindow& w) override;
    
    short unsigned animationLoopsLifetime; // initialize as 0 if the object lasts forever
    short unsigned currentLoop = 0;
};


// @TODO: move utility vector methods and other helper methods to: a) another file, b) another class, c) to free functions
template <typename vec_T>
float AnimatedGameObject::length(const vec_T& source)
{
    return sqrt((source.x * source.x) + (source.y * source.y));
}

template <typename vec_T>
float AnimatedGameObject::angleDeg(const vec_T& source)
{
    return atan2(source.y, source.x) * 180 / PI;
}

template <typename vec_T>
vec_T AnimatedGameObject::normalize(const vec_T& source)
{
    float len = length(source);
    if(len != 0)
        return vec_T(source.x / len, source.y / len);
    else
        return source;
}

/* Helper functions for printing SFML rectangles and vectors */
template<typename T>
std::ostream& operator<< (std::ostream &os, const sf::Rect<T>& rect)
{
    os << "(Rect: left " << rect.left  << ", top " << rect.top << ", width "
       << rect.width << ", height " << rect.height << ")";
    return os;
}

template<typename T>
std::ostream& operator<< (std::ostream &os, const sf::Vector2<T>& vec)
{
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}

#endif /* GAMEOBJECT_HPP */
