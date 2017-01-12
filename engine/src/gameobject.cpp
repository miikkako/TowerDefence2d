#include "include/gameobject.hpp"
#include <typeinfo>

AnimatedGameObject::AnimatedGameObject(float x_pos
                                      ,float y_pos
                                      ,TextureList* t
                                      ,short unsigned animation_tick_interval
                                      ,float rotation_angle_degrees
                                      ,bool centerize_origin)
        :textures(t)
        ,animationTickInterval(animation_tick_interval)
        ,centerizeOrigin(centerize_origin)
{
    sprite.setPosition(x_pos, y_pos);
    this->initializeAnimation();
    sprite.setRotation(rotation_angle_degrees);
}

AnimatedGameObject::AnimatedGameObject(sf::Vector2f pos
                                      ,TextureList* t
                                      ,short unsigned animation_tick_interval
                                      ,float rotation_angle_degrees
                                      ,bool centerize_origin)
        :textures(t)
        ,animationTickInterval(animation_tick_interval)
        ,centerizeOrigin(centerize_origin)
{
    sprite.setPosition(pos);
    this->initializeAnimation();
    sprite.setRotation(rotation_angle_degrees);
}

void AnimatedGameObject::addChildDrawable(std::shared_ptr<sf::Shape> obj)
{
    childrenShapes.push_back(obj);
}

void AnimatedGameObject::removeChildDrawable(sf::Shape* obj_ptr)
{
    for(auto iter = childrenShapes.begin(); iter != childrenShapes.end(); ++iter)
    {
        if(iter->get() == obj_ptr)
        {
            iter = childrenShapes.erase(iter);
            --iter;
        }
    }
}

void AnimatedGameObject::move(sf::Vector2f&& movement)
{
    sprite.move(movement);
    for(auto iter = childrenShapes.begin(); iter != childrenShapes.end(); ++iter)
        (*iter)->move(movement);
}

void AnimatedGameObject::setRotation(const sf::Vector2f& direction)
{
    sprite.setRotation(angleDeg(direction)); // angle in degrees inside setRotation
    //@TODO: rotate the bounding box
}

bool AnimatedGameObject::draw(sf::RenderWindow& w)
{
    this->updateAnimation();
    this->onDraw(w);
    return true;
}

void AnimatedGameObject::onDraw(sf::RenderWindow& w)
{
    w.draw(sprite);
    for(auto iter = childrenShapes.begin(); iter != childrenShapes.end(); ++iter)
        w.draw(**iter);
}

void AnimatedGameObject::drawBoundingBox(sf::RenderWindow& w, const sf::Color& c) const
{
    sf::RectangleShape bbox(sf::Vector2f(sprite.getLocalBounds().width,
                                         sprite.getLocalBounds().height));
    bbox.setFillColor(sf::Color::Transparent);
    bbox.setOutlineThickness(2);
    bbox.setOutlineColor(c);
    bbox.setPosition(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top);
    w.draw(bbox);
}

void AnimatedGameObject::drawOrigin(sf::RenderWindow& w, const sf::Color& c) const
{
    sf::CircleShape circle = sf::CircleShape(3);
    circle.setFillColor(c);
    this->setShapeOriginToCenter(&circle);
    circle.setPosition(sprite.getPosition());
    w.draw(circle);
}

void AnimatedGameObject::updateAnimation()
{
//    if(!textures)
//        throw std::runtime_error(std::string("Object ") + typeid(*this).name() + "'s 'textures'-member points to null");
    if(animationTickInterval > 0 && ++ticksFromLastFrameUpdate >= animationTickInterval)
    {
        sprite.setTexture(this->getNextTexture(), true);
        this->setOriginToCenter();
        ticksFromLastFrameUpdate = 0;
    }
}

sf::Texture& AnimatedGameObject::getNextTexture()
{
    if(currentFrameIndex >= textures->size() - 1)
        currentFrameIndex = 0;
    else
        ++currentFrameIndex;
    return textures->at(currentFrameIndex);
}

void AnimatedGameObject::initializeAnimation()
{
    if(!textures)
        throw std::runtime_error(std::string("Tried to set object ")
                + typeid(*this).name() + "'s 'textures'-member to nullptr");
    sprite.setTexture(textures->at(0), true); // start with the first texture in the list
    if(centerizeOrigin)
    {
        this->setOriginToCenter();
    }
}

void AnimatedGameObject::setShapeOriginToCenter(sf::Shape* s)
{
    sf::FloatRect rect = s->getLocalBounds();
    s->setOrigin(rect.left + rect.width/2.0f, rect.top + rect.height/2.0f);
}

void AnimatedGameObject::setOriginToCenter()
{
    sf::FloatRect rect = sprite.getLocalBounds();
    sprite.setOrigin(rect.left + rect.width/2.0f, rect.top + rect.height/2.0f);
}

void AnimatedGameObject::setAnimation(TextureList* t)
{
    textures = t;
    this->initializeAnimation();
}


/* Explosions, etc. */
StaticAnimation::StaticAnimation(float x_pos, float y_pos, TextureList* t,
    short unsigned animation_loops_lifetime, short unsigned animation_tick_interval,
    float rotation_angle_degrees, bool centerize_origin)
        :AnimatedGameObject(x_pos, y_pos, t, animation_tick_interval,
            rotation_angle_degrees, centerize_origin)
        ,animationLoopsLifetime(animation_loops_lifetime)
{ }

StaticAnimation::StaticAnimation(sf::Vector2f pos, TextureList* t,
    short unsigned animation_loops_lifetime, short unsigned animation_tick_interval,
    float rotation_angle_degrees, bool centerize_origin)
        :AnimatedGameObject(pos, t, animation_tick_interval,
            rotation_angle_degrees, centerize_origin)
        ,animationLoopsLifetime(animation_loops_lifetime)
{ }

bool StaticAnimation::draw(sf::RenderWindow& w)
{
    /* First, check if the animation has lived enough */
    if(animationLoopsLifetime > 0 && currentLoop++ > animationLoopsLifetime)
        return false;
    this->updateAnimation();
    this->onDraw(w);
    return true;
}

std::ostream& operator<<(std::ostream& os, const AnimatedGameObject& obj)
{
    os << "AnimatedGameObject " << typeid(obj).name() << ": "
       << "Position = " << obj.sprite.getPosition() << ". "
       << "Rotation = " << obj.sprite.getRotation() << ". "
       << "Origin = " << obj.sprite.getOrigin() << ". "
       ;
    obj.print(os);
    return os;
}